CC := g++
CCFLAGS := -Wall -std=c++17

# need to set '-lstdc++fs' on linux, breaks macOS builds
OS_NAME := $(shell uname -s | tr A-Z a-z)
OS_FLAGS :=
ifeq ($(OS_NAME), "linux")
	OS_FLAGS += -lstdc++fs
endif

BUILD_DIR   := build
INCLUDE_DIR := include
SOURCE_DIR  := src

TARGET := main

# some included libraries (spdlog)
INC := /usr/local/include $(CURDIR)/$(INCLUDE_DIR)
INC_LIBS := $(addprefix -I,$(INC))

# auto-detect source .cpp files and derive .o names
# assumes corresponding .hpp files exist in the $(INCLUDE_DIR)
SOURCES := $(wildcard $(SOURCE_DIR)/*.cpp)
OBJECTS := $(patsubst $(SOURCE_DIR)/%,%,$(SOURCES))
OBJECTS := $(patsubst %.cpp,%.o,$(OBJECTS))
OBJECTS := $(addprefix $(BUILD_DIR)/,$(OBJECTS))

# setup 'make run' args
ifeq (run, $(firstword $(MAKECMDGOALS)))
  # use the rest as arguments for "run"
  RUN_ARGS := $(wordlist 2, $(words $(MAKECMDGOALS)), $(MAKECMDGOALS))
  # ...and turn them into do-nothing targets
  $(eval $(RUN_ARGS):;@:)
endif

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "linking $@"
	$(CC) $(CCFLAGS) $(OBJECTS) -g -o $@ $(INC_LIBS) $(OS_FLAGS)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@printf "%s\n" "compiling $<"
	$(CC) $(CCFLAGS) -c -g $(INC_DIRS) $< -o $@

clean:
	@printf "%s\n" "cleaning up"
	rm -f $(OBJECTS) $(TARGET)

trim:
	@echo "cleaning object files"
	rm -f $(OBJECTS)

run:
	@printf "%s\n" "prog $(RUN_ARGS)"
	@chmod +x $(TARGET)
	./$(TARGET) $(RUN_ARGS)


.PHONY: clean run trim
