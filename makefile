TARGET_EXEC ?= apprentissage

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

CC   := clang++-6.0

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS)) -Iinclude

WARNING  := -pedantic -Wall -Wextra -Wold-style-cast -Woverloaded-virtual -Wfloat-equal -Wwrite-strings -Wpointer-arith -Wcast-qual -Wcast-align -Wconversion -Wshadow -Weffc++ -Wredundant-decls -Wdouble-promotion -Winit-self -Wswitch-default -Wswitch-enum -Wundef -Wlong-long -Winline
LIBS := -lsfml-system -lsfml-window -lsfml-graphics

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -std=c++14


release: CPPFLAGS += -O2 -Wall
release: $(TARGET_EXEC)

debug: CPPFLAGS += -g -DDEBUG $(WARNING)
debug: $(TARGET_EXEC)

test:  clean
	echo "BUILD DE TEST"
	$(CC) $(CPPFLAGS) $(CXXFLAGS) test.cpp -o test

$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS)

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) $(TARGET_EXEC)

-include $(DEPS)

MKDIR_P ?= mkdir -p
