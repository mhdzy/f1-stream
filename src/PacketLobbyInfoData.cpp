
#include "../include/PacketLobbyInfoData.hpp"

template <>
std::vector<std::size_t> pSizes<LobbyInfoMeta>() {
  return std::vector<std::size_t>{
      sizeof(((LobbyInfoMeta *)0)->m_numPlayers)  // Number of players in the lobby data
  };
}

template <>
std::vector<std::string> pNames<LobbyInfoMeta>() {
  return std::vector<std::string>{
      "m_numPlayers"  // Number of players in the lobby data
  };
}

template <>
std::vector<std::size_t> pSizes<LobbyInfoData>() {
  return std::vector<std::size_t>{
      sizeof(((LobbyInfoData *)0)->m_aiControlled),  // Whether the vehicle is AI (1) or Human (0) controlled
      sizeof(((LobbyInfoData *)0)->m_teamId),        // Team id - see appendix (255 if no team currently selected)
      sizeof(((LobbyInfoData *)0)->m_nationality),   // Nationality of the driver
      sizeof(((LobbyInfoData *)0)->m_name),          // Name of participant in UTF-8 format – null terminated
                                                     // Will be truncated with ... (U+2026) if too long
      sizeof(((LobbyInfoData *)0)->m_carNumber),     // Car number of the player
      sizeof(((LobbyInfoData *)0)->m_readyStatus)    // 0 = not ready, 1 = ready, 2 = spectating
  };
}

template <>
std::vector<std::string> pNames<LobbyInfoData>() {
  return std::vector<std::string>{
      "m_aiControlled",  // Whether the vehicle is AI (1) or Human (0) controlled
      "m_teamId",        // Team id - see appendix (255 if no team currently selected)
      "m_nationality",   // Nationality of the driver
      "m_name",          // Name of participant in UTF-8 format – null terminated
                         // Will be truncated with ... (U+2026) if too long
      "m_carNumber",     // Car number of the player
      "m_readyStatus"    // 0 = not ready, 1 = ready, 2 = spectating
  };
}

template <>
std::string subpacketDataString(LobbyInfoMeta obj, std::string sep) {
  const char *fmt = "%d";
  // const char *ssep = sep.c_str();

  const std::size_t size = std::snprintf(nullptr, 0, fmt, obj.m_numPlayers);

  std::vector<char> buf(size + 1);  // note +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.m_numPlayers);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));  // remove null terminator

  return str;
}

template <>
LobbyInfoMeta parseSubpacketData<LobbyInfoMeta>(std::vector<std::vector<unsigned char>> bytes) {
  LobbyInfoMeta obj;

  std::memcpy(&obj.m_numPlayers, &bytes.at(0).front(), sizeof obj.m_numPlayers);

  return obj;
}

template <>
std::string subpacketDataString(LobbyInfoData obj, std::string sep) {
  const char *fmt = "%d%s%d%s%d%s%s%s%d%s%d";
  const char *ssep = sep.c_str();

  const std::size_t size =
      std::snprintf(nullptr, 0, fmt, obj.m_aiControlled, ssep, obj.m_teamId, ssep, obj.m_nationality, ssep, obj.m_name,
                    ssep, obj.m_carNumber, ssep, obj.m_readyStatus);

  std::vector<char> buf(size + 1);  // note +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.m_aiControlled, ssep, obj.m_teamId, ssep, obj.m_nationality, ssep,
                obj.m_name, ssep, obj.m_carNumber, ssep, obj.m_readyStatus);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));  // remove null terminator

  return str;
}

template <>
LobbyInfoData parseSubpacketData<LobbyInfoData>(std::vector<std::vector<unsigned char>> bytes) {
  LobbyInfoData obj;
  std::memcpy(&obj.m_aiControlled, &bytes.at(0).front(), sizeof obj.m_aiControlled);
  std::memcpy(&obj.m_teamId, &bytes.at(1).front(), sizeof obj.m_teamId);
  std::memcpy(&obj.m_nationality, &bytes.at(2).front(), sizeof obj.m_nationality);
  std::memcpy(&obj.m_name, &bytes.at(3).front(), sizeof obj.m_name);
  std::memcpy(&obj.m_carNumber, &bytes.at(4).front(), sizeof obj.m_carNumber);
  std::memcpy(&obj.m_readyStatus, &bytes.at(5).front(), sizeof obj.m_readyStatus);
  return obj;
}

template <>
std::string packetDataHeader<PacketLobbyInfoData>(std::string sep, std::string compr) {
  std::vector<std::string> vec = {
      vpaste(pNames<PacketHeader>(), sep),   //
      vpaste(pNames<LobbyInfoMeta>(), sep),  //
      vpaste(pNames<LobbyInfoData>(), sep)   //
  };
  return vpaste(vec, sep);
}

template <>
std::string packetDataString(PacketLobbyInfoData obj, std::uint8_t id, std::string sep, std::string compr,
                             std::string compr2) {
  std::vector<std::string> vec = {
      subpacketDataString(obj.m_header),           //
      subpacketDataString(obj.m_lobbyPlayer),      //
      subpacketDataString(obj.m_lobbyPlayers[id])  //
  };
  return vpaste(vec, sep);
}

template <>
PacketLobbyInfoData parsePacketData<PacketLobbyInfoData>(std::vector<unsigned char> bytes) {
  PacketLobbyInfoData obj;
  std::uint16_t offset = 0;

  // parse header
  obj.m_header = parseSubpacketDataT<PacketHeader>(bytes, offset);
  offset += sizeof(PacketHeader);

  // parse extra player car data
  obj.m_lobbyPlayer = parseSubpacketDataT<LobbyInfoMeta>(bytes, offset);
  offset += sizeof(LobbyInfoMeta);

  // loop over the 22 car data packets and parse them
  for (std::uint8_t i = 0; i < 22; i++) {
    obj.m_lobbyPlayers[i] = parseSubpacketDataT<LobbyInfoData>(bytes, offset);
    offset += sizeof(LobbyInfoData);
  }

  return obj;
}
