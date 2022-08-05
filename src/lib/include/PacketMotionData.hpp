#pragma once

#include <cstdint>
#include <iostream>
#include <vector>

#include "File.hpp"
#include "PacketHeader.hpp"

#pragma pack(push, 1)

struct CarMotionData {
  float m_worldPositionX;           // World space X position
  float m_worldPositionY;           // World space Y position
  float m_worldPositionZ;           // World space Z position
  float m_worldVelocityX;           // Velocity in world space X
  float m_worldVelocityY;           // Velocity in world space Y
  float m_worldVelocityZ;           // Velocity in world space Z
  std::int16_t m_worldForwardDirX;  // World space forward X direction (normalised)
  std::int16_t m_worldForwardDirY;  // World space forward Y direction (normalised)
  std::int16_t m_worldForwardDirZ;  // World space forward Z direction (normalised)
  std::int16_t m_worldRightDirX;    // World space right X direction (normalised)
  std::int16_t m_worldRightDirY;    // World space right Y direction (normalised)
  std::int16_t m_worldRightDirZ;    // World space right Z direction (normalised)
  float m_gForceLateral;            // Lateral G-Force component
  float m_gForceLongitudinal;       // Longitudinal G-Force component
  float m_gForceVertical;           // Vertical G-Force component
  float m_yaw;                      // Yaw angle in radians
  float m_pitch;                    // Pitch angle in radians
  float m_roll;                     // Roll angle in radians
};

struct ExtraCarMotionData {
  // Extra player car ONLY data
  float m_suspensionPosition[4];      // Note: All wheel arrays have the following
                                      // order:
  float m_suspensionVelocity[4];      // RL, RR, FL, FR
  float m_suspensionAcceleration[4];  // RL, RR, FL, FR
  float m_wheelSpeed[4];              // Speed of each wheel
  float m_wheelSlip[4];               // Slip ratio for each wheel
  float m_localVelocityX;             // Velocity in local space
  float m_localVelocityY;             // Velocity in local space
  float m_localVelocityZ;             // Velocity in local space
  float m_angularVelocityX;           // Angular velocity x-component
  float m_angularVelocityY;           // Angular velocity y-component
  float m_angularVelocityZ;           // Angular velocity z-component
  float m_angularAccelerationX;       // Angular velocity x-component
  float m_angularAccelerationY;       // Angular velocity y-component
  float m_angularAccelerationZ;       // Angular velocity z-component
  float m_frontWheelsAngle;           // Current front wheels angle in radians
};

struct PacketMotionData {
  PacketHeader m_header;                    // Header
  CarMotionData m_carMotionData[22];        // Data for all cars on track
  ExtraCarMotionData m_extraCarMotionData;  // Custom struct to simplify packet
};

#pragma pack(pop)

extern std::string CarMotionDataCSVHeader();
extern std::string CarMotionDataString(CarMotionData obj, std::string sep = ",");
extern CarMotionData ParseCarMotionData(std::vector<std::vector<unsigned char>> bytes);
extern std::vector<std::size_t> CarMotionDataSizes();

extern std::string ExtraCarMotionDataCSVHeader();
extern std::string ExtraCarMotionDataString(ExtraCarMotionData obj, std::string sep = ",");
extern ExtraCarMotionData ParseExtraCarMotionData(std::vector<std::vector<unsigned char>> bytes);
extern std::vector<std::size_t> ExtraCarMotionDataSizes();

extern std::string PacketMotionDataCSVHeader(std::string sep = ",");
extern std::string PacketMotionDataString(PacketMotionData obj, int carID, std::string sep = ",");
extern PacketMotionData ParsePacketMotionData(std::vector<unsigned char> bytes);
