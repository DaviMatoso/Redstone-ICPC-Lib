/*LATEX_DESC_BEGIN************************
g++ "$1.cpp" -o "$1" -Wall -Wextra -O2 -Wshadow -fsanitize=address,undefined
g++ "$1.cpp" -o "$1" -Wall -Wextra -Wshadow -O1 -g -fno-omit-frame-pointer -fsanitize=address,undefined
***************************LATEX_DESC_END*/