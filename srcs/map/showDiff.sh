#!/bin/bash

clear
clang++ ../ColourConsole.hpp -g -D_GLIBCXX_DEBUG Comparator.hpp pair.hpp Visualize.hpp map.hpp main.cpp && ./a.out > 1
clang++ ../ColourConsole.hpp -g -D=ER -D_GLIBCXX_DEBUG Comparator.hpp pair.hpp Visualize.hpp map.hpp main.cpp && ./a.out > 2

diff 1 2

rm 1 2 a.out