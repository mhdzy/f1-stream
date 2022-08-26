CC:=g++
CCFLAGS:=-Wall -std=c++17

SDIR:=src
LDIR:=src/lib/include

INC=/usr/local/include
INC_DIRS = $(addprefix -I,$(INC))

OBJECTS:= \
	$(SDIR)/main.o \
	$(LDIR)/PacketCarSetupData.o \
	$(LDIR)/PacketCarStatusData.o \
	$(LDIR)/PacketCarTelemetryData.o \
	$(LDIR)/PacketEventData.o \
	$(LDIR)/PacketHeader.o \
	$(LDIR)/PacketLapData.o \
	$(LDIR)/PacketMap.o \
	$(LDIR)/PacketMotionData.o \
	$(LDIR)/PacketParticipantsData.o \
	$(LDIR)/PacketSessionData.o \
	$(LDIR)/File.o \
	$(LDIR)/Bytes.o

TARGET_EXECUTABLE:= \
	$(SDIR)/main

all: $(TARGET_EXECUTABLE)

%.o: %.cpp
	@echo "compiling $<"
	$(CC) $(CCFLAGS) -c -g $(INC_DIRS) $< -o $@

$(TARGET_EXECUTABLE): $(OBJECTS)
	@echo "linking $@"
	$(CC) $(CCFLGAS) $(OBJECTS) -g -o $@

clean:
	@echo "cleaning up"
	rm -f $(OBJECTS) $(TARGET_EXECUTABLE)

run:
	@chmod +x $(TARGET_EXECUTABLE)
	./$(TARGET_EXECUTABLE)

trim:
	@echo "cleaning object files"
	rm -f $(OBJECTS)