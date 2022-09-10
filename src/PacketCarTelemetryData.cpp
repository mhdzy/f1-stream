#include "../include/PacketCarTelemetryData.hpp"

template <>
std::vector<std::size_t> pSizes<CarTelemetryData>() {
  return std::vector<std::size_t>{
      sizeof(((CarTelemetryData *)0)->m_speed),             // Speed of car in kilometres per hour
      sizeof(((CarTelemetryData *)0)->m_throttle),          // Amount of throttle applied (0.0 to 1.0)
      sizeof(((CarTelemetryData *)0)->m_steer),             // Steering (-1.0 (full lock left) to 1.0 (full lock right))
      sizeof(((CarTelemetryData *)0)->m_brake),             // Amount of brake applied (0.0 to 1.0)
      sizeof(((CarTelemetryData *)0)->m_clutch),            // Amount of clutch applied (0 to 100)
      sizeof(((CarTelemetryData *)0)->m_gear),              // Gear selected (1-8, N=0, R=-1)
      sizeof(((CarTelemetryData *)0)->m_engineRPM),         // Engine RPM
      sizeof(((CarTelemetryData *)0)->m_drs),               // 0 = off, 1 = on
      sizeof(((CarTelemetryData *)0)->m_revLightsPercent),  // Rev lights indicator (percentage)
      sizeof(
          ((CarTelemetryData *)0)->m_revLightsBitValue),  // Rev lights (bit 0 = leftmost LED, bit 14 = rightmost LED)
      sizeof(((CarTelemetryData *)0)->m_brakesTemperature),        // Brakes temperature (celsius)
      sizeof(((CarTelemetryData *)0)->m_tyresSurfaceTemperature),  // Tyres surface temperature (celsius)
      sizeof(((CarTelemetryData *)0)->m_tyresInnerTemperature),    // Tyres inner temperature (celsius)
      sizeof(((CarTelemetryData *)0)->m_engineTemperature),        // Engine temperature (celsius)
      sizeof(((CarTelemetryData *)0)->m_tyresPressure),            // Tyres pressure (PSI)
      sizeof(((CarTelemetryData *)0)->m_surfaceType)               // Driving surface, see appendices
  };
}

template <>
std::vector<std::string> pNames<CarTelemetryData>() {
  return std::vector<std::string>{
      "m_speed",                    // Speed of car in kilometres per hour
      "m_throttle",                 // Amount of throttle applied (0.0 to 1.0)
      "m_steer",                    // Steering (-1.0 (full lock left) to 1.0 (full lock right))
      "m_brake",                    // Amount of brake applied (0.0 to 1.0)
      "m_clutch",                   // Amount of clutch applied (0 to 100)
      "m_gear",                     // Gear selected (1-8, N=0, R=-1)
      "m_engineRPM",                // Engine RPM
      "m_drs",                      // 0 = off, 1 = on
      "m_revLightsPercent",         // Rev lights indicator (percentage)
      "m_revLightsBitValue",        // Rev lights (bit 0 = leftmost LED, bit 14 = rightmost LED)
      "m_brakesTemperature",        // Brakes temperature (celsius)
      "m_tyresSurfaceTemperature",  // Tyres surface temperature (celsius)
      "m_tyresInnerTemperature",    // Tyres inner temperature (celsius)
      "m_engineTemperature",        // Engine temperature (celsius)
      "m_tyresPressure",            // Tyres pressure (PSI)
      "m_surfaceType"               // Driving surface, see appendices
  };
}

template <>
std::vector<std::size_t> pSizes<CarTelemetryPanel>() {
  return std::vector<std::size_t>{
      sizeof(((CarTelemetryPanel *)0)->m_mfdPanelIndex),  // Index of MFD panel open - 255 = MFD closed
                                                          // Single player, race – 0 = Car setup, 1 = Pits
                                                          // 2 = Damage, 3 =  Engine, 4 = Temperatures
                                                          // May vary depending on game mode
      sizeof(((CarTelemetryPanel *)0)->m_mfdPanelIndexSecondaryPlayer),  // See above
      sizeof(((CarTelemetryPanel *)0)->m_suggestedGear)                  // Suggested gear for the player (1-8)
                                                                         // 0 if no gear suggested
  };
}

template <>
std::vector<std::string> pNames<CarTelemetryPanel>() {
  return std::vector<std::string>{
      "m_mfdPanelIndex",                 // Index of MFD panel open - 255 = MFD closed
                                         // Single player, race – 0 = Car setup, 1 = Pits
                                         // 2 = Damage, 3 =  Engine, 4 = Temperatures
                                         // May vary depending on game mode
      "m_mfdPanelIndexSecondaryPlayer",  // See above
      "m_suggestedGear"                  // Suggested gear for the player (1-8)
                                         // 0 if no gear suggested
  };
}

template <>
std::string subpacketDataString(CarTelemetryData obj, std::string sep) {
  const char *fmt = "%d%s%f%s%f%s%f%s%d%s%d%s%d%s%d%s%d%s%d%s%s%s%s%s%s%s%d%s%s%s%s";
  const char *ssep = sep.c_str();
  const std::string csep = "/";

  std::string m_brakesTemperature(vpaste(
      std::vector<std::string>{
          std::to_string(obj.m_brakesTemperature[0]),  //
          std::to_string(obj.m_brakesTemperature[1]),  //
          std::to_string(obj.m_brakesTemperature[2]),  //
          std::to_string(obj.m_brakesTemperature[3])   //
      },
      csep));

  std::string m_tyresSurfaceTemperature(vpaste(
      std::vector<std::string>{
          std::to_string(obj.m_tyresSurfaceTemperature[0]),  //
          std::to_string(obj.m_tyresSurfaceTemperature[1]),  //
          std::to_string(obj.m_tyresSurfaceTemperature[2]),  //
          std::to_string(obj.m_tyresSurfaceTemperature[3])   //
      },
      csep));

  std::string m_tyresInnerTemperature(vpaste(
      std::vector<std::string>{
          std::to_string(obj.m_tyresInnerTemperature[0]),  //
          std::to_string(obj.m_tyresInnerTemperature[1]),  //
          std::to_string(obj.m_tyresInnerTemperature[2]),  //
          std::to_string(obj.m_tyresInnerTemperature[3])   //
      },
      csep));

  std::string m_tyresPressure(vpaste(
      std::vector<std::string>{
          ftos(obj.m_tyresPressure[0]),  //
          ftos(obj.m_tyresPressure[1]),  //
          ftos(obj.m_tyresPressure[2]),  //
          ftos(obj.m_tyresPressure[3])   //
      },
      csep));

  std::string m_surfaceType(vpaste(
      std::vector<std::string>{
          std::to_string(obj.m_surfaceType[0]),  //
          std::to_string(obj.m_surfaceType[1]),  //
          std::to_string(obj.m_surfaceType[2]),  //
          std::to_string(obj.m_surfaceType[3])   //
      },
      csep));

  const std::size_t size =
      std::snprintf(nullptr, 0, fmt, obj.m_speed, ssep, obj.m_throttle, ssep, obj.m_steer, ssep, obj.m_brake, ssep,
                    obj.m_clutch, ssep, obj.m_gear, ssep, obj.m_engineRPM, ssep, obj.m_drs, ssep,
                    obj.m_revLightsPercent, ssep, obj.m_revLightsBitValue, ssep, m_brakesTemperature.c_str(), ssep,
                    m_tyresSurfaceTemperature.c_str(), ssep, m_tyresInnerTemperature.c_str(), ssep,
                    obj.m_engineTemperature, ssep, m_tyresPressure.c_str(), ssep, m_surfaceType.c_str());

  std::vector<char> buf(size + 1);  // note +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.m_speed, ssep, obj.m_throttle, ssep, obj.m_steer, ssep, obj.m_brake, ssep,
                obj.m_clutch, ssep, obj.m_gear, ssep, obj.m_engineRPM, ssep, obj.m_drs, ssep, obj.m_revLightsPercent,
                ssep, obj.m_revLightsBitValue, ssep, m_brakesTemperature.c_str(), ssep,
                m_tyresSurfaceTemperature.c_str(), ssep, m_tyresInnerTemperature.c_str(), ssep, obj.m_engineTemperature,
                ssep, m_tyresPressure.c_str(), ssep, m_surfaceType.c_str());

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));

  return str;
}

template <>
CarTelemetryData parseSubpacketData<CarTelemetryData>(std::vector<std::vector<unsigned char>> bytes) {
  CarTelemetryData obj;
  std::uint8_t idx[4] = {0, 1, 2, 3};

  std::memcpy(&obj.m_speed, &bytes.at(0).front(), sizeof obj.m_speed);
  std::memcpy(&obj.m_throttle, &bytes.at(1).front(), sizeof obj.m_throttle);
  std::memcpy(&obj.m_steer, &bytes.at(2).front(), sizeof obj.m_steer);
  std::memcpy(&obj.m_brake, &bytes.at(3).front(), sizeof obj.m_brake);
  std::memcpy(&obj.m_clutch, &bytes.at(4).front(), sizeof obj.m_clutch);
  std::memcpy(&obj.m_gear, &bytes.at(5).front(), sizeof obj.m_gear);
  std::memcpy(&obj.m_engineRPM, &bytes.at(6).front(), sizeof obj.m_engineRPM);
  std::memcpy(&obj.m_drs, &bytes.at(7).front(), sizeof obj.m_drs);
  std::memcpy(&obj.m_revLightsPercent, &bytes.at(8).front(), sizeof obj.m_revLightsPercent);
  std::memcpy(&obj.m_revLightsBitValue, &bytes.at(9).front(), sizeof obj.m_revLightsBitValue);

  for (std::uint8_t i : idx)
    std::memcpy(&obj.m_brakesTemperature[i], &bytes.at(10).front() + (i * sizeof obj.m_brakesTemperature[i]),
                sizeof obj.m_brakesTemperature[i]);

  for (std::uint8_t i : idx)
    std::memcpy(&obj.m_tyresSurfaceTemperature[i],
                &bytes.at(11).front() + (i * sizeof obj.m_tyresSurfaceTemperature[i]),
                sizeof obj.m_tyresSurfaceTemperature[i]);

  for (std::uint8_t i : idx)
    std::memcpy(&obj.m_tyresInnerTemperature[i], &bytes.at(12).front() + (i * sizeof obj.m_tyresInnerTemperature[i]),
                sizeof obj.m_tyresInnerTemperature[i]);

  std::memcpy(&obj.m_engineTemperature, &bytes.at(13).front(), sizeof obj.m_engineTemperature);

  for (std::uint8_t i : idx)
    std::memcpy(&obj.m_tyresPressure[i], &bytes.at(14).front() + (i * sizeof obj.m_tyresPressure[i]),
                sizeof obj.m_tyresPressure[i]);

  for (std::uint8_t i : idx)
    std::memcpy(&obj.m_surfaceType[i], &bytes.at(15).front() + (i * sizeof obj.m_surfaceType[i]),
                sizeof obj.m_surfaceType[i]);

  return obj;
}

template <>
std::string subpacketDataString(CarTelemetryPanel obj, std::string sep) {
  const char *fmt = "%d%s%d%s%d";
  const char *ssep = sep.c_str();

  const std::size_t size = std::snprintf(nullptr, 0, fmt, obj.m_mfdPanelIndex, ssep, obj.m_mfdPanelIndexSecondaryPlayer,
                                         ssep, obj.m_suggestedGear);

  std::vector<char> buf(size + 1);  // +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.m_mfdPanelIndex, ssep, obj.m_mfdPanelIndexSecondaryPlayer, ssep,
                obj.m_suggestedGear);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));  // remove null terminator

  return str;
}

template <>
CarTelemetryPanel parseSubpacketData<CarTelemetryPanel>(std::vector<std::vector<unsigned char>> bytes) {
  CarTelemetryPanel obj;
  std::memcpy(&obj.m_mfdPanelIndex, &bytes.at(0).front(), sizeof obj.m_mfdPanelIndex);
  std::memcpy(&obj.m_mfdPanelIndexSecondaryPlayer, &bytes.at(1).front(), sizeof obj.m_mfdPanelIndexSecondaryPlayer);
  std::memcpy(&obj.m_suggestedGear, &bytes.at(1).front(), sizeof obj.m_suggestedGear);
  return obj;
}

template <>
std::string packetDataHeader<PacketCarTelemetryData>(std::string sep, std::string compr) {
  std::vector<std::string> vec = {
      vpaste(pNames<PacketHeader>(), sep),      //
      vpaste(pNames<CarTelemetryData>(), sep),  //
      vpaste(pNames<CarTelemetryPanel>(), sep)  //
  };

  return vpaste(vec, sep);
}

template <>
std::string packetDataString(PacketCarTelemetryData obj, std::uint8_t id, std::string sep, std::string compr,
                             std::string compr2) {
  std::vector<std::string> vec = {
      subpacketDataString(obj.m_header),                //
      subpacketDataString(obj.m_carTelemetryData[id]),  //
      subpacketDataString(obj.m_carTelemetryPanel)      //
  };
  return vpaste(vec, sep);
}

template <>
PacketCarTelemetryData parsePacketData<PacketCarTelemetryData>(std::vector<unsigned char> bytes) {
  PacketCarTelemetryData obj;
  std::uint16_t offset = 0;

  // parse header
  obj.m_header = parseSubpacketDataT<PacketHeader>(bytes, offset);
  offset += sizeof(PacketHeader);

  // loop over the 22 car data packets and parse them
  for (std::uint8_t i = 0; i < 22; i++) {
    obj.m_carTelemetryData[i] = parseSubpacketDataT<CarTelemetryData>(bytes, offset);
    offset += sizeof(CarTelemetryData);
  }

  // parse extra player car data
  obj.m_carTelemetryPanel = parseSubpacketDataT<CarTelemetryPanel>(bytes, offset);

  return obj;
}
