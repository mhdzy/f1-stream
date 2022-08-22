#include "PacketLapData.hpp"

std::vector<std::size_t> LapDataSizes = {
    sizeof(((LapData *)0)->m_lastLapTimeInMS),     // Last lap time in milliseconds
    sizeof(((LapData *)0)->m_currentLapTimeInMS),  // Current time around the lap in milliseconds
    sizeof(((LapData *)0)->m_sector1TimeInMS),     // Sector 1 time in milliseconds
    sizeof(((LapData *)0)->m_sector2TimeInMS),     // Sector 2 time in milliseconds
    sizeof(((LapData *)0)->m_lapDistance),         // Distance vehicle is around current lap in metres – could
                                                   // be negative if line hasn’t been crossed yet
    sizeof(((LapData *)0)->m_totalDistance),       // Total distance travelled in session in metres – could
                                                   // be negative if line hasn’t been crossed yet
    sizeof(((LapData *)0)->m_safetyCarDelta),      // Delta in seconds for safety car
    sizeof(((LapData *)0)->m_carPosition),         // Car race position
    sizeof(((LapData *)0)->m_currentLapNum),       // Current lap number
    sizeof(((LapData *)0)->m_pitStatus),           // 0 = none, 1 = pitting, 2 = in pit area
    sizeof(((LapData *)0)->m_numPitStops),         // Number of pit stops taken in this race
    sizeof(((LapData *)0)->m_sector),              // 0 = sector1, 1 = sector2, 2 = sector3
    sizeof(((LapData *)0)->m_currentLapInvalid),   // Current lap invalid - 0 = valid, 1 = invalid
    sizeof(((LapData *)0)->m_penalties),           // Accumulated time penalties in seconds to be added
    sizeof(((LapData *)0)->m_warnings),            // Accumulated number of warnings issued
    sizeof(((LapData *)0)->m_numUnservedDriveThroughPens),  // Num drive through pens left to serve
    sizeof(((LapData *)0)->m_numUnservedStopGoPens),        // Num stop go pens left to serve
    sizeof(((LapData *)0)->m_gridPosition),                 // Grid position the vehicle started the race in
    sizeof(((LapData *)0)->m_driverStatus),                 // Status of driver - 0 = in garage, 1 = flying lap
                                                            // 2 = in lap, 3 = out lap, 4 = on track
    sizeof(((LapData *)0)->m_resultStatus),                 // Result status - 0 = invalid, 1 = inactive, 2 = active
                                                            // 3 = finished, 4 = didnotfinish, 5 = disqualified
                                                            // 6 = not classified, 7 = retired
    sizeof(((LapData *)0)->m_pitLaneTimerActive),           // Pit lane timing, 0 = inactive, 1 = active
    sizeof(((LapData *)0)->m_pitLaneTimeInLaneInMS),        // If active, the current time spent in the pit lane in ms
    sizeof(((LapData *)0)->m_pitStopTimerInMS),             // Time of the actual pit stop in ms
    sizeof(((LapData *)0)->m_pitStopShouldServePen)         // Whether the car should serve a penalty at this stop
};

std::vector<std::string> LapDataNames = {
    "m_lastLapTimeInMS",              // Last lap time in milliseconds
    "m_currentLapTimeInMS",           // Current time around the lap in milliseconds
    "m_sector1TimeInMS",              // Sector 1 time in milliseconds
    "m_sector2TimeInMS",              // Sector 2 time in milliseconds
    "m_lapDistance",                  // Distance vehicle is around current lap in metres – could
                                      // be negative if line hasn’t been crossed yet
    "m_totalDistance",                // Total distance travelled in session in metres – could
                                      // be negative if line hasn’t been crossed yet
    "m_safetyCarDelta",               // Delta in seconds for safety car
    "m_carPosition",                  // Car race position
    "m_currentLapNum",                // Current lap number
    "m_pitStatus",                    // 0 = none, 1 = pitting, 2 = in pit area
    "m_numPitStops",                  // Number of pit stops taken in this race
    "m_sector",                       // 0 = sector1, 1 = sector2, 2 = sector3
    "m_currentLapInvalid",            // Current lap invalid - 0 = valid, 1 = invalid
    "m_penalties",                    // Accumulated time penalties in seconds to be added
    "m_warnings",                     // Accumulated number of warnings issued
    "m_numUnservedDriveThroughPens",  // Num drive through pens left to serve
    "m_numUnservedStopGoPens",        // Num stop go pens left to serve
    "m_gridPosition",                 // Grid position the vehicle started the race in
    "m_driverStatus",                 // Status of driver - 0 = in garage, 1 = flying lap
                                      // 2 = in lap, 3 = out lap, 4 = on track
    "m_resultStatus",                 // Result status - 0 = invalid, 1 = inactive, 2 = active
                                      // 3 = finished, 4 = didnotfinish, 5 = disqualified
                                      // 6 = not classified, 7 = retired
    "m_pitLaneTimerActive",           // Pit lane timing, 0 = inactive, 1 = active
    "m_pitLaneTimeInLaneInMS",        // If active, the current time spent in the pit lane in ms
    "m_pitStopTimerInMS",             // Time of the actual pit stop in ms
    "m_pitStopShouldServePen"         // Whether the car should serve a penalty at this stop
};

std::vector<std::size_t> LapDataIdxSizes = {
    sizeof(((LapDataIdx *)0)->m_timeTrialPBCarIdx),    // Index of Personal Best car in time trial (255 if invalid)
    sizeof(((LapDataIdx *)0)->m_timeTrialRivalCarIdx)  // Index of Rival car in time trial (255 if invalid)
};

std::vector<std::string> LapDataIdxNames = {
    "m_timeTrialPBCarIdx",    // Index of Personal Best car in time trial (255 if invalid)
    "m_timeTrialRivalCarIdx"  // Index of Rival car in time trial (255 if invalid)
};

std::string LapDataString(LapData obj, std::string sep) {
  const char *fmt = "%d%s%d%s%d%s%d%s%f%s%f%s%f%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d";
  const char *ssep = sep.c_str();

  const std::size_t size = std::snprintf(
      nullptr, 0, fmt, obj.m_lastLapTimeInMS, ssep, obj.m_currentLapTimeInMS, ssep, obj.m_sector1TimeInMS, ssep,
      obj.m_sector2TimeInMS, ssep, obj.m_lapDistance, ssep, obj.m_totalDistance, ssep, obj.m_safetyCarDelta, ssep,
      obj.m_carPosition, ssep, obj.m_currentLapNum, ssep, obj.m_pitStatus, ssep, obj.m_numPitStops, ssep, obj.m_sector,
      ssep, obj.m_currentLapInvalid, ssep, obj.m_penalties, ssep, obj.m_warnings, ssep,
      obj.m_numUnservedDriveThroughPens, ssep, obj.m_numUnservedStopGoPens, ssep, obj.m_gridPosition, ssep,
      obj.m_driverStatus, ssep, obj.m_resultStatus, ssep, obj.m_pitLaneTimerActive, ssep, obj.m_pitLaneTimeInLaneInMS,
      ssep, obj.m_pitStopTimerInMS, ssep, obj.m_pitStopShouldServePen);

  std::vector<char> buf(size + 1);  // +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.m_lastLapTimeInMS, ssep, obj.m_currentLapTimeInMS, ssep,
                obj.m_sector1TimeInMS, ssep, obj.m_sector2TimeInMS, ssep, obj.m_lapDistance, ssep, obj.m_totalDistance,
                ssep, obj.m_safetyCarDelta, ssep, obj.m_carPosition, ssep, obj.m_currentLapNum, ssep, obj.m_pitStatus,
                ssep, obj.m_numPitStops, ssep, obj.m_sector, ssep, obj.m_currentLapInvalid, ssep, obj.m_penalties, ssep,
                obj.m_warnings, ssep, obj.m_numUnservedDriveThroughPens, ssep, obj.m_numUnservedStopGoPens, ssep,
                obj.m_gridPosition, ssep, obj.m_driverStatus, ssep, obj.m_resultStatus, ssep, obj.m_pitLaneTimerActive,
                ssep, obj.m_pitLaneTimeInLaneInMS, ssep, obj.m_pitStopTimerInMS, ssep, obj.m_pitStopShouldServePen);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));  // remove null terminator

  return str;
}

LapData ParseLapData(std::vector<std::vector<unsigned char>> bytes) {
  LapData obj;

  std::memcpy(&obj.m_lastLapTimeInMS, &bytes.at(0).front(), LapDataSizes.at(0));
  std::memcpy(&obj.m_currentLapTimeInMS, &bytes.at(1).front(), LapDataSizes.at(1));
  std::memcpy(&obj.m_sector1TimeInMS, &bytes.at(2).front(), LapDataSizes.at(2));
  std::memcpy(&obj.m_sector2TimeInMS, &bytes.at(3).front(), LapDataSizes.at(3));
  std::memcpy(&obj.m_lapDistance, &bytes.at(4).front(), LapDataSizes.at(4));
  std::memcpy(&obj.m_totalDistance, &bytes.at(5).front(), LapDataSizes.at(5));
  std::memcpy(&obj.m_safetyCarDelta, &bytes.at(6).front(), LapDataSizes.at(6));
  std::memcpy(&obj.m_carPosition, &bytes.at(7).front(), LapDataSizes.at(7));
  std::memcpy(&obj.m_currentLapNum, &bytes.at(8).front(), LapDataSizes.at(8));
  std::memcpy(&obj.m_pitStatus, &bytes.at(9).front(), LapDataSizes.at(9));
  std::memcpy(&obj.m_numPitStops, &bytes.at(10).front(), LapDataSizes.at(10));
  std::memcpy(&obj.m_sector, &bytes.at(11).front(), LapDataSizes.at(11));
  std::memcpy(&obj.m_currentLapInvalid, &bytes.at(12).front(), LapDataSizes.at(12));
  std::memcpy(&obj.m_penalties, &bytes.at(13).front(), LapDataSizes.at(13));
  std::memcpy(&obj.m_warnings, &bytes.at(14).front(), LapDataSizes.at(14));
  std::memcpy(&obj.m_numUnservedDriveThroughPens, &bytes.at(15).front(), LapDataSizes.at(15));
  std::memcpy(&obj.m_numUnservedStopGoPens, &bytes.at(16).front(), LapDataSizes.at(16));
  std::memcpy(&obj.m_gridPosition, &bytes.at(17).front(), LapDataSizes.at(17));
  std::memcpy(&obj.m_driverStatus, &bytes.at(18).front(), LapDataSizes.at(18));
  std::memcpy(&obj.m_resultStatus, &bytes.at(19).front(), LapDataSizes.at(19));
  std::memcpy(&obj.m_pitLaneTimerActive, &bytes.at(20).front(), LapDataSizes.at(20));
  std::memcpy(&obj.m_pitLaneTimeInLaneInMS, &bytes.at(21).front(), LapDataSizes.at(21));
  std::memcpy(&obj.m_pitStopTimerInMS, &bytes.at(22).front(), LapDataSizes.at(22));
  std::memcpy(&obj.m_pitStopShouldServePen, &bytes.at(23).front(), LapDataSizes.at(23));

  return obj;
}

std::string LapDataIdxString(LapDataIdx obj, std::string sep) {
  const char *fmt = "%d%s%d";
  const char *ssep = sep.c_str();

  const std::size_t size = std::snprintf(nullptr, 0, fmt, obj.m_timeTrialPBCarIdx, ssep, obj.m_timeTrialRivalCarIdx);

  std::vector<char> buf(size + 1);  // +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.m_timeTrialPBCarIdx, ssep, obj.m_timeTrialRivalCarIdx);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));  // remove null terminator

  return str;
}

LapDataIdx ParseLapDataIdx(std::vector<std::vector<unsigned char>> bytes) {
  LapDataIdx obj;
  std::memcpy(&obj.m_timeTrialPBCarIdx, &bytes.at(0).front(), LapDataIdxSizes.at(0));
  std::memcpy(&obj.m_timeTrialRivalCarIdx, &bytes.at(1).front(), LapDataIdxSizes.at(1));
  return obj;
}

std::string PacketLapDataCSVHeader(std::string sep, std::string compr) {
  std::vector<std::string> vec = {
      vpaste(PacketHeaderNames, sep),  //
      vpaste(LapDataNames, sep),       //
      vpaste(LapDataIdxNames, sep)     //
  };

  return vpaste(vec, sep);
}

std::string PacketLapDataString(PacketLapData obj, std::uint8_t carID, std::string sep, std::string compr,
                                std::string compr2) {
  std::vector<std::string> vec = {
      PacketHeaderString(obj.m_header),     //
      LapDataString(obj.m_lapData[carID]),  //
      LapDataIdxString(obj.m_lapDataIdx)    //
  };
  return vpaste(vec, sep);
}

PacketLapData ParsePacketLapData(std::vector<unsigned char> bytes) {
  PacketLapData obj;

  std::uint16_t offset = 0;

  obj.m_header = ParsePacketHeader(parse_bytes_to_vec(PacketHeaderSizes, bytes, offset));
  offset += sizeof(PacketHeader);

  // iterate over all car indices
  for (std::uint8_t i = 0; i < 22; i++) {
    obj.m_lapData[i] = ParseLapData(parse_bytes_to_vec(LapDataSizes, bytes, offset));
    offset += sizeof(LapData);
  }

  obj.m_lapDataIdx = ParseLapDataIdx(parse_bytes_to_vec(LapDataIdxSizes, bytes, offset));
  offset += sizeof(LapDataIdx);

  return obj;
}
