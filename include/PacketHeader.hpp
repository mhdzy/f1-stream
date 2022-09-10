#pragma once

#include <cstdint>
#include <cstring>
#include <map>
#include <string>
#include <vector>

#include "Packet.hpp"

#pragma pack(push, 1)

struct PacketHeader {
  std::uint16_t m_packetFormat;            // 2022
  std::uint8_t m_gameMajorVersion;         // Game major version - "X.00"
  std::uint8_t m_gameMinorVersion;         // Game minor version - "1.XX"
  std::uint8_t m_packetVersion;            // Version of this packet type, all start from 1
  std::uint8_t m_packetId;                 // Identifier for the packet type, see below
  std::uint64_t m_sessionUID;              // Unique identifier for the session
  float m_sessionTime;                     // Session timestamp
  std::uint32_t m_frameIdentifier;         // Identifier for the frame the data was retrieved on
  std::uint8_t m_playerCarIndex;           // Index of player's car in the array
  std::uint8_t m_secondaryPlayerCarIndex;  // Index of secondary player's car in the array
                                           // (splitscreen) 255 if no second player
};

#pragma pack(pop)

template <>
std::vector<std::size_t> pSizes<PacketHeader>();

template <>
std::vector<std::string> pNames<PacketHeader>();

template <>
std::string subpacketDataString(PacketHeader obj, std::string sep);

template <>
PacketHeader parseSubpacketData<PacketHeader>(std::vector<std::vector<unsigned char>> bytes);
