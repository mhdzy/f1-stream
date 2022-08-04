#include "PacketMotionData.hpp"

std::string CarMotionDataCSVHeader() {
  std::string str =
      "m_worldPositionX,m_worldPositionY,m_worldPositionZ,m_worldVelocityX,m_worldVelocityY,m_"
      "worldVelocityZ,m_"
      "worldForwardDirX,m_worldForwardDirY,m_worldForwardDirZ,m_worldRightDirX,m_worldRightDirY,m_worldRightDirZ,m_"
      "gForceLateral,m_gForceLongitudinal,m_gForceVertical,m_yaw,m_pitch,m_roll";

  return str;
}

std::string CarMotionDataString(CarMotionData obj, std::string sep) {
  const char *fmt = "%f%s%f%s%f%s%f%s%f%s%f%s%d%s%d%s%d%s%d%s%d%s%d%s%f%s%f%s%f%s%f%s%f%s%f";
  const char *ssep = sep.c_str();

  const int size = std::snprintf(nullptr, 0, fmt, obj.m_worldPositionX, ssep, obj.m_worldPositionY, ssep,
                                 obj.m_worldPositionZ, ssep, obj.m_worldVelocityX, ssep, obj.m_worldVelocityY, ssep,
                                 obj.m_worldVelocityZ, ssep, obj.m_worldForwardDirX, ssep, obj.m_worldForwardDirY, ssep,
                                 obj.m_worldForwardDirZ, ssep, obj.m_worldRightDirX, ssep, obj.m_worldRightDirY, ssep,
                                 obj.m_worldRightDirZ, ssep, obj.m_gForceLateral, ssep, obj.m_gForceLongitudinal, ssep,
                                 obj.m_gForceVertical, ssep, obj.m_yaw, ssep, obj.m_pitch, ssep, obj.m_roll);

  std::vector<char> buf(size + 1);  // note +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.m_worldPositionX, ssep, obj.m_worldPositionY, ssep, obj.m_worldPositionZ,
                ssep, obj.m_worldVelocityX, ssep, obj.m_worldVelocityY, ssep, obj.m_worldVelocityZ, ssep,
                obj.m_worldForwardDirX, ssep, obj.m_worldForwardDirY, ssep, obj.m_worldForwardDirZ, ssep,
                obj.m_worldRightDirX, ssep, obj.m_worldRightDirY, ssep, obj.m_worldRightDirZ, ssep, obj.m_gForceLateral,
                ssep, obj.m_gForceLongitudinal, ssep, obj.m_gForceVertical, ssep, obj.m_yaw, ssep, obj.m_pitch, ssep,
                obj.m_roll);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));  // remove null terminator

  return str;
}

CarMotionData ParseCarMotionData(std::vector<std::vector<unsigned char>> bytes) {
  CarMotionData obj;

  std::memcpy(&obj.m_worldPositionX, &bytes.at(0).front(), sizeof obj.m_worldPositionX);
  std::memcpy(&obj.m_worldPositionY, &bytes.at(1).front(), sizeof obj.m_worldPositionY);
  std::memcpy(&obj.m_worldPositionZ, &bytes.at(2).front(), sizeof obj.m_worldPositionZ);
  std::memcpy(&obj.m_worldVelocityX, &bytes.at(3).front(), sizeof obj.m_worldVelocityX);
  std::memcpy(&obj.m_worldVelocityY, &bytes.at(4).front(), sizeof obj.m_worldVelocityY);
  std::memcpy(&obj.m_worldVelocityZ, &bytes.at(5).front(), sizeof obj.m_worldVelocityZ);
  std::memcpy(&obj.m_worldForwardDirX, &bytes.at(6).front(), sizeof obj.m_worldForwardDirX);
  std::memcpy(&obj.m_worldForwardDirY, &bytes.at(7).front(), sizeof obj.m_worldForwardDirY);
  std::memcpy(&obj.m_worldForwardDirZ, &bytes.at(8).front(), sizeof obj.m_worldForwardDirZ);
  std::memcpy(&obj.m_worldRightDirX, &bytes.at(9).front(), sizeof obj.m_worldRightDirX);
  std::memcpy(&obj.m_worldRightDirY, &bytes.at(10).front(), sizeof obj.m_worldRightDirY);
  std::memcpy(&obj.m_worldRightDirZ, &bytes.at(11).front(), sizeof obj.m_worldRightDirZ);
  std::memcpy(&obj.m_gForceLateral, &bytes.at(12).front(), sizeof obj.m_gForceLateral);
  std::memcpy(&obj.m_gForceLongitudinal, &bytes.at(13).front(), sizeof obj.m_gForceLongitudinal);
  std::memcpy(&obj.m_gForceVertical, &bytes.at(14).front(), sizeof obj.m_gForceVertical);
  std::memcpy(&obj.m_yaw, &bytes.at(15).front(), sizeof obj.m_yaw);
  std::memcpy(&obj.m_pitch, &bytes.at(16).front(), sizeof obj.m_pitch);
  std::memcpy(&obj.m_roll, &bytes.at(17).front(), sizeof obj.m_roll);

  return obj;
}

std::vector<std::size_t> CarMotionDataSizes() {
  CarMotionData obj;
  std::vector<std::size_t> sizes = {
      sizeof obj.m_worldPositionX,      // World space X position
      sizeof obj.m_worldPositionY,      // World space Y position
      sizeof obj.m_worldPositionZ,      // World space Z position
      sizeof obj.m_worldVelocityX,      // Velocity in world space X
      sizeof obj.m_worldVelocityY,      // Velocity in world space Y
      sizeof obj.m_worldVelocityZ,      // Velocity in world space Z
      sizeof obj.m_worldForwardDirX,    // World space forward X direction (normalised)
      sizeof obj.m_worldForwardDirY,    // World space forward Y direction (normalised)
      sizeof obj.m_worldForwardDirZ,    // World space forward Z direction (normalised)
      sizeof obj.m_worldRightDirX,      // World space right X direction (normalised)
      sizeof obj.m_worldRightDirY,      // World space right Y direction (normalised)
      sizeof obj.m_worldRightDirZ,      // World space right Z direction (normalised)
      sizeof obj.m_gForceLateral,       // Lateral G-Force component
      sizeof obj.m_gForceLongitudinal,  // Longitudinal G-Force component
      sizeof obj.m_gForceVertical,      // Vertical G-Force component
      sizeof obj.m_yaw,                 // Yaw angle in radians
      sizeof obj.m_pitch,               // Pitch angle in radians
      sizeof obj.m_roll                 // Roll angle in radians
  };
  return sizes;
};

std::string ExtraCarMotionDataCSVHeader() {
  std::string str =
      "m_suspensionPosition,m_suspensionVelocity,m_suspensionAcceleration,m_wheelSpeed,m_wheelSlip,m_localVelocityX,"
      "m_localVelocityY,m_localVelocityZ,m_angularVelocityX,m_angularVelocityY,m_angularVelocityZ,"
      "m_angularAccelerationX,m_angularAccelerationY,m_angularAccelerationZ,m_frontWheelsAngle";
  return str;
}

std::string ExtraCarMotionDataString(ExtraCarMotionData obj, std::string sep) {
  const char *fmt = "%s%s%s%s%s%s%s%s%s%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f";
  const char *ssep = sep.c_str();
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

  int size = std::snprintf(nullptr, 0, fmt, m_suspensionPosition.c_str(), ssep, m_suspensionVelocity.c_str(), ssep,
                           m_suspensionAcceleration.c_str(), ssep, m_wheelSpeed.c_str(), ssep, m_wheelSlip.c_str(),
                           ssep, obj.m_localVelocityX, ssep, obj.m_localVelocityY, ssep, obj.m_localVelocityZ, ssep,
                           obj.m_angularVelocityX, ssep, obj.m_angularVelocityY, ssep, obj.m_angularVelocityZ, ssep,
                           obj.m_angularAccelerationX, ssep, obj.m_angularAccelerationY, ssep,
                           obj.m_angularAccelerationZ, ssep, obj.m_frontWheelsAngle);

  std::vector<char> buf(size + 1);  // note +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, m_suspensionPosition.c_str(), ssep, m_suspensionVelocity.c_str(), ssep,
                m_suspensionAcceleration.c_str(), ssep, m_wheelSpeed.c_str(), ssep, m_wheelSlip.c_str(), ssep,
                obj.m_localVelocityX, ssep, obj.m_localVelocityY, ssep, obj.m_localVelocityZ, ssep,
                obj.m_angularVelocityX, ssep, obj.m_angularVelocityY, ssep, obj.m_angularVelocityZ, ssep,
                obj.m_angularAccelerationX, ssep, obj.m_angularAccelerationY, ssep, obj.m_angularAccelerationZ, ssep,
                obj.m_frontWheelsAngle);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));

  return str;
}

ExtraCarMotionData ParseExtraCarMotionData(std::vector<std::vector<unsigned char>> bytes) {
  ExtraCarMotionData obj;
  std::uint8_t idx[4] = {0, 1, 2, 3};

  for (std::uint8_t i : idx)
    std::memcpy(&obj.m_suspensionPosition[i], &bytes.at(0).front() + (i * sizeof obj.m_suspensionPosition[i]),
                sizeof obj.m_suspensionPosition[i]);

  for (std::uint8_t i : idx)
    std::memcpy(&obj.m_suspensionVelocity[i], &bytes.at(1).front() + (i * sizeof obj.m_suspensionVelocity[i]),
                sizeof obj.m_suspensionVelocity[i]);

  for (std::uint8_t i : idx)
    std::memcpy(&obj.m_suspensionAcceleration[i], &bytes.at(2).front() + (i * sizeof obj.m_suspensionAcceleration[i]),
                sizeof obj.m_suspensionAcceleration[i]);

  for (std::uint8_t i : idx)
    std::memcpy(&obj.m_wheelSpeed[i], &bytes.at(3).front() + (i * sizeof obj.m_wheelSpeed[i]),
                sizeof obj.m_wheelSpeed[i]);

  for (std::uint8_t i : idx)
    std::memcpy(&obj.m_wheelSlip[i], &bytes.at(4).front() + (i * sizeof obj.m_wheelSlip[i]), sizeof obj.m_wheelSlip[i]);

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

  return obj;
}

std::vector<std::size_t> ExtraCarMotionDataSizes() {
  ExtraCarMotionData obj;
  std::vector<std::size_t> sizes = {
      sizeof obj.m_suspensionPosition,      // Note: All wheel arrays have the
                                            // following order:
      sizeof obj.m_suspensionVelocity,      // RL, RR, FL, FR
      sizeof obj.m_suspensionAcceleration,  // RL, RR, FL, FR
      sizeof obj.m_wheelSpeed,              // Speed of each wheel
      sizeof obj.m_wheelSlip,               // Slip ratio for each wheel
      sizeof obj.m_localVelocityX,          // Velocity in local space
      sizeof obj.m_localVelocityY,          // Velocity in local space
      sizeof obj.m_localVelocityZ,          // Velocity in local space
      sizeof obj.m_angularVelocityX,        // Angular velocity x-component
      sizeof obj.m_angularVelocityY,        // Angular velocity y-component
      sizeof obj.m_angularVelocityZ,        // Angular velocity z-component
      sizeof obj.m_angularAccelerationX,    // Angular velocity x-component
      sizeof obj.m_angularAccelerationY,    // Angular velocity y-component
      sizeof obj.m_angularAccelerationZ,    // Angular velocity z-component
      sizeof obj.m_frontWheelsAngle         // Curent front wheel angle in radians
  };
  return sizes;
}

std::string PacketMotionDataCSVHeader() {
  std::string str = PacketHeaderCSVHeader() + "," + CarMotionDataCSVHeader() + "," + ExtraCarMotionDataCSVHeader();
  return str;
}

std::string PacketMotionDataString(PacketMotionData obj, int carID, std::string sep) {
  std::string str = PacketHeaderString(obj.m_header) + sep + CarMotionDataString(obj.m_carMotionData.at(carID)) + sep +
                    ExtraCarMotionDataString(obj.m_extraCarMotionData);
  return str;
}

PacketMotionData ParsePacketMotionData(std::vector<unsigned char> bytes) {
  PacketMotionData obj;
  std::uint16_t offset;

  // parse header
  offset = 0;
  obj.m_header = ParsePacketHeader(parse_bytes_to_pairs(PacketHeaderSizes(), bytes, offset));

  // parsing the motion data writes directly to object; requires passing by reference
  offset = sizeof(PacketHeader) + (sizeof(CarMotionData) * 22);
  obj.m_extraCarMotionData = ParseExtraCarMotionData(parse_bytes_to_pairs(ExtraCarMotionDataSizes(), bytes, offset));

  // loop over the 22 car data packets and parse them
  for (std::uint8_t i = 0; i < 22; i++) {
    offset = sizeof(PacketHeader) + (sizeof(CarMotionData) * i);
    obj.m_carMotionData.at(i) = ParseCarMotionData(parse_bytes_to_pairs(CarMotionDataSizes(), bytes, offset));
  }

  return obj;
}
