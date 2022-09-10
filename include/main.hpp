#pragma once

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <vector>

#include "Bytes.hpp"
#include "File.hpp"
#include "Packet.hpp"
#include "PacketCarDamageData.hpp"
#include "PacketCarSetupData.hpp"
#include "PacketCarStatusData.hpp"
#include "PacketCarTelemetryData.hpp"
#include "PacketEventData.hpp"
#include "PacketFinalClassificationData.hpp"
#include "PacketHeader.hpp"
#include "PacketLapData.hpp"
#include "PacketLobbyInfoData.hpp"
#include "PacketMotionData.hpp"
#include "PacketParticipantsData.hpp"
#include "PacketSessionData.hpp"
#include "PacketSessionHistoryData.hpp"
#include "spdlog/spdlog.h"

#define PORT 20777
#define BUFSIZE 4096

const bool DEBUG = false;

std::vector<std::string> RAW_NAMES;       // raw input files (for batch mode)
std::vector<std::string> OUTPUT_NAMES;    // output string names
std::vector<std::ofstream> OUTPUT_FILES;  // vector of writeable output files

void printPacket(std::uint8_t packetid, auto obj, bool debug);

void parseAndPrintPacket(std::vector<unsigned char> bytes, bool debug);

template <class T>
void printHeader(std::uint8_t packetid, std::string prefix);

void printHeaders();

/**
 * @brief
 *
 * @note regex to replace std::int types (std::[u]*int[\d]{1,2}_t)
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char **argv);
