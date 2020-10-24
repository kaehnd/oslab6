TARGET_EXEC ?= a.out

BUILD_DIR ?= ./build
SRC_DIR ?= ./src
INC_DIR ?= ./inc

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)
LDFLAGS ?= -pthread

FLAGS ?= -I$(INC_DIR) -Wall -Wextra -g -std=gnu99 

all: ./build/tester ./build/experiment

./build/tester: $(OBJS)
	$(CC) $(BUILD_DIR)/src/memory_manager_tester.c.o $(BUILD_DIR)/src/memory_manager.c.o $(BUILD_DIR)/src/testHelper.c.o -o $@ $(LDFLAGS)

./build/experiment: $(OBJS)
	$(CC) $(BUILD_DIR)/src/memory_experiment.c.o $(BUILD_DIR)/src/memory_manager.c.o $(BUILD_DIR)/src/testHelper.c.o -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

-include $(DEPS)
