CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests

SRCS = $(SRC_DIR)/main.cpp \
       $(SRC_DIR)/NPC.cpp \
       $(SRC_DIR)/NPCFactory.cpp \
       $(SRC_DIR)/BattleVisitor.cpp \
       $(SRC_DIR)/Observer.cpp \
       $(SRC_DIR)/DungeonEditor.cpp

OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TARGET = $(BIN_DIR)/dungeon_editor

TEST_SRC = $(TEST_DIR)/test_npc.cpp
TEST_TARGET = $(BIN_DIR)/test_npc

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(filter-out $(OBJ_DIR)/main.o, $(OBJS)) $(OBJ_DIR)/test_npc.o
	$(CXX) $(CXXFLAGS) $^ -o $@ -lgtest -lgtest_main -pthread

$(OBJ_DIR)/test_npc.o: $(TEST_SRC)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) log.txt

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run test