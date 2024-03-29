#pragma once

#include "Bytes.hpp"
#include "File.hpp"
#include "Packet.hpp"
#include "PacketHeader.hpp"

#pragma pack(push, 1)

struct LapMetaData {
  std::uint8_t m_carIdx;         // Index of the car this lap data relates to
  std::uint8_t m_numLaps;        // Num laps in the data (including current partial lap)
  std::uint8_t m_numTyreStints;  // Number of tyre stints in the data

  std::uint8_t m_bestLapTimeLapNum;  // Lap the best lap time was achieved on
  std::uint8_t m_bestSector1LapNum;  // Lap the best Sector 1 time was achieved on
  std::uint8_t m_bestSector2LapNum;  // Lap the best Sector 2 time was achieved on
  std::uint8_t m_bestSector3LapNum;  // Lap the best Sector 3 time was achieved on
};

struct LapHistoryData {
  std::uint32_t m_lapTimeInMS;      // Lap time in milliseconds
  std::uint16_t m_sector1TimeInMS;  // Sector 1 time in milliseconds
  std::uint16_t m_sector2TimeInMS;  // Sector 2 time in milliseconds
  std::uint16_t m_sector3TimeInMS;  // Sector 3 time in milliseconds
  std::uint8_t m_lapValidBitFlags;  // 0x01 bit set-lap valid,      0x02 bit set-sector 1 valid
                                    // 0x04 bit set-sector 2 valid, 0x08 bit set-sector 3 valid
};

struct TyreStintHistoryData {
  std::uint8_t m_endLap;              // Lap the tyre usage ends on (255 of current tyre)
  std::uint8_t m_tyreActualCompound;  // Actual tyres used by this driver
  std::uint8_t m_tyreVisualCompound;  // Visual tyres used by this driver
};

struct PacketSessionHistoryData {
  PacketHeader m_header;                 // Header
  LapMetaData m_lapMetaData;             // Metadata describing player and session info
  LapHistoryData m_lapHistoryData[100];  // 100 laps of data max
  TyreStintHistoryData m_tyreStintsHistoryData[8];
};

#pragma pack(pop)

template <>
std::vector<std::size_t> pSizes<LapMetaData>();

template <>
std::vector<std::string> pNames<LapMetaData>();

template <>
std::string subpacketDataString(LapMetaData obj, std::string sep);

template <>
LapMetaData parseSubpacketData<LapMetaData>(std::vector<std::vector<unsigned char>> bytes);

template <>
std::vector<std::size_t> pSizes<LapHistoryData>();

template <>
std::vector<std::string> pNames<LapHistoryData>();

template <>
std::string subpacketDataString(LapHistoryData obj, std::string sep);

template <>
LapHistoryData parseSubpacketData<LapHistoryData>(std::vector<std::vector<unsigned char>> bytes);

template <>
std::vector<std::size_t> pSizes<TyreStintHistoryData>();

template <>
std::vector<std::string> pNames<TyreStintHistoryData>();

template <>
std::string subpacketDataString(TyreStintHistoryData obj, std::string sep);

template <>
TyreStintHistoryData parseSubpacketData<TyreStintHistoryData>(std::vector<std::vector<unsigned char>> bytes);

template <>
std::string packetDataHeader<PacketSessionHistoryData>(std::string sep, std::string compr);

template <>
std::string packetDataString(PacketSessionHistoryData obj, std::uint8_t id, std::string sep, std::string compr,
                             std::string compr2);

template <>
PacketSessionHistoryData parsePacketData<PacketSessionHistoryData>(std::vector<unsigned char> bytes);
