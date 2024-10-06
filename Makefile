CC = clang
CFLAGS = -Wall -Wextra -Werror -g
#LDFLAGS = -I$(LIB)
LDLIBS = -lreadline
NAME = ushell

all: main.o
	$(CC) $(CFLAGS) main.o -o $(NAME) $(LDLIBS)

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

re: fclean all
