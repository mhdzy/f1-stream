#include "../include/PacketMap.hpp"

std::map<std::uint8_t, std::uint8_t> packet_size_to_id = {
    {1464, PacketID::Motion},               //
    {632, PacketID::Session},               //
    {972, PacketID::Lap},                   //
    {40, PacketID::Event},                  //
    {1257, PacketID::Participants},         //
    {1102, PacketID::CarSetups},            //
    {1347, PacketID::CarTelemetry},         //
    {1058, PacketID::CarStatus},            //
    {1015, PacketID::FinalClassification},  //
    {1191, PacketID::LobbyInfo},            //
    {948, PacketID::CarDamage},             //
    {1155, PacketID::SessionHistory}        //
};

std::map<std::uint8_t, std::string> packet_id_to_string = {
    {PacketID::Motion, "Motion"},                            //
    {PacketID::Session, "Session"},                          //
    {PacketID::Lap, "LapData"},                              //
    {PacketID::Event, "Event"},                              //
    {PacketID::Participants, "Participants"},                //
    {PacketID::CarSetups, "CarSetups"},                      //
    {PacketID::CarTelemetry, "CarTelemetry"},                //
    {PacketID::CarStatus, "CarStatus"},                      //
    {PacketID::FinalClassification, "FinalClassification"},  //
    {PacketID::LobbyInfo, "LobbyInfo"},                      //
    {PacketID::CarDamage, "CarDamage"},                      //
    {PacketID::SessionHistory, "SessionHistory"}             //
};

PacketMap packet_map_populate(std::string filename) {
  PacketMap map;
  map.file_name = filename;
  map.file_size = file_size(filename);
  map.file_id = packet_size_to_id.find(map.file_size)->second;
  map.file_packet_name = packet_id_to_string.find(map.file_id)->second.c_str();
  return (map);
};

PacketMap parse_raw_packet(std::uint16_t size) {
  PacketMap map;
  map.file_name = "unknown";
  map.file_size = size;
  map.file_id = packet_size_to_id.find(map.file_size)->second;
  map.file_packet_name = packet_id_to_string.find(map.file_id)->second.c_str();
  return map;
}

std::uint8_t packet_loop_limit(std::uint8_t packetid) {
  if (packetid == PacketID::Session || packetid == PacketID::Event) {
    return 0;
  } else if (packetid == PacketID::SessionHistory) {
    return 100;
  } else {
    return 22;
  }
}
