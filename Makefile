SRC_DIR := source
BUILD_DIR := build
TARGET := $(BUILD_DIR)/hash_table.out
HDR_DIR := headers

SRCS := $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(SRC_DIR)/*.c)
HDRS := $(wildcard $(HDR_DIR)/*.h)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

CXX := g++

COMMON_FLAGS := -I$(HDR_DIR) -std=c++17 -Wall -Wextra
VISUAL_FLAGS := $(COMMON_FLAGS) -D_DEBUG -ggdb3 -O3 -msse4.2 -DPROGRAM_MODE=VISUALIZATION_MODE
BENCH_FLAGS := $(COMMON_FLAGS) -DNDEBUG -O3 -msse4.2 -DPROGRAM_MODE=SEARCH_BENCHMARK_MODE
FLAGS := $(VISUAL_FLAGS)	# set default flags for make

.PHONY: all clean visual bench

all: $(TARGET)

visual:
	make clean
	make FLAGS="$(VISUAL_FLAGS)" all

bench:
	make clean
	make FLAGS="$(BENCH_FLAGS)" all

$(TARGET): $(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CXX) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) callgrind.out.*
