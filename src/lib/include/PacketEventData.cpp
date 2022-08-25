
#include "PacketEventData.hpp"

#include "File.hpp"

std::vector<std::size_t> EventDataDetailsSizes = {

};
std::vector<std::string> EventDataDetailsNames = {

};

std::string EventDataDetailsString(EventDataDetails obj, std::string sep) {
  std::string str = "";
  return str;
}
EventDataDetails ParseEventDataDetails(std::vector<std::vector<unsigned char>> bytes) {
  EventDataDetails obj;
  return obj;
}

std::string PacketEventDataCSVHeader(std::string sep, std::string compr) {
  std::string str = "";

  return str;
}

std::string PacketEventDataString(PacketEventData obj, std::string sep) {
  std::string str = "";
  return str;
}

PacketEventData ParsePacketEventData(std::vector<unsigned char> bytes) {
  PacketEventData obj;
  std::uint16_t offset = 0;

  obj.m_header = ParsePacketHeader(parse_bytes_to_vec(PacketHeaderSizes, bytes, offset));
  offset += sizeof(PacketHeader);

  // extract packet type
  for (std::uint8_t i : {0, 1, 2, 3})
    // don't use "&bytes.at().front()" since it's only a 1d vector (not 2d)
    std::memcpy(&obj.m_eventStringCode[i], &bytes.at(offset) + (i * sizeof obj.m_eventStringCode[i]),
                sizeof obj.m_eventStringCode[i]);
  offset += sizeof obj.m_eventStringCode;

  // print testing
  printf("%d %d %d %d\n", obj.m_eventStringCode[0], obj.m_eventStringCode[1], obj.m_eventStringCode[2],
         obj.m_eventStringCode[3]);

  printf("%s\n", obj.m_eventStringCode);

  return obj;
}
