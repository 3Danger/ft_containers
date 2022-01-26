#!/bin/sh

rm -rf test_container
rm -rf test_container_std

#clear; 
//usr/bin/clang++ -Wall -Werror -Wextra -g -I. -D_GLIBCXX_DEBUG main.cpp -o test_container;
//usr/bin/clang++ -Wall -Werror -Wextra -g -I. -D_GLIBCXX_DEBUG -D=STD main.cpp -o test_container_std;

./test_container > FT_VECTOR
./test_container_std > STD_VECTOR
