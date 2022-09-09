#pragma once

#include "Bytes.hpp"
#include "File.hpp"
#include "Packet.hpp"
#include "PacketHeader.hpp"

#pragma pack(push, 1)

struct CarDamageData {
  float m_tyresWear[4];                 // Tyre wear (percentage)
  std::uint8_t m_tyresDamage[4];        // Tyre damage (percentage)
  std::uint8_t m_brakesDamage[4];       // Brakes damage (percentage)
  std::uint8_t m_frontLeftWingDamage;   // Front left wing damage (percentage)
  std::uint8_t m_frontRightWingDamage;  // Front right wing damage (percentage)
  std::uint8_t m_rearWingDamage;        // Rear wing damage (percentage)
  std::uint8_t m_floorDamage;           // Floor damage (percentage)
  std::uint8_t m_diffuserDamage;        // Diffuser damage (percentage)
  std::uint8_t m_sidepodDamage;         // Sidepod damage (percentage)
  std::uint8_t m_drsFault;              // Indicator for DRS fault, 0 = OK, 1 = fault
  std::uint8_t m_ersFault;              // Indicator for ERS fault, 0 = OK, 1 = fault
  std::uint8_t m_gearBoxDamage;         // Gear box damage (percentage)
  std::uint8_t m_engineDamage;          // Engine damage (percentage)
  std::uint8_t m_engineMGUHWear;        // Engine wear MGU-H (percentage)
  std::uint8_t m_engineESWear;          // Engine wear ES (percentage)
  std::uint8_t m_engineCEWear;          // Engine wear CE (percentage)
  std::uint8_t m_engineICEWear;         // Engine wear ICE (percentage)
  std::uint8_t m_engineMGUKWear;        // Engine wear MGU-K (percentage)
  std::uint8_t m_engineTCWear;          // Engine wear TC (percentage)
  std::uint8_t m_engineBlown;           // Engine blown, 0 = OK, 1 = fault
  std::uint8_t m_engineSeized;          // Engine seized, 0 = OK, 1 = fault
};

struct PacketCarDamageData {
  PacketHeader m_header;  // Header

  CarDamageData m_carDamageData[22];
};

#pragma pack(pop)

extern std::vector<std::size_t> CarDamageDataSizes;
extern std::vector<std::string> CarDamageDataNames;
extern std::string CarDamageDataString(CarDamageData obj, std::string sep = ",");

template <>
CarDamageData parseSubpacketData<CarDamageData>(std::vector<std::vector<unsigned char>> bytes);

template <>
std::string packetDataHeader<PacketCarDamageData>(std::string sep, std::string compr);

template <>
std::string packetDataString(PacketCarDamageData obj, std::uint8_t id, std::string sep, std::string compr,
                             std::string compr2);

template <>
PacketCarDamageData parsePacketData<PacketCarDamageData>(std::vector<unsigned char> bytes);
