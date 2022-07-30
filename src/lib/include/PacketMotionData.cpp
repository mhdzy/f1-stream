#include "PacketMotionData.hpp"

void PrintCarMotionData(CarMotionData cmd) {
  // printf("CarMotionData\n");
  // printf("m_worldPositionX: %f\n", cmd.m_worldPositionX);
  printf("%f, %f\n", cmd.m_worldPositionX, cmd.m_worldPositionY);
  /*
  printf("m_worldPositionY: %f\n", cmd.m_worldPositionY);
  printf("m_worldPositionZ: %f\n", cmd.m_worldPositionZ);
  printf("m_worldVelocityX: %f\n", cmd.m_worldVelocityX);
  printf("m_worldVelocityY: %f\n", cmd.m_worldVelocityY);
  printf("m_worldVelocityZ: %f\n", cmd.m_worldVelocityZ);
  printf("m_worldForwardDirX: %d\n", cmd.m_worldForwardDirX);
  printf("m_worldForwardDirY: %d\n", cmd.m_worldForwardDirY);
  printf("m_worldForwardDirZ: %d\n", cmd.m_worldForwardDirZ);
  printf("m_worldRightDirX: %d\n", cmd.m_worldRightDirX);
  printf("m_worldRightDirY: %d\n", cmd.m_worldRightDirY);
  printf("m_worldRightDirZ: %d\n", cmd.m_worldRightDirZ);
  printf("m_gForceLateral: %f\n", cmd.m_gForceLateral);
  printf("m_gForceLongitudinal: %f\n", cmd.m_gForceLongitudinal);
  printf("m_gForceVertical: %f\n", cmd.m_gForceVertical);
  printf("m_yaw: %f\n", cmd.m_yaw);
  printf("m_pitch: %f\n", cmd.m_pitch);
  printf("m_roll: %f\n", cmd.m_roll);
  */
}

void PrintPacketMotionData(PacketMotionData pmd) {}

CarMotionData ParseCarMotionData(std::vector<std::vector<unsigned char>> bytes) {
  CarMotionData cmd;
  std::memcpy(&cmd.m_worldPositionX, &bytes.at(0).front(), sizeof(float));
  std::memcpy(&cmd.m_worldPositionY, &bytes.at(1).front(), sizeof(float));
  std::memcpy(&cmd.m_worldPositionZ, &bytes.at(2).front(), sizeof(float));
  std::memcpy(&cmd.m_worldVelocityX, &bytes.at(3).front(), sizeof(float));
  std::memcpy(&cmd.m_worldVelocityY, &bytes.at(4).front(), sizeof(float));
  std::memcpy(&cmd.m_worldVelocityZ, &bytes.at(5).front(), sizeof(float));
  std::memcpy(&cmd.m_worldForwardDirX, &bytes.at(6).front(), sizeof(std::uint16_t));
  std::memcpy(&cmd.m_worldForwardDirY, &bytes.at(7).front(), sizeof(std::uint16_t));
  std::memcpy(&cmd.m_worldForwardDirZ, &bytes.at(8).front(), sizeof(std::uint16_t));
  std::memcpy(&cmd.m_worldRightDirX, &bytes.at(9).front(), sizeof(std::uint16_t));
  std::memcpy(&cmd.m_worldRightDirY, &bytes.at(10).front(), sizeof(std::uint16_t));
  std::memcpy(&cmd.m_worldRightDirZ, &bytes.at(11).front(), sizeof(std::uint16_t));
  std::memcpy(&cmd.m_gForceLateral, &bytes.at(12).front(), sizeof(float));
  std::memcpy(&cmd.m_gForceLongitudinal, &bytes.at(13).front(), sizeof(float));
  std::memcpy(&cmd.m_gForceVertical, &bytes.at(14).front(), sizeof(float));
  std::memcpy(&cmd.m_yaw, &bytes.at(15).front(), sizeof(float));
  std::memcpy(&cmd.m_pitch, &bytes.at(16).front(), sizeof(float));
  std::memcpy(&cmd.m_roll, &bytes.at(17).front(), sizeof(float));
  return (cmd);
}

PacketMotionData ParsePacketMotionData(std::vector<std::vector<unsigned char>> bytes) {
  PacketMotionData pmd;
  return (pmd);
}

std::vector<std::pair<int, std::string>> CarMotionDataPairs = {
    std::make_pair(sizeof(float), "m_worldPositionX"),           // World space X position
    std::make_pair(sizeof(float), "m_worldPositionY"),           // World space Y position
    std::make_pair(sizeof(float), "m_worldPositionZ"),           // World space Z position
    std::make_pair(sizeof(float), "m_worldVelocityX"),           // Velocity in world space X
    std::make_pair(sizeof(float), "m_worldVelocityY"),           // Velocity in world space Y
    std::make_pair(sizeof(float), "m_worldVelocityZ"),           // Velocity in world space Z
    std::make_pair(sizeof(std::int16_t), "m_worldForwardDirX"),  // World space forward X direction (normalised)
    std::make_pair(sizeof(std::int16_t), "m_worldForwardDirY"),  // World space forward Y direction (normalised)
    std::make_pair(sizeof(std::int16_t), "m_worldForwardDirZ"),  // World space forward Z direction (normalised)
    std::make_pair(sizeof(std::int16_t), "m_worldRightDirX"),    // World space right X direction (normalised)
    std::make_pair(sizeof(std::int16_t), "m_worldRightDirY"),    // World space right Y direction (normalised)
    std::make_pair(sizeof(std::int16_t), "m_worldRightDirZ"),    // World space right Z direction (normalised)
    std::make_pair(sizeof(float), "m_gForceLateral"),            // Lateral G-Force component
    std::make_pair(sizeof(float), "m_gForceLongitudinal"),       // Longitudinal G-Force component
    std::make_pair(sizeof(float), "m_gForceVertical"),           // Vertical G-Force component
    std::make_pair(sizeof(float), "m_yaw"),                      // Yaw angle in radians
    std::make_pair(sizeof(float), "m_pitch"),                    // Pitch angle in radians
    std::make_pair(sizeof(float), "m_roll")                      // Roll angle in radians
};

std::vector<std::pair<int, std::string>> PacketMotionDataPairs = {

};
