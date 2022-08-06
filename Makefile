CC:=g++
CCFLAGS:=-Wall -std=c++17

SDIR:=src
LDIR:=src/lib/include

OBJECTS:= \
	$(SDIR)/main.o \
	$(LDIR)/PacketHeader.o \
	$(LDIR)/PacketMotionData.o \
	$(LDIR)/PacketSessionData.o \
	$(LDIR)/PacketMap.o \
	$(LDIR)/File.o \
	$(LDIR)/Bytes.o

TARGET_EXECUTABLE:= \
	$(SDIR)/main

all: $(TARGET_EXECUTABLE)

%.o: %.cpp
	@echo "compiling $<"
	$(CC) $(CCFLAGS) -c -g $< -o $@

$(TARGET_EXECUTABLE): $(OBJECTS)
	@echo "linking $@"
	$(CC) $(CCFLGAS) $(OBJECTS) -g -o $@

clean:
	@echo "cleaning up"
	rm -f $(OBJECTS) $(TARGET_EXECUTABLE)

run:
	@chmod +x $(TARGET_EXECUTABLE)
	./$(TARGET_EXECUTABLE)
