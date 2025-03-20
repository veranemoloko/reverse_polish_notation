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

clang-format:
	@echo "\n\033[0;34mmake clang-format\033[0m"
	find . -type f \( -name "*.c" -o -name "*.h" \) -exec clang-format -style=file -n {} +

cppcheck:
	@echo "\n\033[0;34mmake cppcheck\033[0m"
	cppcheck --enable=all --suppress=missingIncludeSystem src/

run:
	@echo "\n\033[0;34mmake run (using valgrind):\033[0m"
	valgrind --tool=memcheck --leak-check=yes ./$(TARGET)


.PHONY: all clean cppchek
