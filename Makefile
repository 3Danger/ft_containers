NAME=test_container

all: $(NAME)

CC=clang++
CFLAGS=-Wall -Werror -Wextra -I. -g

$(NAME): $(wildcard *.cpp *.hpp)
	$(CC) $(CFLAGS) $(wildcard *.cpp) -o $@
	