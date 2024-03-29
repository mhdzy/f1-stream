#pragma once

#include <cstdint>

#include "Bytes.hpp"
#include "File.hpp"
#include "Packet.hpp"
#include "PacketHeader.hpp"

#pragma pack(push, 1)

struct CarTelemetryData {
  std::uint16_t m_speed;                      // Speed of car in kilometres per hour
  float m_throttle;                           // Amount of throttle applied (0.0 to 1.0)
  float m_steer;                              // Steering (-1.0 (full lock left) to 1.0 (full lock right))
  float m_brake;                              // Amount of brake applied (0.0 to 1.0)
  std::uint8_t m_clutch;                      // Amount of clutch applied (0 to 100)
  std::int8_t m_gear;                         // Gear selected (1-8, N=0, R=-1)
  std::uint16_t m_engineRPM;                  // Engine RPM
  std::uint8_t m_drs;                         // 0 = off, 1 = on
  std::uint8_t m_revLightsPercent;            // Rev lights indicator (percentage)
  std::uint16_t m_revLightsBitValue;          // Rev lights (bit 0 = leftmost LED, bit 14 = rightmost LED)
  std::uint16_t m_brakesTemperature[4];       // Brakes temperature (celsius)
  std::uint8_t m_tyresSurfaceTemperature[4];  // Tyres surface temperature (celsius)
  std::uint8_t m_tyresInnerTemperature[4];    // Tyres inner temperature (celsius)
  std::uint16_t m_engineTemperature;          // Engine temperature (celsius)
  float m_tyresPressure[4];                   // Tyres pressure (PSI)
  std::uint8_t m_surfaceType[4];              // Driving surface, see appendices
};

struct CarTelemetryPanel {
  std::uint8_t m_mfdPanelIndex;                 // Index of MFD panel open - 255 = MFD closed
                                                // Single player, race – 0 = Car setup, 1 = Pits
                                                // 2 = Damage, 3 =  Engine, 4 = Temperatures
                                                // May vary depending on game mode
  std::uint8_t m_mfdPanelIndexSecondaryPlayer;  // See above
  std::int8_t m_suggestedGear;                  // Suggested gear for the player (1-8)
                                                // 0 if no gear suggested
};

struct PacketCarTelemetryData {
  PacketHeader m_header;  // Header

  CarTelemetryData m_carTelemetryData[22];
  CarTelemetryPanel m_carTelemetryPanel;
};

#pragma pack(pop)

template <>
std::vector<std::size_t> pSizes<CarTelemetryData>();

template <>
std::vector<std::string> pNames<CarTelemetryData>();

template <>
std::string subpacketDataString(CarTelemetryData obj, std::string sep);

template <>
CarTelemetryData parseSubpacketData<CarTelemetryData>(std::vector<std::vector<unsigned char>> bytes);

template <>
std::vector<std::size_t> pSizes<CarTelemetryPanel>();

template <>
std::vector<std::string> pNames<CarTelemetryPanel>();

template <>
std::string subpacketDataString(CarTelemetryPanel obj, std::string sep);

template <>
CarTelemetryPanel parseSubpacketData<CarTelemetryPanel>(std::vector<std::vector<unsigned char>> bytes);

template <>
std::string packetDataHeader<PacketCarTelemetryData>(std::string sep, std::string compr);

template <>
std::string packetDataString(PacketCarTelemetryData obj, std::uint8_t id, std::string sep, std::string compr,
                             std::string compr2);

template <>
PacketCarTelemetryData parsePacketData<PacketCarTelemetryData>(std::vector<unsigned char> bytes);
