#pragma once

#include <cstdint>

#include "File.hpp"
#include "PacketHeader.hpp"

#pragma pack(push, 1)

struct CarSetupData {
  std::uint8_t m_frontWing;              // Front wing aero
  std::uint8_t m_rearWing;               // Rear wing aero
  std::uint8_t m_onThrottle;             // Differential adjustment on throttle (percentage)
  std::uint8_t m_offThrottle;            // Differential adjustment off throttle (percentage)
  float m_frontCamber;                   // Front camber angle (suspension geometry)
  float m_rearCamber;                    // Rear camber angle (suspension geometry)
  float m_frontToe;                      // Front toe angle (suspension geometry)
  float m_rearToe;                       // Rear toe angle (suspension geometry)
  std::uint8_t m_frontSuspension;        // Front suspension
  std::uint8_t m_rearSuspension;         // Rear suspension
  std::uint8_t m_frontAntiRollBar;       // Front anti-roll bar
  std::uint8_t m_rearAntiRollBar;        // Front anti-roll bar
  std::uint8_t m_frontSuspensionHeight;  // Front ride height
  std::uint8_t m_rearSuspensionHeight;   // Rear ride height
  std::uint8_t m_brakePressure;          // Brake pressure (percentage)
  std::uint8_t m_brakeBias;              // Brake bias (percentage)
  float m_rearLeftTyrePressure;          // Rear left tyre pressure (PSI)
  float m_rearRightTyrePressure;         // Rear right tyre pressure (PSI)
  float m_frontLeftTyrePressure;         // Front left tyre pressure (PSI)
  float m_frontRightTyrePressure;        // Front right tyre pressure (PSI)
  std::uint8_t m_ballast;                // Ballast
  float m_fuelLoad;                      // Fuel load
};

struct PacketCarSetupData {
  PacketHeader m_header;  // Header

  CarSetupData m_carSetups[22];
};

#pragma pack(pop)

extern std::vector<std::size_t> CarSetupDataSizes;
extern std::vector<std::string> CarSetupDataNames;
extern std::string CarSetupDataString(CarSetupData obj, std::string sep = ",");
extern CarSetupData ParseCarSetupData(std::vector<std::vector<unsigned char>> bytes);

extern std::string PacketCarSetupDataCSVHeader(std::string sep = ",", std::string compr = "/");
extern std::string PacketCarSetupDataString(PacketCarSetupData obj, std::uint8_t carID, std::string sep = ",");
extern PacketCarSetupData ParsePacketCarSetupData(std::vector<unsigned char> bytes);
