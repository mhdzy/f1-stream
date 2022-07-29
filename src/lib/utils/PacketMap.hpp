#pragma once

#include <map>
#include <string>

#include "File.hpp"

struct PacketMap
{
  std::string file_name;
  std::string file_packet_name;
  int file_size;
  int file_id;
};

PacketMap packet_map_populate(std::string filename);
