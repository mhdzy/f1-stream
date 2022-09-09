#include "../include/PacketFinalClassificationData.hpp"

std::vector<std::size_t> FinalClassificationDataSizes = {
    sizeof(((FinalClassificationData *)0)->m_position),         // Finishing position
    sizeof(((FinalClassificationData *)0)->m_numLaps),          // Number of laps completed
    sizeof(((FinalClassificationData *)0)->m_gridPosition),     // Grid position of the car
    sizeof(((FinalClassificationData *)0)->m_points),           // Number of points scored
    sizeof(((FinalClassificationData *)0)->m_numPitStops),      // Number of pit stops made
    sizeof(((FinalClassificationData *)0)->m_resultStatus),     // Result status - 0 = invalid, 1 = inactive, 2 = active
                                                                // 3 = finished, 4 = didnotfinish, 5 = disqualified
                                                                // 6 = not classified, 7 = retired
    sizeof(((FinalClassificationData *)0)->m_bestLapTimeInMS),  // Best lap time of the session in milliseconds
    sizeof(((FinalClassificationData *)0)->m_totalRaceTime),    // Total race time in seconds without penalties
    sizeof(((FinalClassificationData *)0)->m_penaltiesTime),    // Total penalties accumulated in seconds
    sizeof(((FinalClassificationData *)0)->m_numPenalties),     // Number of penalties applied to this driver
    sizeof(((FinalClassificationData *)0)->m_numTyreStints),    // Number of tyres stints up to maximum
    sizeof(((FinalClassificationData *)0)->m_tyreStintsActual),  // Actual tyres used by this driver
    sizeof(((FinalClassificationData *)0)->m_tyreStintsVisual),  // Visual tyres used by this driver
    sizeof(((FinalClassificationData *)0)->m_tyreStintsEndLaps)  // The lap number stints end on
};

std::vector<std::string> FinalClassificationDataNames = {
    "m_position",           // Finishing position
    "m_numLaps",            // Number of laps completed
    "m_gridPosition",       // Grid position of the car
    "m_points",             // Number of points scored
    "m_numPitStops",        // Number of pit stops made
    "m_resultStatus",       // Result status - 0 = invalid, 1 = inactive, 2 = active
                            // 3 = finished, 4 = didnotfinish, 5 = disqualified
                            // 6 = not classified, 7 = retired
    "m_bestLapTimeInMS",    // Best lap time of the session in milliseconds
    "m_totalRaceTime",      // Total race time in seconds without penalties
    "m_penaltiesTime",      // Total penalties accumulated in seconds
    "m_numPenalties",       // Number of penalties applied to this driver
    "m_numTyreStints",      // Number of tyres stints up to maximum
    "m_tyreStintsActual",   // Actual tyres used by this driver
    "m_tyreStintsVisual",   // Visual tyres used by this driver
    "m_tyreStintsEndLaps",  // The lap number stints end on
};

std::vector<std::size_t> FinalClassificationMetaSizes = {
    sizeof(((FinalClassificationMeta *)0)->m_numCars)  //  Number of cars in the final classification
};

std::vector<std::string> FinalClassificationMetaNames = {
    "m_numCars"  //  Number of cars in the final classification
};

std::string FinalClassificationDataString(FinalClassificationData obj, std::string sep) {
  const char *fmt = "%d%s%d%s%d%s%d%s%d%s%d%s%d%s%s%s%d%s%d%s%d%s%s%s%s%s%s";
  const char *ssep = sep.c_str();
  const std::string csep = "/";

  // cast double to string to avoid a segfault
  std::string m_totalRaceTime(std::to_string(obj.m_totalRaceTime));

  std::string m_tyreStintsActual(vpaste(
      std::vector<std::string>{
          std::to_string(obj.m_tyreStintsActual[0]),  //
          std::to_string(obj.m_tyreStintsActual[1]),  //
          std::to_string(obj.m_tyreStintsActual[2]),  //
          std::to_string(obj.m_tyreStintsActual[3])   //
      },
      csep));

  std::string m_tyreStintsVisual(vpaste(
      std::vector<std::string>{
          std::to_string(obj.m_tyreStintsVisual[0]),  //
          std::to_string(obj.m_tyreStintsVisual[1]),  //
          std::to_string(obj.m_tyreStintsVisual[2]),  //
          std::to_string(obj.m_tyreStintsVisual[3])   //
      },
      csep));

  std::string m_tyreStintsEndLaps(vpaste(
      std::vector<std::string>{
          std::to_string(obj.m_tyreStintsEndLaps[0]),  //
          std::to_string(obj.m_tyreStintsEndLaps[1]),  //
          std::to_string(obj.m_tyreStintsEndLaps[2]),  //
          std::to_string(obj.m_tyreStintsEndLaps[3])   //
      },
      csep));

  const std::size_t size = std::snprintf(
      nullptr, 0, fmt, obj.m_position, ssep, obj.m_numLaps, ssep, obj.m_gridPosition, ssep, obj.m_points, ssep,
      obj.m_numPitStops, ssep, obj.m_resultStatus, ssep, obj.m_bestLapTimeInMS, ssep, m_totalRaceTime.c_str(), ssep,
      obj.m_penaltiesTime, ssep, obj.m_numPenalties, ssep, obj.m_numTyreStints, ssep, m_tyreStintsActual.c_str(), ssep,
      m_tyreStintsVisual.c_str(), ssep, m_tyreStintsEndLaps.c_str());

  std::vector<char> buf(size + 1);  // note +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.m_position, ssep, obj.m_numLaps, ssep, obj.m_gridPosition, ssep,
                obj.m_points, ssep, obj.m_numPitStops, ssep, obj.m_resultStatus, ssep, obj.m_bestLapTimeInMS, ssep,
                m_totalRaceTime.c_str(), ssep, obj.m_penaltiesTime, ssep, obj.m_numPenalties, ssep, obj.m_numTyreStints,
                ssep, m_tyreStintsActual.c_str(), ssep, m_tyreStintsVisual.c_str(), ssep, m_tyreStintsEndLaps.c_str());

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));  // remove null terminator

  return str;
}

template <>
FinalClassificationData parseSubpacketData<FinalClassificationData>(std::vector<std::vector<unsigned char>> bytes) {
  FinalClassificationData obj;
  std::uint8_t idx[8] = {0, 1, 2, 3, 4, 5, 6, 7};

  std::memcpy(&obj.m_position, &bytes.at(0).front(), sizeof obj.m_position);
  std::memcpy(&obj.m_numLaps, &bytes.at(1).front(), sizeof obj.m_numLaps);
  std::memcpy(&obj.m_gridPosition, &bytes.at(2).front(), sizeof obj.m_gridPosition);
  std::memcpy(&obj.m_points, &bytes.at(3).front(), sizeof obj.m_points);
  std::memcpy(&obj.m_numPitStops, &bytes.at(4).front(), sizeof obj.m_numPitStops);
  std::memcpy(&obj.m_resultStatus, &bytes.at(5).front(), sizeof obj.m_resultStatus);
  std::memcpy(&obj.m_bestLapTimeInMS, &bytes.at(6).front(), sizeof obj.m_bestLapTimeInMS);
  std::memcpy(&obj.m_totalRaceTime, &bytes.at(7).front(), sizeof obj.m_totalRaceTime);
  std::memcpy(&obj.m_penaltiesTime, &bytes.at(8).front(), sizeof obj.m_penaltiesTime);
  std::memcpy(&obj.m_numPenalties, &bytes.at(9).front(), sizeof obj.m_numPenalties);
  std::memcpy(&obj.m_numTyreStints, &bytes.at(10).front(), sizeof obj.m_numTyreStints);

  for (std::uint8_t i : idx)
    std::memcpy(&obj.m_tyreStintsActual[i], &bytes.at(11).front() + (i * sizeof obj.m_tyreStintsActual[i]),
                sizeof obj.m_tyreStintsActual[i]);

  for (std::uint8_t i : idx)
    std::memcpy(&obj.m_tyreStintsVisual[i], &bytes.at(12).front() + (i * sizeof obj.m_tyreStintsVisual[i]),
                sizeof obj.m_tyreStintsVisual[i]);

  for (std::uint8_t i : idx)
    std::memcpy(&obj.m_tyreStintsEndLaps[i], &bytes.at(13).front() + (i * sizeof obj.m_tyreStintsEndLaps[i]),
                sizeof obj.m_tyreStintsEndLaps[i]);

  return obj;
}

std::string FinalClassificationMetaString(FinalClassificationMeta obj, std::string sep) {
  const char *fmt = "%d";
  // const char *ssep = sep.c_str();

  const std::size_t size = std::snprintf(nullptr, 0, fmt, obj.m_numCars);

  std::vector<char> buf(size + 1);  // note +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.m_numCars);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));  // remove null terminator

  return str;
}

template <>
FinalClassificationMeta parseSubpacketData<FinalClassificationMeta>(std::vector<std::vector<unsigned char>> bytes) {
  FinalClassificationMeta obj;

  std::memcpy(&obj.m_numCars, &bytes.at(0).front(), sizeof obj.m_numCars);

  return obj;
}

template <>
std::string packetDataHeader<PacketFinalClassificationData>(std::string sep, std::string compr) {
  std::vector<std::string> vec = {
      vpaste(PacketHeaderNames, sep),             //
      vpaste(FinalClassificationMetaNames, sep),  //
      vpaste(FinalClassificationDataNames, sep)   //
  };

  return vpaste(vec, sep);
}

template <>
std::string packetDataString(PacketFinalClassificationData obj, std::uint8_t id, std::string sep, std::string compr,
                             std::string compr2) {
  std::vector<std::string> vec = {
      PacketHeaderString(obj.m_header),                            //
      FinalClassificationMetaString(obj.m_classificationMeta),     //
      FinalClassificationDataString(obj.m_classificationData[id])  //
  };

  return vpaste(vec, sep);
}

template <>
PacketFinalClassificationData parsePacketData<PacketFinalClassificationData>(std::vector<unsigned char> bytes) {
  PacketFinalClassificationData obj;
  std::uint16_t offset = 0;

  // parse header
  obj.m_header = parseSubpacketData<PacketHeader>(parseBytes(PacketHeaderSizes, bytes, offset));
  offset += sizeof(PacketHeader);

  obj.m_classificationMeta =
      parseSubpacketData<FinalClassificationMeta>(parseBytes(FinalClassificationMetaSizes, bytes, offset));
  offset += sizeof(FinalClassificationMeta);

  // loop over the 22 car data packets and parse them
  for (std::uint8_t i = 0; i < 22; i++) {
    obj.m_classificationData[i] =
        parseSubpacketData<FinalClassificationData>(parseBytes(FinalClassificationDataSizes, bytes, offset));
    offset += sizeof(FinalClassificationData);
  }

  return obj;
}
