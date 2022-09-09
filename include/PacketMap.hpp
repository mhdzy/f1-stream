#pragma once

#include <map>
#include <string>

#include "File.hpp"

enum PacketID {
  Motion = 0,               //
  Session = 1,              //
  Lap = 2,                  //
  Event = 3,                //
  Participants = 4,         //
  CarSetups = 5,            //
  CarTelemetry = 6,         //
  CarStatus = 7,            //
  FinalClassification = 8,  //
  LobbyInfo = 9,            //
  CarDamage = 10,           //
  SessionHistory = 11       //
};

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
