find . -type f \( -iname \*.cpp -o -iname \*.h -o -iname \*.hpp -o -iname \*.cc -o -iname \*.c \) -exec clang-format -style=file -verbose -i {} \;
