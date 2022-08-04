#include "PacketMotionData.hpp"

std::string CarMotionDataCSVHeader() {
  std::string str =
      "m_worldPositionX,m_worldPositionY,m_worldPositionZ,m_worldVelocityX,m_worldVelocityY,m_"
      "worldVelocityZ,m_"
      "worldForwardDirX,m_worldForwardDirY,m_worldForwardDirZ,m_worldRightDirX,m_worldRightDirY,m_worldRightDirZ,m_"
      "gForceLateral,m_gForceLongitudinal,m_gForceVertical,m_yaw,m_pitch,m_roll";

  return str;
}

std::string ExtraCarMotionDataCSVHeader() {
  std::string str =
      "m_suspensionPosition,m_suspensionVelocity,m_suspensionAcceleration,m_wheelSpeed,m_wheelSlip,m_localVelocityX,"
      "m_localVelocityY,m_localVelocityZ,m_angularVelocityX,m_angularVelocityY,m_angularVelocityZ,"
      "m_angularAccelerationX,m_angularAccelerationY,m_angularAccelerationZ,m_frontWheelsAngle";

  return str;
}

std::string PacketMotionDataCSVHeader() {
  std::string str = PacketHeaderCSVHeader() + "," + CarMotionDataCSVHeader() + "," + ExtraCarMotionDataCSVHeader();
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

std::string PacketMotionDataString(PacketMotionData obj, int carID, std::string sep) {
  std::string str = PacketHeaderString(obj.m_header) + sep + CarMotionDataString(obj.m_carMotionData.at(carID)) + sep +
                    ExtraCarMotionDataString(obj.m_extraCarMotionData);

  return str;
}

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
}

ExtraCarMotionData ParseExtraCarMotionData(std::vector<std::vector<unsigned char>> bytes) {
  ExtraCarMotionData obj;
  std::uint8_t idx[4] = {0, 1, 2, 3};

  for (std::uint8_t i : idx)
    std::memcpy(&obj.m_suspensionPosition[i], &bytes.at(0).front() + i * sizeof(float), sizeof(float));
  
  for (std::uint8_t i : idx)
    std::memcpy(&obj.m_suspensionVelocity[i], &bytes.at(1).front() + i * sizeof(float), sizeof(float));
  
  for (std::uint8_t i : idx)
    std::memcpy(&obj.m_suspensionAcceleration[i], &bytes.at(2).front() + i * sizeof(float), sizeof(float));
  
  for (std::uint8_t i : idx) std::memcpy(&obj.m_wheelSpeed[i], &bytes.at(3).front() + i * sizeof(float), sizeof(float));
  
  for (std::uint8_t i : idx) std::memcpy(&obj.m_wheelSlip[i], &bytes.at(4).front() + i * sizeof(float), sizeof(float));

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

PacketMotionData ParsePacketMotionData(std::vector<unsigned char> bytes) {
  PacketMotionData obj;
  int offset;

  // parse header
  offset = 0L;
  obj.m_header = ParsePacketHeader(parse_bytes_to_pairs(PacketHeaderPairs, bytes, offset));

  // parsing the motion data writes directly to object; requires passing by reference
  offset = sizeof(PacketHeader) + (sizeof(CarMotionData) * 22);
  obj.m_extraCarMotionData = ParseExtraCarMotionData(parse_bytes_to_pairs(ExtraCarMotionDataPairs, bytes, offset));

  // loop over the 22 car data packets and parse them
  for (int i = 0; i < 22; i++) {
    offset = sizeof(PacketHeader) + (sizeof(CarMotionData) * i);
    obj.m_carMotionData.at(i) = ParseCarMotionData(parse_bytes_to_pairs(CarMotionDataPairs, bytes, offset));
  }

  return obj;
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

std::vector<std::pair<int, std::string>> ExtraCarMotionDataPairs = {
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
