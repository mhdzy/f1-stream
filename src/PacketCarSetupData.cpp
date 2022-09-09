#include "../include/PacketCarSetupData.hpp"

std::vector<std::size_t> CarSetupDataSizes = {
    sizeof(((CarSetupData *)0)->m_frontWing),               // Front wing aero
    sizeof(((CarSetupData *)0)->m_rearWing),                // Rear wing aero
    sizeof(((CarSetupData *)0)->m_onThrottle),              // Differential adjustment on throttle (percentage)
    sizeof(((CarSetupData *)0)->m_offThrottle),             // Differential adjustment off throttle (percentage)
    sizeof(((CarSetupData *)0)->m_frontCamber),             // Front camber angle (suspension geometry)
    sizeof(((CarSetupData *)0)->m_rearCamber),              // Rear camber angle (suspension geometry)
    sizeof(((CarSetupData *)0)->m_frontToe),                // Front toe angle (suspension geometry)
    sizeof(((CarSetupData *)0)->m_rearToe),                 // Rear toe angle (suspension geometry)
    sizeof(((CarSetupData *)0)->m_frontSuspension),         // Front suspension
    sizeof(((CarSetupData *)0)->m_rearSuspension),          // Rear suspension
    sizeof(((CarSetupData *)0)->m_frontAntiRollBar),        // Front anti-roll bar
    sizeof(((CarSetupData *)0)->m_rearAntiRollBar),         // Front anti-roll bar
    sizeof(((CarSetupData *)0)->m_frontSuspensionHeight),   // Front ride height
    sizeof(((CarSetupData *)0)->m_rearSuspensionHeight),    // Rear ride height
    sizeof(((CarSetupData *)0)->m_brakePressure),           // Brake pressure (percentage)
    sizeof(((CarSetupData *)0)->m_brakeBias),               // Brake bias (percentage)
    sizeof(((CarSetupData *)0)->m_rearLeftTyrePressure),    // Rear left tyre pressure (PSI)
    sizeof(((CarSetupData *)0)->m_rearRightTyrePressure),   // Rear right tyre pressure (PSI)
    sizeof(((CarSetupData *)0)->m_frontLeftTyrePressure),   // Front left tyre pressure (PSI)
    sizeof(((CarSetupData *)0)->m_frontRightTyrePressure),  // Front right tyre pressure (PSI)
    sizeof(((CarSetupData *)0)->m_ballast),                 // Ballast
    sizeof(((CarSetupData *)0)->m_fuelLoad)                 // Fuel load
};

std::vector<std::string> CarSetupDataNames = {
    "m_frontWing",               // Front wing aero
    "m_rearWing",                // Rear wing aero
    "m_onThrottle",              // Differential adjustment on throttle (percentage)
    "m_offThrottle",             // Differential adjustment off throttle (percentage)
    "m_frontCamber",             // Front camber angle (suspension geometry)
    "m_rearCamber",              // Rear camber angle (suspension geometry)
    "m_frontToe",                // Front toe angle (suspension geometry)
    "m_rearToe",                 // Rear toe angle (suspension geometry)
    "m_frontSuspension",         // Front suspension
    "m_rearSuspension",          // Rear suspension
    "m_frontAntiRollBar",        // Front anti-roll bar
    "m_rearAntiRollBar",         // Front anti-roll bar
    "m_frontSuspensionHeight",   // Front ride height
    "m_rearSuspensionHeight",    // Rear ride height
    "m_brakePressure",           // Brake pressure (percentage)
    "m_brakeBias",               // Brake bias (percentage)
    "m_rearLeftTyrePressure",    // Rear left tyre pressure (PSI)
    "m_rearRightTyrePressure",   // Rear right tyre pressure (PSI)
    "m_frontLeftTyrePressure",   // Front left tyre pressure (PSI)
    "m_frontRightTyrePressure",  // Front right tyre pressure (PSI)
    "m_ballast",                 // Ballast
    "m_fuelLoad"                 // Fuel load
};

std::string CarSetupDataString(CarSetupData obj, std::string sep) {
  const char *fmt = "%d%s%d%s%d%s%d%s%f%s%f%s%f%s%f%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%f%s%f%s%f%s%f%s%d%s%f";
  const char *ssep = sep.c_str();

  const std::size_t size = std::snprintf(
      nullptr, 0, fmt, obj.m_frontWing, ssep, obj.m_rearWing, ssep, obj.m_onThrottle, ssep, obj.m_offThrottle, ssep,
      obj.m_frontCamber, ssep, obj.m_rearCamber, ssep, obj.m_frontToe, ssep, obj.m_rearToe, ssep, obj.m_frontSuspension,
      ssep, obj.m_rearSuspension, ssep, obj.m_frontAntiRollBar, ssep, obj.m_rearAntiRollBar, ssep,
      obj.m_frontSuspensionHeight, ssep, obj.m_rearSuspensionHeight, ssep, obj.m_brakePressure, ssep, obj.m_brakeBias,
      ssep, obj.m_rearLeftTyrePressure, ssep, obj.m_rearRightTyrePressure, ssep, obj.m_frontLeftTyrePressure, ssep,
      obj.m_frontRightTyrePressure, ssep, obj.m_ballast, ssep, obj.m_fuelLoad);

  std::vector<char> buf(size + 1);  // +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.m_frontWing, ssep, obj.m_rearWing, ssep, obj.m_onThrottle, ssep,
                obj.m_offThrottle, ssep, obj.m_frontCamber, ssep, obj.m_rearCamber, ssep, obj.m_frontToe, ssep,
                obj.m_rearToe, ssep, obj.m_frontSuspension, ssep, obj.m_rearSuspension, ssep, obj.m_frontAntiRollBar,
                ssep, obj.m_rearAntiRollBar, ssep, obj.m_frontSuspensionHeight, ssep, obj.m_rearSuspensionHeight, ssep,
                obj.m_brakePressure, ssep, obj.m_brakeBias, ssep, obj.m_rearLeftTyrePressure, ssep,
                obj.m_rearRightTyrePressure, ssep, obj.m_frontLeftTyrePressure, ssep, obj.m_frontRightTyrePressure,
                ssep, obj.m_ballast, ssep, obj.m_fuelLoad);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));  // remove null terminator

  return str;
}

template <>
CarSetupData parseSubpacketData<CarSetupData>(std::vector<std::vector<unsigned char>> bytes) {
  CarSetupData obj;
  std::memcpy(&obj.m_frontWing, &bytes.at(0).front(), CarSetupDataSizes.at(0));
  std::memcpy(&obj.m_rearWing, &bytes.at(1).front(), CarSetupDataSizes.at(1));
  std::memcpy(&obj.m_onThrottle, &bytes.at(2).front(), CarSetupDataSizes.at(2));
  std::memcpy(&obj.m_offThrottle, &bytes.at(3).front(), CarSetupDataSizes.at(3));
  std::memcpy(&obj.m_frontCamber, &bytes.at(4).front(), CarSetupDataSizes.at(4));
  std::memcpy(&obj.m_rearCamber, &bytes.at(5).front(), CarSetupDataSizes.at(5));
  std::memcpy(&obj.m_frontToe, &bytes.at(6).front(), CarSetupDataSizes.at(6));
  std::memcpy(&obj.m_rearToe, &bytes.at(7).front(), CarSetupDataSizes.at(7));
  std::memcpy(&obj.m_frontSuspension, &bytes.at(8).front(), CarSetupDataSizes.at(8));
  std::memcpy(&obj.m_rearSuspension, &bytes.at(9).front(), CarSetupDataSizes.at(9));
  std::memcpy(&obj.m_frontAntiRollBar, &bytes.at(10).front(), CarSetupDataSizes.at(10));
  std::memcpy(&obj.m_rearAntiRollBar, &bytes.at(11).front(), CarSetupDataSizes.at(11));
  std::memcpy(&obj.m_frontSuspensionHeight, &bytes.at(12).front(), CarSetupDataSizes.at(12));
  std::memcpy(&obj.m_rearSuspensionHeight, &bytes.at(13).front(), CarSetupDataSizes.at(13));
  std::memcpy(&obj.m_brakePressure, &bytes.at(14).front(), CarSetupDataSizes.at(14));
  std::memcpy(&obj.m_brakeBias, &bytes.at(15).front(), CarSetupDataSizes.at(15));
  std::memcpy(&obj.m_rearLeftTyrePressure, &bytes.at(16).front(), CarSetupDataSizes.at(16));
  std::memcpy(&obj.m_rearRightTyrePressure, &bytes.at(17).front(), CarSetupDataSizes.at(17));
  std::memcpy(&obj.m_frontLeftTyrePressure, &bytes.at(18).front(), CarSetupDataSizes.at(18));
  std::memcpy(&obj.m_frontRightTyrePressure, &bytes.at(19).front(), CarSetupDataSizes.at(19));
  std::memcpy(&obj.m_ballast, &bytes.at(20).front(), CarSetupDataSizes.at(20));
  std::memcpy(&obj.m_fuelLoad, &bytes.at(21).front(), CarSetupDataSizes.at(21));
  return obj;
}

std::string PacketCarSetupDataCSVHeader(std::string sep, std::string compr) {
  std::vector<std::string> vec = {
      vpaste(PacketHeaderNames, sep),  //
      vpaste(CarSetupDataNames, sep)   //
  };

  return vpaste(vec, sep);
}

template <>
std::string packetDataString(PacketCarSetupData obj, std::uint8_t id, std::string sep, std::string compr,
                             std::string compr2) {
  std::vector<std::string> vec = {
      PacketHeaderString(obj.m_header),        //
      CarSetupDataString(obj.m_carSetups[id])  //
  };
  return vpaste(vec, sep);
}

template <>
PacketCarSetupData parsePacketData<PacketCarSetupData>(std::vector<unsigned char> bytes) {
  PacketCarSetupData obj;
  std::uint16_t offset = 0;

  obj.m_header = parseSubpacketData<PacketHeader>(parseBytes(PacketHeaderSizes, bytes, offset));
  offset += sizeof(PacketHeader);

  // iterate over all car indices
  for (std::uint8_t i = 0; i < 22; i++) {
    obj.m_carSetups[i] = parseSubpacketData<CarSetupData>(parseBytes(CarSetupDataSizes, bytes, offset));
    offset += sizeof(CarSetupData);
  }

  return obj;
}
