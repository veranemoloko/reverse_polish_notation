CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g
SRC_DIR = src
SRC = $(SRC_DIR)/graph.c $(SRC_DIR)/input.c $(SRC_DIR)/validate.c $(SRC_DIR)/tokens.c \
      $(SRC_DIR)/numbers.c $(SRC_DIR)/stack.c $(SRC_DIR)/units.c $(SRC_DIR)/draw.c \
      $(SRC_DIR)/calculate.c $(SRC_DIR)/errType.c
OBG = $(SRC:.c=.o)
TARGET = graph

all: $(TARGET)

$(TARGET) : $(OBG)
	$(CC) $(OBG) -o $(TARGET) -lm
	

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBG) $(TARGET)

rebuild: clean all

.PHONY: all clean
