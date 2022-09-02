#pragma once

#include <map>
#include <string>

#include "../utils/File.hpp"

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
  std::string file_name;         // used to identify the particular file being described
  std::string file_packet_name;  // internal packet name (given by F1 spec sheet)
  std::size_t file_size;         // size in bytes
  std::uint8_t file_id;          // internal file id number (0-11)
};

extern std::map<int, int> packet_size_to_id;
extern std::map<int, std::string> packet_id_to_string;

PacketMap packet_map_populate(std::string filename);
PacketMap parse_raw_packet(std::uint16_t size);
