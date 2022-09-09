#pragma once

#include "Bytes.hpp"
#include "File.hpp"
#include "Packet.hpp"
#include "PacketHeader.hpp"

#pragma pack(push, 1)

struct LobbyInfoData {
  std::uint8_t m_aiControlled;  // Whether the vehicle is AI (1) or Human (0) controlled
  std::uint8_t m_teamId;        // Team id - see appendix (255 if no team currently selected)
  std::uint8_t m_nationality;   // Nationality of the driver
  char m_name[48];              // Name of participant in UTF-8 format – null terminated
                                // Will be truncated with ... (U+2026) if too long
  std::uint8_t m_carNumber;     // Car number of the player
  std::uint8_t m_readyStatus;   // 0 = not ready, 1 = ready, 2 = spectating
};

struct LobbyInfoMeta {
  std::uint8_t m_numPlayers;  // Number of players in the lobby data
};

struct PacketLobbyInfoData {
  PacketHeader m_header;  // Header

  // Packet specific data
  LobbyInfoMeta m_lobbyPlayer;
  LobbyInfoData m_lobbyPlayers[22];
};

#pragma pack(pop)

extern std::vector<std::size_t> LobbyInfoDataSizes;
extern std::vector<std::string> LobbyInfoDataNames;

template <>
std::string subpacketDataString(LobbyInfoData obj, std::string sep);

template <>
LobbyInfoData parseSubpacketData<LobbyInfoData>(std::vector<std::vector<unsigned char>> bytes);

extern std::vector<std::size_t> LobbyInfoMetaSizes;
extern std::vector<std::string> LobbyInfoMetaNames;

template <>
std::string subpacketDataString(LobbyInfoMeta obj, std::string sep);

template <>
LobbyInfoMeta parseSubpacketData<LobbyInfoMeta>(std::vector<std::vector<unsigned char>> bytes);

template <>
std::string packetDataHeader<PacketLobbyInfoData>(std::string sep, std::string compr);

template <>
std::string packetDataString(PacketLobbyInfoData obj, std::uint8_t id, std::string sep, std::string compr,
                             std::string compr2);

template <>
PacketLobbyInfoData parsePacketData<PacketLobbyInfoData>(std::vector<unsigned char> bytes);
