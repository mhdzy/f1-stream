#include "PacketHeader.hpp"

void PrintPacketHeader(PacketHeader ph) {
  printf("PacketHeader\n");
  printf("m_packetFormat: %d\n", ph.m_packetFormat);
  printf("m_gameMajorVersion: %d\n", ph.m_gameMajorVersion);
  printf("m_gameMinorVersion: %d\n", ph.m_gameMinorVersion);
  printf("m_packetVersion: %d\n", ph.m_packetVersion);
  printf("m_packetId: %d\n", ph.m_packetId);
  printf("m_sessionUID: %llu\n", ph.m_sessionUID);
  printf("m_sessionTime: %f\n", ph.m_sessionTime);
  printf("m_frameIdentifier: %d\n", ph.m_frameIdentifier);
  printf("m_playerCarIndex: %d\n", ph.m_playerCarIndex);
  printf("m_secondaryPlayerCarIndex: %d\n", ph.m_secondaryPlayerCarIndex);
};

PacketHeader ParsePacketHeader(std::vector<std::vector<unsigned char>> bytes) {
  PacketHeader ph;
  std::memcpy(&ph.m_packetFormat, &bytes.at(0).front(), sizeof(std::uint16_t));
  std::memcpy(&ph.m_gameMajorVersion, &bytes.at(1).front(), sizeof(std::uint8_t));
  std::memcpy(&ph.m_gameMinorVersion, &bytes.at(2).front(), sizeof(std::uint8_t));
  std::memcpy(&ph.m_packetVersion, &bytes.at(3).front(), sizeof(std::uint8_t));
  std::memcpy(&ph.m_packetId, &bytes.at(4).front(), sizeof(std::uint8_t));
  std::memcpy(&ph.m_sessionUID, &bytes.at(5).front(), sizeof(std::uint64_t));
  std::memcpy(&ph.m_sessionTime, &bytes.at(6).front(), sizeof(float));
  std::memcpy(&ph.m_frameIdentifier, &bytes.at(7).front(), sizeof(std::uint32_t));
  std::memcpy(&ph.m_playerCarIndex, &bytes.at(8).front(), sizeof(std::uint8_t));
  std::memcpy(&ph.m_secondaryPlayerCarIndex, &bytes.at(9).front(), sizeof(std::uint8_t));
  return (ph);
};

std::vector<std::pair<int, std::string>> PacketHeaderPairs = {
    std::make_pair(sizeof(std::uint16_t), "m_packetFormat"),  // 2022
    std::make_pair(sizeof(std::uint8_t),
                   "m_gameMajorVersion"),  // Game major version - "X.00"
    std::make_pair(sizeof(std::uint8_t),
                   "m_gameMinorVersion"),  // Game minor version - "1.XX"
    std::make_pair(sizeof(std::uint8_t),
                   "m_packetVersion"),  // Version of this packet type, all start from 1
    std::make_pair(sizeof(std::uint8_t),
                   "m_packetId"),  // Identifier for the packet type, see below
    std::make_pair(sizeof(std::uint64_t),
                   "m_sessionUID"),                  // Unique identifier for the session
    std::make_pair(sizeof(float), "m_sessionTime"),  // Session timestamp
    std::make_pair(sizeof(std::uint32_t),
                   "m_frameIdentifier"),  // Identifier for the frame the data
                                          // was retrieved on
    std::make_pair(sizeof(std::uint8_t),
                   "m_playerCarIndex"),  // Index of player's car in the array
    std::make_pair(sizeof(std::uint8_t),
                   "m_secondaryPlayerCarIndex")  // Index of secondary player's car in the
                                                 // array (splitscreen), 255 if no second
                                                 // player
};
