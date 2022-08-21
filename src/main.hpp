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
#include "lib/include/PacketCarSetupData.hpp"
#include "lib/include/PacketCarTelemetryData.hpp"
#include "lib/include/PacketCatStatusData.hpp"
#include "lib/include/PacketEventData.hpp"
#include "lib/include/PacketFinalClassificationData.hpp"
*/

#include "lib/include/PacketHeader.hpp"
#include "lib/include/PacketMotionData.hpp"
#include "lib/include/PacketSessionData.hpp"

/*
#include "lib/include/PacketLapData.hpp"
#include "lib/include/PacketLobbyInfoData.hpp"
#include "lib/include/PacketParticipantsData.hpp"
#include "lib/include/PacketSessionHistoryData.hpp"
*/

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
const std::string TRACK = "singapore";
const std::string DATA_PATH = "data/";
const std::string LOG_DATA_PATH = DATA_PATH + TRACK + "/logs/";
const std::string RAW_DATA_PATH = DATA_PATH + TRACK + "/raw/";
const std::string OUT_DATA_PATH = DATA_PATH + TRACK + "/parsed/";

const std::vector<std::uint8_t> IMPLEMENTED_PACKET_IDS = {0, 1};

/**
 * @brief
 *
 * @note regex to replace std::int types (std::[u]*int[\d]{1,2}_t)
 *
 * @return int
 */

int main();
