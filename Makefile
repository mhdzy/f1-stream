CC := g++
CCFLAGS := -Wall -std=c++17

SOURCE_DIR  := src
UTILS_DIR   := src/utils
PACKETS_DIR := src/packets

INC := /usr/local/include $(UTILS_DIR) $(PACKET_DIR)
INC_LIBS := $(addprefix -I,$(INC))

OBJECTS := \
	$(SOURCE_DIR)/main.o \
	$(PACKETS_DIR)/PacketCarDamageData.o \
	$(PACKETS_DIR)/PacketCarSetupData.o \
	$(PACKETS_DIR)/PacketCarStatusData.o \
	$(PACKETS_DIR)/PacketCarTelemetryData.o \
	$(PACKETS_DIR)/PacketEventData.o \
	$(PACKETS_DIR)/PacketFinalClassificationData.o \
	$(PACKETS_DIR)/PacketHeader.o \
	$(PACKETS_DIR)/PacketLapData.o \
	$(PACKETS_DIR)/PacketLobbyInfoData.o \
	$(PACKETS_DIR)/PacketMap.o \
	$(PACKETS_DIR)/PacketMotionData.o \
	$(PACKETS_DIR)/PacketParticipantsData.o \
	$(PACKETS_DIR)/PacketSessionData.o \
	$(PACKETS_DIR)/PacketSessionHistoryData.o \
	$(UTILS_DIR)/File.o \
	$(UTILS_DIR)/Bytes.o

TARGET := \
	$(SOURCE_DIR)/main

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
	$(CC) $(CCFLGAS) $(OBJECTS) -g -o $@ $(INC_LIBS)

%.o: %.cpp
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
