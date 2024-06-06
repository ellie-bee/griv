CC = gcc
CFLAGS = -Wall -Wextra -Werror -ggdb -lm

SRC_DIR = src
BIN_DIR = bin
BUILD_DIR = build

SRCS = $(shell find $(SRC_DIR) -name '*.c')
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

GRIVC_OBJS = $(filter-out $(BUILD_DIR)/grivc_test.o, $(OBJS))
GRIVC_TEST_OBJS = $(filter-out $(BUILD_DIR)/grivc.o, $(OBJS))

GRIVC = $(BIN_DIR)/grivc
GRIVC_TEST = $(BIN_DIR)/grivc_test

.PHONY: all clean run test
all: $(GRIVC) $(GRIVC_TEST)

clean:
	rm -rf $(BIN_DIR) $(BUILD_DIR)

run: $(GRIVC)
	$(GRIVC)

test: $(GRIVC_TEST) $(GRIVC)
	$(GRIVC_TEST) 

$(GRIVC): $(GRIVC_OBJS)
	@mkdir -p $(BIN_DIR) $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(GRIVC_TEST): $(GRIVC_TEST_OBJS)
	@mkdir -p $(BIN_DIR) $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


