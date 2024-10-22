CC		= clang
NAME	= ushell
CFLAGS	+= -Wall -Wextra -Werror -g
CFLAGS	+= -fsanitize=address
LDFLAGS	+=
LDLIBS	+= -lreadline
OBJS	= main.o builtin.o parse.o
LIB		= lib/lib0.o lib/lib1.o lib/lib2.o lib/lib3.o lib/lib4.o lib/lib5.o

all: $(LIB) $(NAME)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(LDLIBS)

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all

