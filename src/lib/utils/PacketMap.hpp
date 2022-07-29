#pragma once

#include <map>
#include <string>

#include "File.hpp"

struct PacketMap
{
  char *file_name;
  const char *file_packet_name;
  int file_size;
  int file_id;
};

PacketMap packet_map_populate(std::string filename);
