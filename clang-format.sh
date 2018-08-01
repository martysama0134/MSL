find . -regex '.*\.\(cpp\|h\|hpp\|cc\|c\)' -exec clang-format -style=file -verbose -i {} \;
