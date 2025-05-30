CC = gcc
CFLAGS = -Wall -Wextra -g

SRC = main.c server.c config.c request.c response.c utils.c
OBJ = $(SRC:.c=.o)
DEPS = server.h config.h request.h response.h utils.h

TARGET = myserver

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o $(TARGET)
