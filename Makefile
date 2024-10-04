CC = clang
CFLAGS = -Wall -Wextra -Werror -g
#LDFLAGS = -I$(LIB)
LDLIBS= -lreadline

all: main.o
	$(CC) $(CFLAGS) main.o -o ushell $(LDLIBS)

clean:
	$(RM) *.o ushell

re: clean all
