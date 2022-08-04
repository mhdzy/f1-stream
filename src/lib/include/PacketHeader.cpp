#include "PacketHeader.hpp"

std::string PacketHeaderCSVHeader() {
  std::string str =
      "m_packetFormat,m_gameMajorVersion,m_gameMinorVersion,m_packetVersion,m_packetId,m_sessionUID,m_sessionTime,m_"
      "frameIdentifier,m_playerCarIndex,m_secondaryPlayerCarIndex";
  return str;
}

std::string PacketHeaderString(PacketHeader obj, std::string sep) {
  const char *fmt = "%d%s%d%s%d%s%d%s%d%s%llu%s%f%s%d%s%d%s%d";

  int size = std::snprintf(
      nullptr, 0, fmt, obj.m_packetFormat, sep.c_str(), static_cast<std::uint32_t>(obj.m_gameMajorVersion), sep.c_str(),
      static_cast<std::uint32_t>(obj.m_gameMinorVersion), sep.c_str(), static_cast<std::uint32_t>(obj.m_packetVersion),
      sep.c_str(), static_cast<std::uint32_t>(obj.m_packetId), sep.c_str(), obj.m_sessionUID, sep.c_str(),
      obj.m_sessionTime, sep.c_str(), obj.m_frameIdentifier, sep.c_str(),
      static_cast<std::uint32_t>(obj.m_playerCarIndex), sep.c_str(),
      static_cast<std::uint32_t>(obj.m_secondaryPlayerCarIndex));

  std::vector<char> buf(size + 1);  // note +1 for null terminator
  std::snprintf(
      &buf[0], buf.size(), fmt, obj.m_packetFormat, sep.c_str(), static_cast<std::uint32_t>(obj.m_gameMajorVersion),
      sep.c_str(), static_cast<std::uint32_t>(obj.m_gameMinorVersion), sep.c_str(),
      static_cast<std::uint32_t>(obj.m_packetVersion), sep.c_str(), static_cast<std::uint32_t>(obj.m_packetId),
      sep.c_str(), obj.m_sessionUID, sep.c_str(), obj.m_sessionTime, sep.c_str(), obj.m_frameIdentifier, sep.c_str(),
      static_cast<std::uint32_t>(obj.m_playerCarIndex), sep.c_str(),
      static_cast<std::uint32_t>(obj.m_secondaryPlayerCarIndex));

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));  // remove null terminator

  return str;
}

PacketHeader ParsePacketHeader(std::vector<std::vector<unsigned char>> bytes) {
  PacketHeader obj;
  std::memcpy(&obj.m_packetFormat, &bytes.at(0).front(), sizeof(std::uint16_t));
  std::memcpy(&obj.m_gameMajorVersion, &bytes.at(1).front(), sizeof(std::uint8_t));
  std::memcpy(&obj.m_gameMinorVersion, &bytes.at(2).front(), sizeof(std::uint8_t));
  std::memcpy(&obj.m_packetVersion, &bytes.at(3).front(), sizeof(std::uint8_t));
  std::memcpy(&obj.m_packetId, &bytes.at(4).front(), sizeof(std::uint8_t));
  std::memcpy(&obj.m_sessionUID, &bytes.at(5).front(), sizeof(std::uint64_t));
  std::memcpy(&obj.m_sessionTime, &bytes.at(6).front(), sizeof(float));
  std::memcpy(&obj.m_frameIdentifier, &bytes.at(7).front(), sizeof(std::uint32_t));
  std::memcpy(&obj.m_playerCarIndex, &bytes.at(8).front(), sizeof(std::uint8_t));
  std::memcpy(&obj.m_secondaryPlayerCarIndex, &bytes.at(9).front(), sizeof(std::uint8_t));
  return obj;
};

std::vector<std::size_t> PacketHeaderSizes() {
    PacketHeader obj;
    std::vector<std::size_t> sizes = {
        sizeof obj.m_packetFormat,           // 2022
        sizeof obj.m_gameMajorVersion,       // Game major version - "X.00"
        sizeof obj.m_gameMinorVersion,       // Game minor version - "1.XX"
        sizeof obj.m_packetVersion,          // Version of this packet type, all start from 1
        sizeof obj.m_packetId,               // Identifier for the packet type, see below
        sizeof obj.m_sessionUID,             // Unique identifier for the session
        sizeof obj.m_sessionTime,            // Session timestamp
        sizeof obj.m_frameIdentifier,        // Identifier for the frame the data was retrieved on
        sizeof obj.m_playerCarIndex,         // Index of player's car in the array
        sizeof obj.m_secondaryPlayerCarIndex // Index of secondary player's car in the array
                                                      // (splitscreen), 255 if no second player
    };
    return sizes;
}
