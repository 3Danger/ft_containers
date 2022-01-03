NAME_APP=Containers
CC=clang++
FLAGS=-Wall -Werror -Wextra -Wshadow -g
HEADERS=./ ./utils/
CPP=./main.cpp

all: $(NAME_APP)

$(NAME_APP):
	$(CC) $(FLAGS) $(CPP) $(addprefix -I, $(HEADERS)) -o $@
clean:
	rm $(NAME_APP)
re:
	rm $(NAME_APP)
	@make -C ./