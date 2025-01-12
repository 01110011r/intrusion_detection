CC = gcc
CFLAGS = -Icore/include -Wall
SRC_DIR = core/src
BUILD_DIR = core/build
BIN_DIR = core/bin
TARGET = $(BIN_DIR)/ids

SRC = $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC))

all: $(TARGET)

# Binar fayl yaratish
$(TARGET): $(OBJ)
	mkdir -p $(BIN_DIR)
	$(CC) -o $@ $^

# Har bir .c fayldan .o faylni yaratish
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean
