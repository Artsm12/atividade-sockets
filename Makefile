CXX      := g++
CXXFLAGS := -std=c++20 -pthread -Iinclude -MMD -MP

SRC_DIR  := src
OBJ_DIR  := objs
DOCS_DIR  = docs

TARGET_SERVER := server
TARGET_CLIENT := client

SRCS_SERVER := $(wildcard $(SRC_DIR)/server/*.cpp)
SRCS_CLIENT := $(wildcard $(SRC_DIR)/client/*.cpp)
SRCS_UTILS  := $(SRC_DIR)/thread_pool.cpp

OBJS_SERVER := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS_SERVER))
OBJS_CLIENT := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS_CLIENT))
OBJS_UTILS  := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS_UTILS))

DEPS := $(OBJS_SERVER:.o=.d) $(OBJS_CLIENT:.o=.d) $(OBJS_UTILS:.o=.d)

all: $(TARGET_SERVER) $(TARGET_CLIENT)

$(TARGET_SERVER): $(OBJS_SERVER) $(OBJS_UTILS)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Servidor compilado -> ./$(TARGET_SERVER)"

$(TARGET_CLIENT): $(OBJS_CLIENT)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Cliente compilado -> ./$(TARGET_CLIENT)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(OBJ_DIR) $(TARGET_SERVER) $(TARGET_CLIENT) $(DOCS_DIR)

docs:
	@doxygen Doxyfile

.PHONY: all clean docs