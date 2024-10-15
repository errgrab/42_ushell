CC		= clang
NAME	= ushell
CFLAGS	+= -Wall -Wextra -Werror -g
CFLAGS	+= -fsanitize=address
LDFLAGS	+=
LDLIBS	+= -lreadline

all: $(NAME)

$(NAME): main.o
	$(CC) $(CFLAGS) $^ -o $(NAME) $(LDLIBS)

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all
