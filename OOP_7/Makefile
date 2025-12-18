CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Все исходные файлы
SRCS = $(SRC_DIR)/npc.cpp $(SRC_DIR)/game_world.cpp $(SRC_DIR)/main.cpp
# Соответствующие объектные файлы
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
TARGET = $(BIN_DIR)/dungeon_game

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Правило для компиляции .cpp в .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run