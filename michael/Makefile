BIN_DIR := bin
OBJ_DIR := obj
SRC_DIR := src
SRC_EXT := cpp
BIN := $(BIN_DIR)/AdventOfCode
INCLUDES := -I.
CXXSTD := -std=c++17
CXXFLAGS := -Wall -Wextra -Wpedantic $(CXXSTD) -MMD -g
SRC = $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
OBJ = $(SRC:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/%.o)
DEPS = $(OBJ:.o=.d)

MAKE_DIR = @mkdir -p $(@D)

.PHONY: all build
all:
	@$(MAKE) -j --no-print-directory build

build: $(BIN)

-include $(DEPS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	$(MAKE_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@

$(BIN): $(OBJ)
	$(MAKE_DIR)
	$(CXX) $(OBJ) -o $@

.PHONY: clean docs
docs: Doxyfile $(SRC)
	doxygen Doxyfile

clean:
	$(RM) $(BIN) $(OBJ) $(DEPS)
