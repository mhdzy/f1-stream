#pragma once

#include <map>
#include <string>

#include "File.hpp"

#define MotionPacketID 0
#define SessionPacketID 1
#define LapDataPacketID 2
#define EventPacketID 3
#define ParticipantsPacketID 4
#define CarSetupsPacketID 5
#define CarTelemetryPacketID 6
#define CarStatusPacketID 7
#define FinalClassificationPacketID 8
#define LobbyInfoPacketID 9
#define CarDamagePacketID 10
#define SessionHistoryPacketID 11

struct PacketMap {
  std::string file_name;
  std::string file_packet_name;
  int file_size;
  int file_id;
};

extern std::map<int, int> packet_size_to_id;
extern std::map<int, std::string> packet_id_to_string;

PacketMap packet_map_populate(std::string filename);
