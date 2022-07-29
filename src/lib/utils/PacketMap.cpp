#include "PacketMap.hpp"

std::map<int, int> packet_size_to_id = {
    {1464, 0},
    {632, 1},
    {972, 2},
    {40, 3},
    {1257, 4},
    {1102, 5},
    {1347, 6},
    {1058, 7},
    {1015, 8},
    {1191, 9},
    {948, 10},
    {1155, 11}};

std::map<int, std::string> packet_id_to_string = {
    {0, "Motion"},
    {1, "Session"},
    {2, "LapData"},
    {3, "Event"},
    {4, "Participants"},
    {5, "CarSetups"},
    {6, "CarTelemetry"},
    {7, "CarStatus"},
    {8, "FinalClassification"},
    {9, "LobbyInfo"},
    {10, "CarDamage"},
    {11, "SessionHistory"}};

PacketMap packet_map_populate(std::string filename)
{
  PacketMap map;
  map.file_name = (char *)filename.c_str();
  map.file_size = (int)file_size(filename.c_str());
  map.file_id = packet_size_to_id.find(map.file_size)->second;
  map.file_packet_name = packet_id_to_string.find(map.file_id)->second.c_str();
  return (map);
};
