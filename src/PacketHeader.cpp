#include "../include/PacketHeader.hpp"

template <>
std::vector<std::size_t> pSizes<PacketHeader>() {
  std::vector<std::size_t> vec = {
      sizeof(((PacketHeader *)0)->m_packetFormat),            // 2022
      sizeof(((PacketHeader *)0)->m_gameMajorVersion),        // Game major version - "X.00"
      sizeof(((PacketHeader *)0)->m_gameMinorVersion),        // Game minor version - "1.XX"
      sizeof(((PacketHeader *)0)->m_packetVersion),           // Version of this packet type, all start from 1
      sizeof(((PacketHeader *)0)->m_packetId),                // Identifier for the packet type, see below
      sizeof(((PacketHeader *)0)->m_sessionUID),              // Unique identifier for the session
      sizeof(((PacketHeader *)0)->m_sessionTime),             // Session timestamp
      sizeof(((PacketHeader *)0)->m_frameIdentifier),         // Identifier for the frame the data was retrieved on
      sizeof(((PacketHeader *)0)->m_playerCarIndex),          // Index of player's car in the array
      sizeof(((PacketHeader *)0)->m_secondaryPlayerCarIndex)  // Index of secondary player's car in the array
                                                              // (splitscreen), 255 if no second player
  };
  return vec;
}

template <>
std::vector<std::string> pNames<PacketHeader>() {
  std::vector<std::string> vec = {
      "m_packetFormat",            // 2022
      "m_gameMajorVersion",        // Game major version - "X.00"
      "m_gameMinorVersion",        // Game minor version - "1.XX"
      "m_packetVersion",           // Version of this packet type", all start from 1
      "m_packetId",                // Identifier for the packet type", see below
      "m_sessionUID",              // Unique identifier for the session
      "m_sessionTime",             // Session timestamp
      "m_frameIdentifier",         // Identifier for the frame the data was retrieved on
      "m_playerCarIndex",          // Index of player's car in the array
      "m_secondaryPlayerCarIndex"  // Index of secondary player's car in the array
                                   // (splitscreen), 255 if no second player
  };
  return vec;
}

template <>
std::string subpacketDataString(PacketHeader obj, std::string sep) {
  const char *fmt = "%d%s%d%s%d%s%d%s%d%s%llu%s%f%s%d%s%d%s%d";
  const char *ssep = sep.c_str();

  std::size_t size =
      std::snprintf(nullptr, 0, fmt, obj.m_packetFormat, ssep, obj.m_gameMajorVersion, ssep, obj.m_gameMinorVersion,
                    ssep, obj.m_packetVersion, ssep, obj.m_packetId, ssep, obj.m_sessionUID, ssep, obj.m_sessionTime,
                    ssep, obj.m_frameIdentifier, ssep, obj.m_playerCarIndex, ssep, obj.m_secondaryPlayerCarIndex);

  std::vector<char> buf(size + 1);  // note +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.m_packetFormat, ssep, obj.m_gameMajorVersion, ssep,
                obj.m_gameMinorVersion, ssep, obj.m_packetVersion, ssep, obj.m_packetId, ssep, obj.m_sessionUID, ssep,
                obj.m_sessionTime, ssep, obj.m_frameIdentifier, ssep, obj.m_playerCarIndex, ssep,
                obj.m_secondaryPlayerCarIndex);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));  // remove null terminator

  return str;
}

template <>
PacketHeader parseSubpacketData<PacketHeader>(std::vector<std::vector<unsigned char>> bytes) {
  PacketHeader obj;
  std::memcpy(&obj.m_packetFormat, &bytes.at(0).front(), sizeof obj.m_packetFormat);
  std::memcpy(&obj.m_gameMajorVersion, &bytes.at(1).front(), sizeof obj.m_gameMajorVersion);
  std::memcpy(&obj.m_gameMinorVersion, &bytes.at(2).front(), sizeof obj.m_gameMinorVersion);
  std::memcpy(&obj.m_packetVersion, &bytes.at(3).front(), sizeof obj.m_packetVersion);
  std::memcpy(&obj.m_packetId, &bytes.at(4).front(), sizeof obj.m_packetId);
  std::memcpy(&obj.m_sessionUID, &bytes.at(5).front(), sizeof obj.m_sessionUID);
  std::memcpy(&obj.m_sessionTime, &bytes.at(6).front(), sizeof obj.m_sessionTime);
  std::memcpy(&obj.m_frameIdentifier, &bytes.at(7).front(), sizeof obj.m_frameIdentifier);
  std::memcpy(&obj.m_playerCarIndex, &bytes.at(8).front(), sizeof obj.m_playerCarIndex);
  std::memcpy(&obj.m_secondaryPlayerCarIndex, &bytes.at(9).front(), sizeof obj.m_secondaryPlayerCarIndex);
  return obj;
}
