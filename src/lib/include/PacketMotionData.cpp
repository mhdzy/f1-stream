#include "PacketMotionData.hpp"

std::string CarMotionDataCSVHeader() {
  std::string str =
      "m_worldPositionX,m_worldPositionY,m_worldPositionZ,m_worldVelocityX,m_worldVelocityY,m_"
      "worldVelocityZ,m_"
      "worldForwardDirX,m_worldForwardDirY,m_worldForwardDirZ,m_worldRightDirX,m_worldRightDirY,m_worldRightDirZ,m_"
      "gForceLateral,m_gForceLongitudinal,m_gForceVertical,m_yaw,m_pitch,m_roll";

  return str;
};

std::string CarMotionDataString(CarMotionData obj, std::string sep = ",") {
  const char *fmt = "%f%s%f%s%f%s%f%s%f%s%f%s%d%s%d%s%d%s%d%s%d%s%d%s%f%s%f%s%f%s%f%s%f%s%f";

  int size = std::snprintf(
      nullptr, 0, fmt, obj.m_worldPositionX, sep.c_str(), obj.m_worldPositionY, sep.c_str(), obj.m_worldPositionZ,
      sep.c_str(), obj.m_worldVelocityX, sep.c_str(), obj.m_worldVelocityY, sep.c_str(), obj.m_worldVelocityZ,
      sep.c_str(), obj.m_worldForwardDirX, sep.c_str(), obj.m_worldForwardDirY, sep.c_str(), obj.m_worldForwardDirZ,
      sep.c_str(), obj.m_worldRightDirX, sep.c_str(), obj.m_worldRightDirY, sep.c_str(), obj.m_worldRightDirZ,
      sep.c_str(), obj.m_gForceLateral, sep.c_str(), obj.m_gForceLongitudinal, sep.c_str(), obj.m_gForceVertical,
      sep.c_str(), obj.m_yaw, sep.c_str(), obj.m_pitch, sep.c_str(), obj.m_roll);

  std::vector<char> buf(size + 1);  // note +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.m_worldPositionX, sep.c_str(), obj.m_worldPositionY, sep.c_str(),
                obj.m_worldPositionZ, sep.c_str(), obj.m_worldVelocityX, sep.c_str(), obj.m_worldVelocityY, sep.c_str(),
                obj.m_worldVelocityZ, sep.c_str(), obj.m_worldForwardDirX, sep.c_str(), obj.m_worldForwardDirY,
                sep.c_str(), obj.m_worldForwardDirZ, sep.c_str(), obj.m_worldRightDirX, sep.c_str(),
                obj.m_worldRightDirY, sep.c_str(), obj.m_worldRightDirZ, sep.c_str(), obj.m_gForceLateral, sep.c_str(),
                obj.m_gForceLongitudinal, sep.c_str(), obj.m_gForceVertical, sep.c_str(), obj.m_yaw, sep.c_str(),
                obj.m_pitch, sep.c_str(), obj.m_roll);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));  // remove null terminator

  return str;
};

CarMotionData ParseCarMotionData(std::vector<std::vector<unsigned char>> bytes) {
  CarMotionData obj;

  std::memcpy(&obj.m_worldPositionX, &bytes.at(0).front(), sizeof(float));
  std::memcpy(&obj.m_worldPositionY, &bytes.at(1).front(), sizeof(float));
  std::memcpy(&obj.m_worldPositionZ, &bytes.at(2).front(), sizeof(float));
  std::memcpy(&obj.m_worldVelocityX, &bytes.at(3).front(), sizeof(float));
  std::memcpy(&obj.m_worldVelocityY, &bytes.at(4).front(), sizeof(float));
  std::memcpy(&obj.m_worldVelocityZ, &bytes.at(5).front(), sizeof(float));
  std::memcpy(&obj.m_worldForwardDirX, &bytes.at(6).front(), sizeof(std::uint16_t));
  std::memcpy(&obj.m_worldForwardDirY, &bytes.at(7).front(), sizeof(std::uint16_t));
  std::memcpy(&obj.m_worldForwardDirZ, &bytes.at(8).front(), sizeof(std::uint16_t));
  std::memcpy(&obj.m_worldRightDirX, &bytes.at(9).front(), sizeof(std::uint16_t));
  std::memcpy(&obj.m_worldRightDirY, &bytes.at(10).front(), sizeof(std::uint16_t));
  std::memcpy(&obj.m_worldRightDirZ, &bytes.at(11).front(), sizeof(std::uint16_t));
  std::memcpy(&obj.m_gForceLateral, &bytes.at(12).front(), sizeof(float));
  std::memcpy(&obj.m_gForceLongitudinal, &bytes.at(13).front(), sizeof(float));
  std::memcpy(&obj.m_gForceVertical, &bytes.at(14).front(), sizeof(float));
  std::memcpy(&obj.m_yaw, &bytes.at(15).front(), sizeof(float));
  std::memcpy(&obj.m_pitch, &bytes.at(16).front(), sizeof(float));
  std::memcpy(&obj.m_roll, &bytes.at(17).front(), sizeof(float));

  return obj;
};

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

std::string PacketMotionDataCSVHeader() {
  std::string str =
      "m_suspensionPosition,m_suspensionVelocity,m_suspensionAcceleration,m_wheelSpeed,m_wheelSlip,m_localVelocityX,"
      "m_localVelocityY,m_localVelocityZ,m_angularVelocityX,m_angularVelocityY,m_angularVelocityZ,"
      "m_angularAccelerationX,m_angularAccelerationY,m_angularAccelerationZ,m_frontWheelsAngle";

  return str;
};

std::string PacketMotionDataString(PacketMotionData obj, std::string sep) {
  const char *fmt = "%s%s%s%s%s%s%s%s%s%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f";
  const char csep = '/';
  std::string m_suspensionPosition(
      std::to_string(obj.m_suspensionPosition[0]) + csep + std::to_string(obj.m_suspensionPosition[1]) + csep +
      std::to_string(obj.m_suspensionPosition[2]) + csep + std::to_string(obj.m_suspensionPosition[3]));

  std::string m_suspensionVelocity(
      std::to_string(obj.m_suspensionVelocity[0]) + csep + std::to_string(obj.m_suspensionVelocity[1]) + csep +
      std::to_string(obj.m_suspensionVelocity[2]) + csep + std::to_string(obj.m_suspensionVelocity[3]));

  std::string m_suspensionAcceleration(
      std::to_string(obj.m_suspensionAcceleration[0]) + csep + std::to_string(obj.m_suspensionAcceleration[1]) + csep +
      std::to_string(obj.m_suspensionAcceleration[2]) + csep + std::to_string(obj.m_suspensionAcceleration[3]));

  std::string m_wheelSpeed(std::to_string(obj.m_wheelSpeed[0]) + csep + std::to_string(obj.m_wheelSpeed[1]) + csep +
                           std::to_string(obj.m_wheelSpeed[2]) + csep + std::to_string(obj.m_wheelSpeed[3]));

  std::string m_wheelSlip(std::to_string(obj.m_wheelSlip[0]) + csep + std::to_string(obj.m_wheelSlip[1]) + csep +
                          std::to_string(obj.m_wheelSlip[2]) + csep + std::to_string(obj.m_wheelSlip[3]));

  int size = std::snprintf(nullptr, 0, fmt, m_suspensionPosition.c_str(), sep.c_str(), m_suspensionVelocity.c_str(),
                           sep.c_str(), m_suspensionAcceleration.c_str(), sep.c_str(), m_wheelSpeed.c_str(),
                           sep.c_str(), m_wheelSlip.c_str(), sep.c_str(), obj.m_localVelocityX, sep.c_str(),
                           obj.m_localVelocityY, sep.c_str(), obj.m_localVelocityZ, sep.c_str(), obj.m_angularVelocityX,
                           sep.c_str(), obj.m_angularVelocityY, sep.c_str(), obj.m_angularVelocityZ, sep.c_str(),
                           obj.m_angularAccelerationX, sep.c_str(), obj.m_angularAccelerationY, sep.c_str(),
                           obj.m_angularAccelerationZ, sep.c_str(), obj.m_frontWheelsAngle);

  std::vector<char> buf(size + 1);  // note +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, m_suspensionPosition.c_str(), sep.c_str(), m_suspensionVelocity.c_str(),
                sep.c_str(), m_suspensionAcceleration.c_str(), sep.c_str(), m_wheelSpeed.c_str(), sep.c_str(),
                m_wheelSlip.c_str(), sep.c_str(), obj.m_localVelocityX, sep.c_str(), obj.m_localVelocityY, sep.c_str(),
                obj.m_localVelocityZ, sep.c_str(), obj.m_angularVelocityX, sep.c_str(), obj.m_angularVelocityY,
                sep.c_str(), obj.m_angularVelocityZ, sep.c_str(), obj.m_angularAccelerationX, sep.c_str(),
                obj.m_angularAccelerationY, sep.c_str(), obj.m_angularAccelerationZ, sep.c_str(),
                obj.m_frontWheelsAngle);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));

  return str;
};

void ParsePacketMotionData(PacketMotionData &obj, std::vector<std::vector<unsigned char>> bytes) {
  /*
    H O W   T O   D E A L   W I T H   A R R A Y S    ???
  */
  std::memcpy(&obj.m_suspensionPosition[0], &bytes.at(0).front() + 0 * sizeof(float), sizeof(float));
  std::memcpy(&obj.m_suspensionPosition[1], &bytes.at(0).front() + 1 * sizeof(float), sizeof(float));
  std::memcpy(&obj.m_suspensionPosition[2], &bytes.at(0).front() + 2 * sizeof(float), sizeof(float));
  std::memcpy(&obj.m_suspensionPosition[3], &bytes.at(0).front() + 3 * sizeof(float), sizeof(float));

  std::memcpy(&obj.m_suspensionVelocity[0], &bytes.at(1).front() + 0 * sizeof(float), sizeof(float));
  std::memcpy(&obj.m_suspensionVelocity[1], &bytes.at(1).front() + 1 * sizeof(float), sizeof(float));
  std::memcpy(&obj.m_suspensionVelocity[2], &bytes.at(1).front() + 2 * sizeof(float), sizeof(float));
  std::memcpy(&obj.m_suspensionVelocity[3], &bytes.at(1).front() + 3 * sizeof(float), sizeof(float));

  std::memcpy(&obj.m_suspensionAcceleration[0], &bytes.at(2).front() + 0 * sizeof(float), sizeof(float));
  std::memcpy(&obj.m_suspensionAcceleration[1], &bytes.at(2).front() + 1 * sizeof(float), sizeof(float));
  std::memcpy(&obj.m_suspensionAcceleration[2], &bytes.at(2).front() + 2 * sizeof(float), sizeof(float));
  std::memcpy(&obj.m_suspensionAcceleration[3], &bytes.at(2).front() + 3 * sizeof(float), sizeof(float));

  std::memcpy(&obj.m_wheelSpeed[0], &bytes.at(3).front() + 0 * sizeof(float), sizeof(float));
  std::memcpy(&obj.m_wheelSpeed[1], &bytes.at(3).front() + 1 * sizeof(float), sizeof(float));
  std::memcpy(&obj.m_wheelSpeed[2], &bytes.at(3).front() + 2 * sizeof(float), sizeof(float));
  std::memcpy(&obj.m_wheelSpeed[3], &bytes.at(3).front() + 3 * sizeof(float), sizeof(float));

  std::memcpy(&obj.m_wheelSlip[0], &bytes.at(4).front() + 0 * sizeof(float), sizeof(float));
  std::memcpy(&obj.m_wheelSlip[1], &bytes.at(4).front() + 1 * sizeof(float), sizeof(float));
  std::memcpy(&obj.m_wheelSlip[2], &bytes.at(4).front() + 2 * sizeof(float), sizeof(float));
  std::memcpy(&obj.m_wheelSlip[3], &bytes.at(4).front() + 3 * sizeof(float), sizeof(float));

  std::memcpy(&obj.m_localVelocityX, &bytes.at(5).front(), sizeof(float));
  std::memcpy(&obj.m_localVelocityY, &bytes.at(6).front(), sizeof(float));
  std::memcpy(&obj.m_localVelocityZ, &bytes.at(7).front(), sizeof(float));
  std::memcpy(&obj.m_angularVelocityX, &bytes.at(8).front(), sizeof(float));
  std::memcpy(&obj.m_angularVelocityY, &bytes.at(9).front(), sizeof(float));
  std::memcpy(&obj.m_angularVelocityZ, &bytes.at(10).front(), sizeof(float));
  std::memcpy(&obj.m_angularAccelerationX, &bytes.at(11).front(), sizeof(float));
  std::memcpy(&obj.m_angularAccelerationY, &bytes.at(12).front(), sizeof(float));
  std::memcpy(&obj.m_angularAccelerationZ, &bytes.at(13).front(), sizeof(float));
  std::memcpy(&obj.m_frontWheelsAngle, &bytes.at(14).front(), sizeof(float));

  return;
};

std::vector<std::pair<int, std::string>> PacketMotionDataPairs = {
    std::make_pair(sizeof(float) * 4, "m_suspensionPosition"),      // Note: All wheel arrays have the
                                                                    // following order:
    std::make_pair(sizeof(float) * 4, "m_suspensionVelocity"),      // RL, RR, FL, FR
    std::make_pair(sizeof(float) * 4, "m_suspensionAcceleration"),  // RL, RR, FL, FR
    std::make_pair(sizeof(float) * 4, "m_wheelSpeed"),              // Speed of each wheel
    std::make_pair(sizeof(float) * 4, "m_wheelSlip"),               // Slip ratio for each wheel
    std::make_pair(sizeof(float), "m_localVelocityX"),              // Velocity in local space
    std::make_pair(sizeof(float), "m_localVelocityY"),              // Velocity in local space
    std::make_pair(sizeof(float), "m_localVelocityZ"),              // Velocity in local space
    std::make_pair(sizeof(float), "m_angularVelocityX"),            // Angular velocity x-component
    std::make_pair(sizeof(float), "m_angularVelocityY"),            // Angular velocity y-component
    std::make_pair(sizeof(float), "m_angularVelocityZ"),            // Angular velocity z-component
    std::make_pair(sizeof(float), "m_angularAccelerationX"),        // Angular velocity x-component
    std::make_pair(sizeof(float), "m_angularAccelerationY"),        // Angular velocity y-component
    std::make_pair(sizeof(float), "m_angularAccelerationZ"),        // Angular velocity z-component
    std::make_pair(sizeof(float), "m_frontWheelsAngle")             // Curent front wheel angle in radians
};
