#pragma once

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <vector>

#include "lib/include/Bytes.hpp"
#include "lib/include/File.hpp"
#include "lib/include/PacketMap.hpp"

/*
#include "lib/include/PacketCarDamageData.hpp"
#include "lib/include/PacketFinalClassificationData.hpp"
#include "lib/include/PacketLobbyInfoData.hpp"
#include "lib/include/PacketSessionHistoryData.hpp"
*/

#include "lib/include/PacketCarSetupData.hpp"
#include "lib/include/PacketCarStatusData.hpp"
#include "lib/include/PacketCarTelemetryData.hpp"
#include "lib/include/PacketEventData.hpp"
#include "lib/include/PacketHeader.hpp"
#include "lib/include/PacketLapData.hpp"
#include "lib/include/PacketMotionData.hpp"
#include "lib/include/PacketParticipantsData.hpp"
#include "lib/include/PacketSessionData.hpp"

/*
  spdlog::info debug warn error critical
*/
#include "spdlog/spdlog.h"

/*
  given a track:
    assumes data is stored at
      data/{track}/raw/
    code will store packet files to
      data/{track}/parsed/
*/
const std::string TRACK = "portugal-prac";
const std::string DATA_PATH = "data/";
const std::string LOG_DATA_PATH = DATA_PATH + TRACK + "/logs/";
const std::string RAW_DATA_PATH = DATA_PATH + TRACK + "/raw/";
const std::string OUT_DATA_PATH = DATA_PATH + TRACK + "/parsed/";

// note: there are a total of 12 packet types
const std::vector<std::uint8_t> IMPLEMENTED_PACKET_IDS = {
    0,  // motion data
    1,  // session data
    2,  // lap data
    3,  // event data
    4,  // participants data
    5,  // (car) setup
    6,  // (car) telemetry
    7   // (car) status
};

const bool DEBUG = false;

/**
 * @brief
 *
 * @note regex to replace std::int types (std::[u]*int[\d]{1,2}_t)
 *
 * @return int
 */

int main();
