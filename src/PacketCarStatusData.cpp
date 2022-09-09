#include "../include/PacketCarStatusData.hpp"

std::vector<std::size_t> CarStatusDataSizes = {
    sizeof(((CarStatusData *)0)->m_tractionControl),        // Traction control - 0 = off, 1 = medium, 2 = full
    sizeof(((CarStatusData *)0)->m_antiLockBrakes),         // 0 (off) - 1 (on)
    sizeof(((CarStatusData *)0)->m_fuelMix),                // Fuel mix - 0 = lean, 1 = standard, 2 = rich, 3 = max
    sizeof(((CarStatusData *)0)->m_frontBrakeBias),         // Front brake bias (percentage)
    sizeof(((CarStatusData *)0)->m_pitLimiterStatus),       // Pit limiter status - 0 = off, 1 = on
    sizeof(((CarStatusData *)0)->m_fuelInTank),             // Current fuel mass
    sizeof(((CarStatusData *)0)->m_fuelCapacity),           // Fuel capacity
    sizeof(((CarStatusData *)0)->m_fuelRemainingLaps),      // Fuel remaining in terms of laps (value on MFD)
    sizeof(((CarStatusData *)0)->m_maxRPM),                 // Cars max RPM, point of rev limiter
    sizeof(((CarStatusData *)0)->m_idleRPM),                // Cars idle RPM
    sizeof(((CarStatusData *)0)->m_maxGears),               // Maximum number of gears
    sizeof(((CarStatusData *)0)->m_drsAllowed),             // 0 = not allowed, 1 = allowed
    sizeof(((CarStatusData *)0)->m_drsActivationDistance),  // 0 = DRS not available, non-zero - DRS will be
                                                            // available in [X] metres
    sizeof(((CarStatusData *)0)->m_actualTyreCompound),     // F1 Modern - 16 = C5, 17 = C4, 18 = C3, 19 = C2, 20 = C1
                                                            // 7 = inter, 8 = wet
                                                            // F1 Classic - 9 = dry, 10 = wet
                                                            // F2 – 11 = super soft, 12 = soft, 13 = medium, 14 = hard
                                                            // 15 = wet
    sizeof(((CarStatusData *)0)->m_visualTyreCompound),     // F1 visual (can be different from actual compound)
                                                            // 16 = soft, 17 = medium, 18 = hard, 7 = inter, 8 = wet
                                                            // F1 Classic – same as above
                                                            // F2 ‘19, 15 = wet, 19 – super soft, 20 = soft
                                                            // 21 = medium , 22 = hard
    sizeof(((CarStatusData *)0)->m_tyresAgeLaps),           // Age in laps of the current set of tyres
    sizeof(((CarStatusData *)0)->m_vehicleFiaFlags),        // -1 = invalid/unknown, 0 = none, 1 = green
                                                            // 2 = blue, 3 = yellow, 4 = red
    sizeof(((CarStatusData *)0)->m_ersStoreEnergy),         // ERS energy store in Joules
    sizeof(((CarStatusData *)0)->m_ersDeployMode),          // ERS deployment mode, 0 = none, 1 = medium
                                                            // 2 = hotlap, 3 = overtake
    sizeof(((CarStatusData *)0)->m_ersHarvestedThisLapMGUK),  // ERS energy harvested this lap by MGU-K
    sizeof(((CarStatusData *)0)->m_ersHarvestedThisLapMGUH),  // ERS energy harvested this lap by MGU-H
    sizeof(((CarStatusData *)0)->m_ersDeployedThisLap),       // ERS energy deployed this lap
    sizeof(((CarStatusData *)0)->m_networkPaused)             // Whether the car is paused in a network game
};

std::vector<std::string> CarStatusDataNames = {
    "m_tractionControl",          // Traction control - 0 = off, 1 = medium, 2 = full
    "m_antiLockBrakes",           // 0 (off) - 1 (on)
    "m_fuelMix",                  // Fuel mix - 0 = lean, 1 = standard, 2 = rich, 3 = max
    "m_frontBrakeBias",           // Front brake bias (percentage)
    "m_pitLimiterStatus",         // Pit limiter status - 0 = off, 1 = on
    "m_fuelInTank",               // Current fuel mass
    "m_fuelCapacity",             // Fuel capacity
    "m_fuelRemainingLaps",        // Fuel remaining in terms of laps (value on MFD)
    "m_maxRPM",                   // Cars max RPM, point of rev limiter
    "m_idleRPM",                  // Cars idle RPM
    "m_maxGears",                 // Maximum number of gears
    "m_drsAllowed",               // 0 = not allowed, 1 = allowed
    "m_drsActivationDistance",    // 0 = DRS not available, non-zero - DRS will be available
                                  // in [X] metres
    "m_actualTyreCompound",       // F1 Modern - 16 = C5, 17 = C4, 18 = C3, 19 = C2, 20 = C1
                                  // 7 = inter, 8 = wet
                                  // F1 Classic - 9 = dry, 10 = wet
                                  // F2 – 11 = super soft, 12 = soft, 13 = medium, 14 = hard
                                  // 15 = wet
    "m_visualTyreCompound",       // F1 visual (can be different from actual compound)
                                  // 16 = soft, 17 = medium, 18 = hard, 7 = inter, 8 = wet
                                  // F1 Classic – same as above
                                  // F2 ‘19, 15 = wet, 19 – super soft, 20 = soft
                                  // 21 = medium , 22 = hard
    "m_tyresAgeLaps",             // Age in laps of the current set of tyres
    "m_vehicleFiaFlags",          // -1 = invalid/unknown, 0 = none, 1 = green
                                  // 2 = blue, 3 = yellow, 4 = red
    "m_ersStoreEnergy",           // ERS energy store in Joules
    "m_ersDeployMode",            // ERS deployment mode, 0 = none, 1 = medium
                                  // 2 = hotlap, 3 = overtake
    "m_ersHarvestedThisLapMGUK",  // ERS energy harvested this lap by MGU-K
    "m_ersHarvestedThisLapMGUH",  // ERS energy harvested this lap by MGU-H
    "m_ersDeployedThisLap",       // ERS energy deployed this lap
    "m_networkPaused"             // Whether the car is paused in a network game
};

std::string CarStatusDataString(CarStatusData obj, std::string sep) {
  const char *fmt = "%d%s%d%s%d%s%d%s%d%s%f%s%f%s%f%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%f%s%d%s%f%s%f%s%f%s%d";
  const char *ssep = sep.c_str();

  const std::size_t size = std::snprintf(
      nullptr, 0, fmt, obj.m_tractionControl, ssep, obj.m_antiLockBrakes, ssep, obj.m_fuelMix, ssep,
      obj.m_frontBrakeBias, ssep, obj.m_pitLimiterStatus, ssep, obj.m_fuelInTank, ssep, obj.m_fuelCapacity, ssep,
      obj.m_fuelRemainingLaps, ssep, obj.m_maxRPM, ssep, obj.m_idleRPM, ssep, obj.m_maxGears, ssep, obj.m_drsAllowed,
      ssep, obj.m_drsActivationDistance, ssep, obj.m_actualTyreCompound, ssep, obj.m_visualTyreCompound, ssep,
      obj.m_tyresAgeLaps, ssep, obj.m_vehicleFiaFlags, ssep, obj.m_ersStoreEnergy, ssep, obj.m_ersDeployMode, ssep,
      obj.m_ersHarvestedThisLapMGUK, ssep, obj.m_ersHarvestedThisLapMGUH, ssep, obj.m_ersDeployedThisLap, ssep,
      obj.m_networkPaused);

  std::vector<char> buf(size + 1);  // note +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.m_tractionControl, ssep, obj.m_antiLockBrakes, ssep, obj.m_fuelMix, ssep,
                obj.m_frontBrakeBias, ssep, obj.m_pitLimiterStatus, ssep, obj.m_fuelInTank, ssep, obj.m_fuelCapacity,
                ssep, obj.m_fuelRemainingLaps, ssep, obj.m_maxRPM, ssep, obj.m_idleRPM, ssep, obj.m_maxGears, ssep,
                obj.m_drsAllowed, ssep, obj.m_drsActivationDistance, ssep, obj.m_actualTyreCompound, ssep,
                obj.m_visualTyreCompound, ssep, obj.m_tyresAgeLaps, ssep, obj.m_vehicleFiaFlags, ssep,
                obj.m_ersStoreEnergy, ssep, obj.m_ersDeployMode, ssep, obj.m_ersHarvestedThisLapMGUK, ssep,
                obj.m_ersHarvestedThisLapMGUH, ssep, obj.m_ersDeployedThisLap, ssep, obj.m_networkPaused);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));  // remove null terminator

  return str;
}

CarStatusData ParseCarStatusData(std::vector<std::vector<unsigned char>> bytes) {
  CarStatusData obj;
  std::memcpy(&obj.m_tractionControl, &bytes.at(0).front(), sizeof obj.m_tractionControl);
  std::memcpy(&obj.m_antiLockBrakes, &bytes.at(1).front(), sizeof obj.m_antiLockBrakes);
  std::memcpy(&obj.m_fuelMix, &bytes.at(2).front(), sizeof obj.m_fuelMix);
  std::memcpy(&obj.m_frontBrakeBias, &bytes.at(3).front(), sizeof obj.m_frontBrakeBias);
  std::memcpy(&obj.m_pitLimiterStatus, &bytes.at(4).front(), sizeof obj.m_pitLimiterStatus);
  std::memcpy(&obj.m_fuelInTank, &bytes.at(5).front(), sizeof obj.m_fuelInTank);
  std::memcpy(&obj.m_fuelCapacity, &bytes.at(6).front(), sizeof obj.m_fuelCapacity);
  std::memcpy(&obj.m_fuelRemainingLaps, &bytes.at(7).front(), sizeof obj.m_fuelRemainingLaps);
  std::memcpy(&obj.m_maxRPM, &bytes.at(8).front(), sizeof obj.m_maxRPM);
  std::memcpy(&obj.m_idleRPM, &bytes.at(9).front(), sizeof obj.m_idleRPM);
  std::memcpy(&obj.m_maxGears, &bytes.at(10).front(), sizeof obj.m_maxGears);
  std::memcpy(&obj.m_drsAllowed, &bytes.at(11).front(), sizeof obj.m_drsAllowed);
  std::memcpy(&obj.m_drsActivationDistance, &bytes.at(12).front(), sizeof obj.m_drsActivationDistance);
  std::memcpy(&obj.m_actualTyreCompound, &bytes.at(13).front(), sizeof obj.m_actualTyreCompound);
  std::memcpy(&obj.m_visualTyreCompound, &bytes.at(14).front(), sizeof obj.m_visualTyreCompound);
  std::memcpy(&obj.m_tyresAgeLaps, &bytes.at(15).front(), sizeof obj.m_tyresAgeLaps);
  std::memcpy(&obj.m_vehicleFiaFlags, &bytes.at(16).front(), sizeof obj.m_vehicleFiaFlags);
  std::memcpy(&obj.m_ersStoreEnergy, &bytes.at(17).front(), sizeof obj.m_ersStoreEnergy);
  std::memcpy(&obj.m_ersDeployMode, &bytes.at(17).front(), sizeof obj.m_ersDeployMode);
  std::memcpy(&obj.m_ersHarvestedThisLapMGUK, &bytes.at(17).front(), sizeof obj.m_ersHarvestedThisLapMGUK);
  std::memcpy(&obj.m_ersHarvestedThisLapMGUH, &bytes.at(17).front(), sizeof obj.m_ersHarvestedThisLapMGUH);
  std::memcpy(&obj.m_ersDeployedThisLap, &bytes.at(17).front(), sizeof obj.m_ersDeployedThisLap);
  std::memcpy(&obj.m_networkPaused, &bytes.at(17).front(), sizeof obj.m_networkPaused);
  return obj;
}

std::string PacketCarStatusDataCSVHeader(std::string sep, std::string compr) {
  std::vector<std::string> vec = {
      vpaste(PacketHeaderNames, sep),   //
      vpaste(CarStatusDataNames, sep),  //
  };
  return vpaste(vec, sep);
}

template <>
std::string packetDataString(PacketCarStatusData obj, std::uint8_t id, std::string sep, std::string compr,
                             std::string compr2) {
  std::vector<std::string> vec = {
      PacketHeaderString(obj.m_header),              //
      CarStatusDataString(obj.m_carStatusData[id]),  //
  };
  return vpaste(vec, sep);
}

template <>
PacketCarStatusData parsePacketData<PacketCarStatusData>(std::vector<unsigned char> bytes) {
  PacketCarStatusData obj;
  std::uint16_t offset = 0;

  // parse header
  obj.m_header = ParsePacketHeader(parse_bytes_to_vec(PacketHeaderSizes, bytes, offset));
  offset += sizeof(PacketHeader);

  // loop over the 22 car data packets and parse them
  for (std::uint8_t i = 0; i < 22; i++) {
    obj.m_carStatusData[i] = ParseCarStatusData(parse_bytes_to_vec(CarStatusDataSizes, bytes, offset));
    offset += sizeof(CarStatusData);
  }

  return obj;
}
