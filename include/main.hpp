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
#include "PacketCarDamageData.hpp"
#include "PacketCarSetupData.hpp"
#include "PacketCarStatusData.hpp"
#include "PacketCarTelemetryData.hpp"
#include "PacketEventData.hpp"
#include "PacketFinalClassificationData.hpp"
#include "PacketHeader.hpp"
#include "PacketLapData.hpp"
#include "PacketLobbyInfoData.hpp"
#include "PacketMap.hpp"
#include "PacketMotionData.hpp"
#include "PacketParticipantsData.hpp"
#include "PacketSessionData.hpp"
#include "PacketSessionHistoryData.hpp"
#include "spdlog/spdlog.h"

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
