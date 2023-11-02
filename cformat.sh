
find . -type f \( -name '*.h' -o -name '*.hpp' -o -name '*.hh' -o -name '*.ino' -o -name '*.cpp' -o -name '*.c' -o -name '*.cxx' -o -name '*.inl' \) -and -not -path './build/*' -not -path './base/external/*' -not -path './libs/*' | while read file; do
  if [[ "$file" != *"json.hpp" ]]; then
    echo "Formatting $file..."
    clang-format -i --style=Google $file
  fi
done