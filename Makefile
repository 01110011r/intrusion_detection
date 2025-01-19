# Kompilyator va flaglar
CC = gcc
CFLAGS = -Icore/include -I/usr/include/postgresql -Wall -Wextra -g
LDFLAGS = -L/usr/lib -lpq

# Papka strukturalari
SRC_DIR = core/src
BUILD_DIR = core/build
BIN_DIR = core/bin
TARGET = $(BIN_DIR)/ids

# Fayllar
SRC = $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

# Default target
all: $(TARGET)

# Binar fayl yaratish
$(TARGET): $(OBJ)
	mkdir -p $(BIN_DIR)
	$(CC) -o $@ $^ $(LDFLAGS)

# Har bir .c fayldan .o faylni yaratish
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Tozalash
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean
