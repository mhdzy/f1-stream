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

#include "packets/PacketCarDamageData.hpp"
#include "packets/PacketCarSetupData.hpp"
#include "packets/PacketCarStatusData.hpp"
#include "packets/PacketCarTelemetryData.hpp"
#include "packets/PacketEventData.hpp"
#include "packets/PacketFinalClassificationData.hpp"
#include "packets/PacketHeader.hpp"
#include "packets/PacketLapData.hpp"
#include "packets/PacketLobbyInfoData.hpp"
#include "packets/PacketMap.hpp"
#include "packets/PacketMotionData.hpp"
#include "packets/PacketParticipantsData.hpp"
#include "packets/PacketSessionData.hpp"
#include "packets/PacketSessionHistoryData.hpp"
#include "spdlog/spdlog.h"
#include "utils/Bytes.hpp"
#include "utils/File.hpp"

/**
 * @brief
 *
 * @note regex to replace std::int types (std::[u]*int[\d]{1,2}_t)
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char** argv);
