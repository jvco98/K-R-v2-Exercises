#!/usr/bin/env bash
# Test runner for exercise5_16
# Usage:
#   ./tests.sh                 # auto-detects or builds via CMake
#   ./tests.sh /path/to/exe    # run against explicit executable

set -u -o pipefail

RED="$(printf '\033[31m')"
GRN="$(printf '\033[32m')"
YEL="$(printf '\033[33m')"
RST="$(printf '\033[0m')"

log() { printf "%s\n" "$*"; }
ok()  { printf "${GRN}%s${RST}\n" "$*"; }
warn(){ printf "${YEL}%s${RST}\n" "$*"; }
err() { printf "${RED}%s${RST}\n" "$*"; }

detect_or_build_exec() {
  if [[ $# -ge 1 ]]; then
    echo "$1"
    return 0
  fi

  # Common locations
  local candidates=(
    "./exercise5_16"
    "./exercise5_16.exe"
    "./build/exercise5_16"
    "./build/exercise5_16.exe"
    "./cmake-build-debug/exercise5_16"
    "./cmake-build-debug/exercise5_16.exe"
    "./cmake-build-release/exercise5_16"
    "./cmake-build-release/exercise5_16.exe"
  )
  for c in "${candidates[@]}"; do
    if [[ -x "$c" ]]; then
      echo "$c"
      return 0
    fi
  done

  if [[ -f "CMakeLists.txt" ]]; then
    warn "Executable not found; attempting to build with CMake..."
    cmake -S . -B build >/dev/null
    cmake --build build --config Release >/dev/null
    # Try build outputs again
    for c in "${candidates[@]}"; do
      if [[ -x "$c" ]]; then
        echo "$c"
        return 0
      fi
    done
  fi

  err "Could not locate or build the executable."
  exit 2
}

run_test() {
  # Args:
  # 1: test name
  # 2: program args (single string, may be empty)
  # 3: input text
  # 4: expected output text
  local name="$1"
  local args="$2"
  local input="$3"
  local expected="$4"

  local tdir
  tdir="$(mktemp -d)"
  trap 'rm -rf "$tdir"' RETURN

  printf "%s" "$input"   > "$tdir/input.txt"
  printf "%s" "$expected" > "$tdir/expected.txt"

  local cmd="$EXEC $args"
  # shellcheck disable=SC2086
  if ! bash -c "$cmd" < \"$tdir/input.txt\" > \"$tdir/actual.txt\" 2> \"$tdir/stderr.txt\"; then
    err "[$name] Program exited with non-zero status"
    printf "stderr:\n"
    sed 's/^/  /' "$tdir/stderr.txt"
    echo
    FAILS=$((FAILS+1))
    return
  fi

  if diff -u "$tdir/expected.txt" "$tdir/actual.txt" > "$tdir/diff.txt"; then
    ok "[PASS] $name"
    PASSES=$((PASSES+1))
  else
    err "[FAIL] $name"
    printf "Diff (expected vs actual):\n"
    sed 's/^/  /' "$tdir/diff.txt"
    printf "stderr (if any):\n"
    sed 's/^/  /' "$tdir/stderr.txt"
    echo
    FAILS=$((FAILS+1))
  fi
}

main() {
  EXEC="$(detect_or_build_exec "${1:-}")"
  log "Using executable: $EXEC"
  PASSES=0
  FAILS=0

  # Tests

  # 1. Default lexicographic (case-sensitive)
  run_test "Default lexicographic" "" \
"Zebra
grape
Banana
cherry
Apple
mango
alpha
" \
"Apple
Banana
Zebra
alpha
cherry
grape
mango
"

  # 2. Reverse lexicographic (case-sensitive)
  run_test "Reverse lexicographic" "-r" \
"Zebra
grape
Banana
cherry
Apple
mango
alpha
" \
"mango
grape
cherry
alpha
Zebra
Banana
Apple
"

  # 3. Case-insensitive
  run_test "Case-insensitive" "-f" \
"Zebra
grape
Banana
cherry
Apple
mango
alpha
" \
"alpha
Apple
Banana
cherry
grape
mango
Zebra
"

  # 4. Case-insensitive + reverse
  run_test "Case-insensitive + reverse" "-f -r" \
"Zebra
grape
Banana
cherry
Apple
mango
alpha
" \
"Zebra
mango
grape
cherry
Banana
Apple
alpha
"

  # 5. Numeric sort
  run_test "Numeric sort" "-n" \
"10
2
-3
2.5
-0.5
100
0
" \
"-3
-0.5
0
2
2.5
10
100
"

  # 6. Numeric + reverse
  run_test "Numeric + reverse" "-n -r" \
"10
2
-3
2.5
-0.5
100
0
" \
"100
10
2.5
2
0
-0.5
-3
"

  # Optional sanity checks

  # 7. Empty input
  run_test "Empty input" "" \
"" \
""

  # 8. Single line (with mixed flags)
  run_test "Single line passthrough" "-n -r -f" \
"only-one
" \
"only-one
"

  total=$((PASSES+FAILS))
  echo
  if [[ $FAILS -eq 0 ]]; then
    ok "All $total tests passed."
    exit 0
  else
    err "$FAILS of $total tests failed."
    exit 1
  fi
}

main "$@"