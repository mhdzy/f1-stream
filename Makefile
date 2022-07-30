CC:=g++
CCFLAGS:=-Wall -std=c++17

SDIR:=src
LDIR:=src/lib/include
UDIR:=src/lib/utils

OBJECTS:=$(SDIR)/main.o $(LDIR)/PacketHeader.o $(LDIR)/PacketMotionData.o $(UDIR)/PacketMap.o $(UDIR)/File.o $(UDIR)/Maps.o $(UDIR)/Pairs.o
TARGET_EXECUTABLE:=$(SDIR)/main

all: ${TARGET_EXECUTABLE}

%.o: %.cpp
	@echo "compiling $<"
	$(CC) $(CCFLAGS) -c -g $< -o $@

${TARGET_EXECUTABLE}: ${OBJECTS}
	@echo "linking $@"
	$(CC) $(CCFLGAS) ${OBJECTS} -g -o $@

clean:
	@echo "cleaning up"
	rm -f ${OBJECTS} ${TARGET_EXECUTABLE}

run:
	@chmod +x ${TARGET_EXECUTABLE}
	./${TARGET_EXECUTABLE}
