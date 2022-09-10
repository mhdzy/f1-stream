#include "../include/PacketCarSetupData.hpp"

template <>
std::vector<std::size_t> pSizes<CarSetupData>() {
  return std::vector<std::size_t>{
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
}

template <>
std::vector<std::string> pNames<CarSetupData>() {
  return std::vector<std::string>{
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
}

template <>
std::string subpacketDataString(CarSetupData obj, std::string sep) {
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
  std::memcpy(&obj.m_frontWing, &bytes.at(0).front(), sizeof obj.m_frontWing);
  std::memcpy(&obj.m_rearWing, &bytes.at(1).front(), sizeof obj.m_rearWing);
  std::memcpy(&obj.m_onThrottle, &bytes.at(2).front(), sizeof obj.m_onThrottle);
  std::memcpy(&obj.m_offThrottle, &bytes.at(3).front(), sizeof obj.m_offThrottle);
  std::memcpy(&obj.m_frontCamber, &bytes.at(4).front(), sizeof obj.m_frontCamber);
  std::memcpy(&obj.m_rearCamber, &bytes.at(5).front(), sizeof obj.m_rearCamber);
  std::memcpy(&obj.m_frontToe, &bytes.at(6).front(), sizeof obj.m_frontToe);
  std::memcpy(&obj.m_rearToe, &bytes.at(7).front(), sizeof obj.m_rearToe);
  std::memcpy(&obj.m_frontSuspension, &bytes.at(8).front(), sizeof obj.m_frontSuspension);
  std::memcpy(&obj.m_rearSuspension, &bytes.at(9).front(), sizeof obj.m_rearSuspension);
  std::memcpy(&obj.m_frontAntiRollBar, &bytes.at(10).front(), sizeof obj.m_frontAntiRollBar);
  std::memcpy(&obj.m_rearAntiRollBar, &bytes.at(11).front(), sizeof obj.m_rearAntiRollBar);
  std::memcpy(&obj.m_frontSuspensionHeight, &bytes.at(12).front(), sizeof obj.m_frontSuspensionHeight);
  std::memcpy(&obj.m_rearSuspensionHeight, &bytes.at(13).front(), sizeof obj.m_rearSuspensionHeight);
  std::memcpy(&obj.m_brakePressure, &bytes.at(14).front(), sizeof obj.m_brakePressure);
  std::memcpy(&obj.m_brakeBias, &bytes.at(15).front(), sizeof obj.m_brakeBias);
  std::memcpy(&obj.m_rearLeftTyrePressure, &bytes.at(16).front(), sizeof obj.m_rearLeftTyrePressure);
  std::memcpy(&obj.m_rearRightTyrePressure, &bytes.at(17).front(), sizeof obj.m_rearRightTyrePressure);
  std::memcpy(&obj.m_frontLeftTyrePressure, &bytes.at(18).front(), sizeof obj.m_frontLeftTyrePressure);
  std::memcpy(&obj.m_frontRightTyrePressure, &bytes.at(19).front(), sizeof obj.m_frontRightTyrePressure);
  std::memcpy(&obj.m_ballast, &bytes.at(20).front(), sizeof obj.m_ballast);
  std::memcpy(&obj.m_fuelLoad, &bytes.at(21).front(), sizeof obj.m_fuelLoad);
  return obj;
}

template <>
std::string packetDataHeader<PacketCarSetupData>(std::string sep, std::string compr) {
  std::vector<std::string> vec = {
      vpaste(pNames<PacketHeader>(), sep),  //
      vpaste(pNames<CarSetupData>(), sep)   //
  };

  return vpaste(vec, sep);
}

template <>
std::string packetDataString(PacketCarSetupData obj, std::uint8_t id, std::string sep, std::string compr,
                             std::string compr2) {
  std::vector<std::string> vec = {
      subpacketDataString(obj.m_header),        //
      subpacketDataString(obj.m_carSetups[id])  //
  };
  return vpaste(vec, sep);
}

template <>
PacketCarSetupData parsePacketData<PacketCarSetupData>(std::vector<unsigned char> bytes) {
  PacketCarSetupData obj;
  std::uint16_t offset = 0;

  obj.m_header = parseSubpacketDataT<PacketHeader>(bytes, offset);
  offset += sizeof(PacketHeader);

  // iterate over all car indices
  for (std::uint8_t i = 0; i < 22; i++) {
    obj.m_carSetups[i] = parseSubpacketDataT<CarSetupData>(bytes, offset);
    offset += sizeof(CarSetupData);
  }

  return obj;
}
