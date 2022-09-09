#include "../include/PacketSessionData.hpp"

std::vector<std::size_t> MarshalZoneSizes = {
    sizeof(((MarshalZone *)0)->m_zoneStart),  // Fraction (0..1) of way through the lap the marshal zone starts
    sizeof(((MarshalZone *)0)->m_zoneFlag)  // -1 = invalid/unknown, 0 = none, 1 = green, 2 = blue, 3 = yellow, 4 = red
};

std::vector<std::string> MarshalZoneNames = {
    "m_zoneStart",  // Fraction (0..1) of way through the lap the marshal zone starts
    "m_zoneFlag"    // -1 = invalid/unknown, 0 = none, 1 = green, 2 = blue, 3 = yellow, 4 = red
};

std::vector<std::size_t> WeatherForecastSampleSizes = {
    sizeof(((WeatherForecastSample *)0)->m_sessionType),  // 0 = unknown, 1 = P1, 2 = P2, 3 = P3, 4 = Short P, 5 = Q1
                                                          // 6 = Q2, 7 = Q3, 8 = Short Q, 9 = OSQ, 10 = R, 11 = R2
                                                          // 12 = R3, 13 = Time Trial
    sizeof(((WeatherForecastSample *)0)->m_timeOffset),   // Time in minutes the forecast is for
    sizeof(((WeatherForecastSample *)0)->m_weather),      // Weather - 0 = clear, 1 = light cloud, 2 = overcast
                                                          // 3 = light rain, 4 = heavy rain, 5 = storm
    sizeof(((WeatherForecastSample *)0)->m_trackTemperature),        // Track temp. in degrees Celsius
    sizeof(((WeatherForecastSample *)0)->m_trackTemperatureChange),  // Track temp. change – 0 = up 1 = down,
                                                                     // 2 = no change
    sizeof(((WeatherForecastSample *)0)->m_airTemperature),          // Air temp. in degrees celsius
    sizeof(((WeatherForecastSample *)0)->m_airTemperatureChange),  // Air temp. change – 0 = up, 1 = down, 2 = no change
    sizeof(((WeatherForecastSample *)0)->m_rainPercentage)         // Rain percentage (0-100)
};

std::vector<std::string> WeatherForecastSampleNames = {
    "m_sessionType",             // 0 = unknown, 1 = P1, 2 = P2, 3 = P3, 4 = Short P, 5 = Q1
                                 // 6 = Q2, 7 = Q3, 8 = Short Q, 9 = OSQ, 10 = R, 11 = R2
                                 // 12 = R3, 13 = Time Trial
    "m_timeOffset",              // Time in minutes the forecast is for
    "m_weather",                 // Weather - 0 = clear, 1 = light cloud, 2 = overcast
                                 // 3 = light rain, 4 = heavy rain, 5 = storm
    "m_trackTemperature",        // Track temp. in degrees Celsius
    "m_trackTemperatureChange",  // Track temp. change – 0 = up 1 = down, 2 = no change
    "m_airTemperature",          // Air temp. in degrees celsius
    "m_airTemperatureChange",    // Air temp. change – 0 = up, 1 = down, 2 = no change
    "m_rainPercentage"           // Rain percentage (0-100)
};

std::vector<std::size_t> PacketSessionDataTopSizes = {
    sizeof(((PacketSessionDataTop *)0)->m_weather),              // Weather - 0 = clear, 1 = light cloud, 2 = overcast
                                                                 // 3 = light rain, 4 = heavy rain, 5 = storm
    sizeof(((PacketSessionDataTop *)0)->m_trackTemperature),     // Track temp. in degrees celsius
    sizeof(((PacketSessionDataTop *)0)->m_airTemperature),       // Air temp. in degrees celsius
    sizeof(((PacketSessionDataTop *)0)->m_totalLaps),            // Total number of laps in this race
    sizeof(((PacketSessionDataTop *)0)->m_trackLength),          // Track length in metres
    sizeof(((PacketSessionDataTop *)0)->m_sessionType),          // 0 = unknown, 1 = P1, 2 = P2, 3 = P3, 4 = Short P
                                                                 // 5 = Q1, 6 = Q2, 7 = Q3, 8 = Short Q, 9 = OSQ
                                                                 // 10 = R, 11 = R2, 12 = R3, 13 = Time Trial
    sizeof(((PacketSessionDataTop *)0)->m_trackId),              // -1 for unknown, see appendix
    sizeof(((PacketSessionDataTop *)0)->m_formula),              // Formula, 0 = F1 Modern, 1 = F1 Classic, 2 = F2,
                                                                 // 3 = F1 Generic, 4 = Beta, 5 = Supercars
                                                                 // 6 = Esports, 7 = F2 2021
    sizeof(((PacketSessionDataTop *)0)->m_sessionTimeLeft),      // Time left in session in seconds
    sizeof(((PacketSessionDataTop *)0)->m_sessionDuration),      // Session duration in seconds
    sizeof(((PacketSessionDataTop *)0)->m_pitSpeedLimit),        // Pit speed limit in kilometres per hour
    sizeof(((PacketSessionDataTop *)0)->m_gamePaused),           // Whether the game is paused – network game only
    sizeof(((PacketSessionDataTop *)0)->m_isSpectating),         // Whether the player is spectating
    sizeof(((PacketSessionDataTop *)0)->m_spectatorCarIndex),    // Index of the car being spectated
    sizeof(((PacketSessionDataTop *)0)->m_sliProNativeSupport),  // SLI Pro support, 0 = inactive, 1 = active
    sizeof(((PacketSessionDataTop *)0)->m_numMarshalZones)       // Number of marshal zones to follow
};

std::vector<std::string> PacketSessionDataTopNames = {
    "m_weather",              // Weather - 0 = clear, 1 = light cloud, 2 = overcast
                              // 3 = light rain, 4 = heavy rain, 5 = storm
    "m_trackTemperature",     // Track temp. in degrees celsius
    "m_airTemperature",       // Air temp. in degrees celsius
    "m_totalLaps",            // Total number of laps in this race
    "m_trackLength",          // Track length in metres
    "m_sessionType",          // 0 = unknown, 1 = P1, 2 = P2, 3 = P3, 4 = Short P
                              // 5 = Q1, 6 = Q2, 7 = Q3, 8 = Short Q, 9 = OSQ
                              // 10 = R, 11 = R2, 12 = R3, 13 = Time Trial
    "m_trackId",              // -1 for unknown, see appendix
    "m_formula",              // Formula, 0 = F1 Modern, 1 = F1 Classic, 2 = F2,
                              // 3 = F1 Generic, 4 = Beta, 5 = Supercars
                              // 6 = Esports, 7 = F2 2021
    "m_sessionTimeLeft",      // Time left in session in seconds
    "m_sessionDuration",      // Session duration in seconds
    "m_pitSpeedLimit",        // Pit speed limit in kilometres per hour
    "m_gamePaused",           // Whether the game is paused – network game only
    "m_isSpectating",         // Whether the player is spectating
    "m_spectatorCarIndex",    // Index of the car being spectated
    "m_sliProNativeSupport",  // SLI Pro support, 0 = inactive, 1 = active
    "m_numMarshalZones"       // Number of marshal zones to follow
};

std::vector<std::size_t> PacketSessionDataMidSizes = {
    sizeof(((PacketSessionDataMid *)0)->m_safetyCarStatus),           // 0 = no safety car, 1 = full, 2 = virtual,
                                                                      // 3 = formation lap
    sizeof(((PacketSessionDataMid *)0)->m_networkGame),               // 0 = offline, 1 = online
    sizeof(((PacketSessionDataMid *)0)->m_numWeatherForecastSamples)  // Number of weather samples to follow
};

std::vector<std::string> PacketSessionDataMidNames = {
    "m_safetyCarStatus",           // 0 = no safety car, 1 = full, 2 = virtual, 3 = formation lap
    "m_networkGame",               // 0 = offline, 1 = online
    "m_numWeatherForecastSamples"  // Number of weather samples to follow
};

std::vector<std::size_t> PacketSessionDataBotSizes = {
    sizeof(((PacketSessionDataBot *)0)->m_forecastAccuracy),        // 0 = Perfect, 1 = Approximate
    sizeof(((PacketSessionDataBot *)0)->m_aiDifficulty),            // AI Difficulty rating – 0-110
    sizeof(((PacketSessionDataBot *)0)->m_seasonLinkIdentifier),    // Identifier for season - persists across saves
    sizeof(((PacketSessionDataBot *)0)->m_weekendLinkIdentifier),   // Identifier for weekend - persists across saves
    sizeof(((PacketSessionDataBot *)0)->m_sessionLinkIdentifier),   // Identifier for session - persists across saves
    sizeof(((PacketSessionDataBot *)0)->m_pitStopWindowIdealLap),   // Ideal lap to pit on for current strategy (player)
    sizeof(((PacketSessionDataBot *)0)->m_pitStopWindowLatestLap),  // Latest lap to pit on for current strategy(player)
    sizeof(((PacketSessionDataBot *)0)->m_pitStopRejoinPosition),   // Predicted position to rejoin at (player)
    sizeof(((PacketSessionDataBot *)0)->m_steeringAssist),          // 0 = off, 1 = on
    sizeof(((PacketSessionDataBot *)0)->m_brakingAssist),           // 0 = off, 1 = low, 2 = medium, 3 = high
    sizeof(((PacketSessionDataBot *)0)->m_gearboxAssist),           // 1 = manual, 2 = manual & suggested gear, 3 = auto
    sizeof(((PacketSessionDataBot *)0)->m_pitAssist),               // 0 = off, 1 = on
    sizeof(((PacketSessionDataBot *)0)->m_pitReleaseAssist),        // 0 = off, 1 = on
    sizeof(((PacketSessionDataBot *)0)->m_ERSAssist),               // 0 = off, 1 = on
    sizeof(((PacketSessionDataBot *)0)->m_DRSAssist),               // 0 = off, 1 = on
    sizeof(((PacketSessionDataBot *)0)->m_dynamicRacingLine),       // 0 = off, 1 = corners only, 2 = full
    sizeof(((PacketSessionDataBot *)0)->m_dynamicRacingLineType),   // 0 = 2D, 1 = 3D
    sizeof(((PacketSessionDataBot *)0)->m_gameMode),                // Game mode id - see appendix
    sizeof(((PacketSessionDataBot *)0)->m_ruleSet),                 // Ruleset - see appendix
    sizeof(((PacketSessionDataBot *)0)->m_timeOfDay),               // Local time of day - minutes since midnight
    sizeof(((PacketSessionDataBot *)0)->m_sessionLength)            // 0 = None, 2 = Very Short, 3 = Short, 4 = Medium,
                                                                    // 5 = Medium Long, 6 = Long, 7 = Full
};

std::vector<std::string> PacketSessionDataBotNames = {
    "m_forecastAccuracy",        // 0 = Perfect, 1 = Approximate
    "m_aiDifficulty",            // AI Difficulty rating – 0-110
    "m_seasonLinkIdentifier",    // Identifier for season - persists across saves
    "m_weekendLinkIdentifier",   // Identifier for weekend - persists across saves
    "m_sessionLinkIdentifier",   // Identifier for session - persists across saves
    "m_pitStopWindowIdealLap",   // Ideal lap to pit on for current strategy (player)
    "m_pitStopWindowLatestLap",  // Latest lap to pit on for current strategy (player)
    "m_pitStopRejoinPosition",   // Predicted position to rejoin at (player)
    "m_steeringAssist",          // 0 = off, 1 = on
    "m_brakingAssist",           // 0 = off, 1 = low, 2 = medium, 3 = high
    "m_gearboxAssist",           // 1 = manual, 2 = manual & suggested gear, 3 = auto
    "m_pitAssist",               // 0 = off, 1 = on
    "m_pitReleaseAssist",        // 0 = off, 1 = on
    "m_ERSAssist",               // 0 = off, 1 = on
    "m_DRSAssist",               // 0 = off, 1 = on
    "m_dynamicRacingLine",       // 0 = off, 1 = corners only, 2 = full
    "m_dynamicRacingLineType",   // 0 = 2D, 1 = 3D
    "m_gameMode",                // Game mode id - see appendix
    "m_ruleSet",                 // Ruleset - see appendix
    "m_timeOfDay",               // Local time of day - minutes since midnight
    "m_sessionLength"            // 0 = None, 2 = Very Short, 3 = Short, 4 = Medium,
                                 // 5 = Medium Long, 6 = Long, 7 = Full
};

std::string MarshalZoneString(MarshalZone obj, std::string sep) {
  const char *fmt = "%f%s%d";
  const char *ssep = sep.c_str();

  const std::size_t size = std::snprintf(nullptr, 0, fmt, obj.m_zoneStart, ssep, obj.m_zoneFlag);

  std::vector<char> buf(size + 1);  // +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.m_zoneStart, ssep, obj.m_zoneFlag);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));  // remove null terminator

  return str;
}

MarshalZone ParseMarshalZone(std::vector<std::vector<unsigned char>> bytes) {
  MarshalZone obj;
  std::memcpy(&obj.m_zoneStart, &bytes.at(0).front(), sizeof obj.m_zoneStart);
  std::memcpy(&obj.m_zoneFlag, &bytes.at(1).front(), sizeof obj.m_zoneFlag);
  return obj;
}

std::string WeatherForecastSampleString(WeatherForecastSample obj, std::string sep) {
  const char *fmt = "%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d";
  const char *ssep = sep.c_str();

  const std::size_t size =
      std::snprintf(nullptr, 0, fmt, obj.m_sessionType, ssep, obj.m_timeOffset, ssep, obj.m_weather, ssep,
                    obj.m_trackTemperature, ssep, obj.m_trackTemperatureChange, ssep, obj.m_airTemperature, ssep,
                    obj.m_airTemperatureChange, ssep, obj.m_rainPercentage);

  std::vector<char> buf(size + 1);  // +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.m_sessionType, ssep, obj.m_timeOffset, ssep, obj.m_weather, ssep,
                obj.m_trackTemperature, ssep, obj.m_trackTemperatureChange, ssep, obj.m_airTemperature, ssep,
                obj.m_airTemperatureChange, ssep, obj.m_rainPercentage);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));  // remove null terminator

  return str;
}

WeatherForecastSample ParseWeatherForecastSample(std::vector<std::vector<unsigned char>> bytes) {
  WeatherForecastSample obj;
  std::memcpy(&obj.m_sessionType, &bytes.at(0).front(), sizeof obj.m_sessionType);
  std::memcpy(&obj.m_timeOffset, &bytes.at(1).front(), sizeof obj.m_timeOffset);
  std::memcpy(&obj.m_weather, &bytes.at(2).front(), sizeof obj.m_weather);
  std::memcpy(&obj.m_trackTemperature, &bytes.at(3).front(), sizeof obj.m_trackTemperature);
  std::memcpy(&obj.m_trackTemperatureChange, &bytes.at(4).front(), sizeof obj.m_trackTemperatureChange);
  std::memcpy(&obj.m_airTemperature, &bytes.at(5).front(), sizeof obj.m_airTemperature);
  std::memcpy(&obj.m_airTemperatureChange, &bytes.at(6).front(), sizeof obj.m_airTemperatureChange);
  std::memcpy(&obj.m_rainPercentage, &bytes.at(7).front(), sizeof obj.m_rainPercentage);
  return obj;
}

std::string PacketSessionDataTopString(PacketSessionDataTop obj, std::string sep) {
  const char *fmt = "%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d";
  const char *ssep = sep.c_str();

  const std::size_t size = std::snprintf(
      nullptr, 0, fmt, obj.m_weather, ssep, obj.m_trackTemperature, ssep, obj.m_airTemperature, ssep, obj.m_totalLaps,
      ssep, obj.m_trackLength, ssep, obj.m_sessionType, ssep, obj.m_trackId, ssep, obj.m_formula, ssep,
      obj.m_sessionTimeLeft, ssep, obj.m_sessionDuration, ssep, obj.m_pitSpeedLimit, ssep, obj.m_gamePaused, ssep,
      obj.m_isSpectating, ssep, obj.m_spectatorCarIndex, ssep, obj.m_sliProNativeSupport, ssep, obj.m_numMarshalZones);

  std::vector<char> buf(size + 1);  // +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.m_weather, ssep, obj.m_trackTemperature, ssep, obj.m_airTemperature, ssep,
                obj.m_totalLaps, ssep, obj.m_trackLength, ssep, obj.m_sessionType, ssep, obj.m_trackId, ssep,
                obj.m_formula, ssep, obj.m_sessionTimeLeft, ssep, obj.m_sessionDuration, ssep, obj.m_pitSpeedLimit,
                ssep, obj.m_gamePaused, ssep, obj.m_isSpectating, ssep, obj.m_spectatorCarIndex, ssep,
                obj.m_sliProNativeSupport, ssep, obj.m_numMarshalZones);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));  // remove null terminator

  return str;
}

PacketSessionDataTop ParsePacketSessionDataTop(std::vector<std::vector<unsigned char>> bytes) {
  PacketSessionDataTop obj;
  std::memcpy(&obj.m_weather, &bytes.at(0).front(), sizeof obj.m_weather);
  std::memcpy(&obj.m_trackTemperature, &bytes.at(1).front(), sizeof obj.m_trackTemperature);
  std::memcpy(&obj.m_airTemperature, &bytes.at(2).front(), sizeof obj.m_airTemperature);
  std::memcpy(&obj.m_totalLaps, &bytes.at(3).front(), sizeof obj.m_totalLaps);
  std::memcpy(&obj.m_trackLength, &bytes.at(4).front(), sizeof obj.m_trackLength);
  std::memcpy(&obj.m_sessionType, &bytes.at(5).front(), sizeof obj.m_sessionType);
  std::memcpy(&obj.m_trackId, &bytes.at(6).front(), sizeof obj.m_trackId);
  std::memcpy(&obj.m_formula, &bytes.at(7).front(), sizeof obj.m_formula);
  std::memcpy(&obj.m_sessionTimeLeft, &bytes.at(8).front(), sizeof obj.m_sessionTimeLeft);
  std::memcpy(&obj.m_sessionDuration, &bytes.at(9).front(), sizeof obj.m_sessionDuration);
  std::memcpy(&obj.m_pitSpeedLimit, &bytes.at(10).front(), sizeof obj.m_pitSpeedLimit);
  std::memcpy(&obj.m_gamePaused, &bytes.at(11).front(), sizeof obj.m_gamePaused);
  std::memcpy(&obj.m_isSpectating, &bytes.at(12).front(), sizeof obj.m_isSpectating);
  std::memcpy(&obj.m_spectatorCarIndex, &bytes.at(13).front(), sizeof obj.m_spectatorCarIndex);
  std::memcpy(&obj.m_sliProNativeSupport, &bytes.at(14).front(), sizeof obj.m_sliProNativeSupport);
  std::memcpy(&obj.m_numMarshalZones, &bytes.at(15).front(), sizeof obj.m_numMarshalZones);
  return obj;
}

std::string PacketSessionDataMidString(PacketSessionDataMid obj, std::string sep) {
  const char *fmt = "%d%s%d%s%d";
  const char *ssep = sep.c_str();

  const std::size_t size = std::snprintf(nullptr, 0, fmt, obj.m_safetyCarStatus, ssep, obj.m_networkGame, ssep,
                                         obj.m_numWeatherForecastSamples);

  std::vector<char> buf(size + 1);  // +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.m_safetyCarStatus, ssep, obj.m_networkGame, ssep,
                obj.m_numWeatherForecastSamples);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));  // remove null terminator

  return str;
}

PacketSessionDataMid ParsePacketSessionDataMid(std::vector<std::vector<unsigned char>> bytes) {
  PacketSessionDataMid obj;
  std::memcpy(&obj.m_safetyCarStatus, &bytes.at(0).front(), sizeof obj.m_safetyCarStatus);
  std::memcpy(&obj.m_networkGame, &bytes.at(1).front(), sizeof obj.m_networkGame);
  std::memcpy(&obj.m_numWeatherForecastSamples, &bytes.at(2).front(), sizeof obj.m_numWeatherForecastSamples);
  return obj;
}

std::string PacketSessionDataBotString(PacketSessionDataBot obj, std::string sep) {
  const char *fmt = "%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d";
  const char *ssep = sep.c_str();

  const std::size_t size = std::snprintf(
      nullptr, 0, fmt, obj.m_forecastAccuracy, ssep, obj.m_aiDifficulty, ssep, obj.m_seasonLinkIdentifier, ssep,
      obj.m_weekendLinkIdentifier, ssep, obj.m_sessionLinkIdentifier, ssep, obj.m_pitStopWindowIdealLap, ssep,
      obj.m_pitStopWindowLatestLap, ssep, obj.m_pitStopRejoinPosition, ssep, obj.m_steeringAssist, ssep,
      obj.m_brakingAssist, ssep, obj.m_gearboxAssist, ssep, obj.m_pitAssist, ssep, obj.m_pitReleaseAssist, ssep,
      obj.m_ERSAssist, ssep, obj.m_DRSAssist, ssep, obj.m_dynamicRacingLine, ssep, obj.m_dynamicRacingLineType, ssep,
      obj.m_gameMode, ssep, obj.m_ruleSet, ssep, obj.m_timeOfDay, ssep, obj.m_sessionLength);

  std::vector<char> buf(size + 1);  // +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.m_forecastAccuracy, ssep, obj.m_aiDifficulty, ssep,
                obj.m_seasonLinkIdentifier, ssep, obj.m_weekendLinkIdentifier, ssep, obj.m_sessionLinkIdentifier, ssep,
                obj.m_pitStopWindowIdealLap, ssep, obj.m_pitStopWindowLatestLap, ssep, obj.m_pitStopRejoinPosition,
                ssep, obj.m_steeringAssist, ssep, obj.m_brakingAssist, ssep, obj.m_gearboxAssist, ssep, obj.m_pitAssist,
                ssep, obj.m_pitReleaseAssist, ssep, obj.m_ERSAssist, ssep, obj.m_DRSAssist, ssep,
                obj.m_dynamicRacingLine, ssep, obj.m_dynamicRacingLineType, ssep, obj.m_gameMode, ssep, obj.m_ruleSet,
                ssep, obj.m_timeOfDay, ssep, obj.m_sessionLength);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));  // remove null terminator

  return str;
}

PacketSessionDataBot ParsePacketSessionDataBot(std::vector<std::vector<unsigned char>> bytes) {
  PacketSessionDataBot obj;
  std::memcpy(&obj.m_forecastAccuracy, &bytes.at(0).front(), sizeof obj.m_forecastAccuracy);
  std::memcpy(&obj.m_aiDifficulty, &bytes.at(1).front(), sizeof obj.m_aiDifficulty);
  std::memcpy(&obj.m_seasonLinkIdentifier, &bytes.at(2).front(), sizeof obj.m_seasonLinkIdentifier);
  std::memcpy(&obj.m_weekendLinkIdentifier, &bytes.at(3).front(), sizeof obj.m_weekendLinkIdentifier);
  std::memcpy(&obj.m_sessionLinkIdentifier, &bytes.at(4).front(), sizeof obj.m_sessionLinkIdentifier);
  std::memcpy(&obj.m_pitStopWindowIdealLap, &bytes.at(5).front(), sizeof obj.m_pitStopWindowIdealLap);
  std::memcpy(&obj.m_pitStopWindowLatestLap, &bytes.at(6).front(), sizeof obj.m_pitStopWindowLatestLap);
  std::memcpy(&obj.m_pitStopRejoinPosition, &bytes.at(7).front(), sizeof obj.m_pitStopRejoinPosition);
  std::memcpy(&obj.m_steeringAssist, &bytes.at(8).front(), sizeof obj.m_steeringAssist);
  std::memcpy(&obj.m_brakingAssist, &bytes.at(9).front(), sizeof obj.m_brakingAssist);
  std::memcpy(&obj.m_gearboxAssist, &bytes.at(10).front(), sizeof obj.m_gearboxAssist);
  std::memcpy(&obj.m_pitAssist, &bytes.at(11).front(), sizeof obj.m_pitAssist);
  std::memcpy(&obj.m_pitReleaseAssist, &bytes.at(12).front(), sizeof obj.m_pitReleaseAssist);
  std::memcpy(&obj.m_ERSAssist, &bytes.at(13).front(), sizeof obj.m_ERSAssist);
  std::memcpy(&obj.m_DRSAssist, &bytes.at(14).front(), sizeof obj.m_DRSAssist);
  std::memcpy(&obj.m_dynamicRacingLine, &bytes.at(15).front(), sizeof obj.m_dynamicRacingLine);
  std::memcpy(&obj.m_dynamicRacingLineType, &bytes.at(16).front(), sizeof obj.m_dynamicRacingLineType);
  std::memcpy(&obj.m_gameMode, &bytes.at(17).front(), sizeof obj.m_gameMode);
  std::memcpy(&obj.m_ruleSet, &bytes.at(18).front(), sizeof obj.m_ruleSet);
  std::memcpy(&obj.m_timeOfDay, &bytes.at(19).front(), sizeof obj.m_timeOfDay);
  std::memcpy(&obj.m_sessionLength, &bytes.at(20).front(), sizeof obj.m_sessionLength);
  return obj;
}

/**
 * @brief Returns a CSV header string.
 *
 * @param sep A string separator.
 * @param compr A string used to compress the array-valued fields.
 * @return std::string to use as a CSV header for PacketSessionData.
 *
 */
std::string PacketSessionDataCSVHeader(std::string sep, std::string compr) {
  std::vector<std::string> vec = {
      vpaste(PacketHeaderNames, sep),             //
      vpaste(PacketSessionDataTopNames, sep),     //
      vpaste(MarshalZoneNames, compr),            //
      vpaste(PacketSessionDataMidNames, sep),     //
      vpaste(WeatherForecastSampleNames, compr),  //
      vpaste(PacketSessionDataBotNames, sep)      //
  };

  return vpaste(vec, sep);
}

/**
 * @brief Parse a string representation (default csv) of the PacketSessionData struct. Use .pop_back() to remove the
 * lingering "compr" character that remains.
 *
 * @param obj
 * @param id
 * @param sep A string used to separate the individual field values.
 * @param compr A string used to compress the array-valued field values, should they be a struct or array themselves.
 * @param compr2 A string used to compress the array-typed field values together.
 * @return std::string
 */
template <>
std::string packetDataString(PacketSessionData obj, std::uint8_t id, std::string sep, std::string compr,
                             std::string compr2) {
  // compress marshal zones
  std::string compr_marshalZones;
  for (std::uint8_t i = 0; i < obj.m_packetSessionDataTop.m_numMarshalZones; i++) {
    compr_marshalZones += MarshalZoneString(obj.m_marshalZones[i], compr) + compr2;
  }
  if (!compr_marshalZones.empty()) compr_marshalZones.pop_back();

  // compress weather forecasts
  std::string compr_weatherForecastSamples;
  for (std::uint8_t i = 0; i < obj.m_packetSessionDataMid.m_numWeatherForecastSamples; i++) {
    compr_weatherForecastSamples += WeatherForecastSampleString(obj.m_weatherForecastSamples[i], compr) + compr2;
  }
  if (!compr_weatherForecastSamples.empty()) compr_weatherForecastSamples.pop_back();

  std::vector<std::string> vec = {
      PacketHeaderString(obj.m_header),
      PacketSessionDataTopString(obj.m_packetSessionDataTop),
      compr_marshalZones,
      PacketSessionDataMidString(obj.m_packetSessionDataMid),
      compr_weatherForecastSamples,
      PacketSessionDataBotString(obj.m_PacketSessionDataBot),
  };

  return vpaste(vec, sep);
}

template <>
PacketSessionData parsePacketData<PacketSessionData>(std::vector<unsigned char> bytes) {
  PacketSessionData obj;
  std::uint16_t offset = 0;

  obj.m_header = ParsePacketHeader(parseBytes(PacketHeaderSizes, bytes, offset));
  offset += sizeof(PacketHeader);

  obj.m_packetSessionDataTop = ParsePacketSessionDataTop(parseBytes(PacketSessionDataTopSizes, bytes, offset));
  offset += sizeof(PacketSessionDataTop);

  // iterate over all marshal zone array indices to correctly set the offset
  for (std::uint8_t i = 0; i < 21; i++) {
    obj.m_marshalZones[i] = ParseMarshalZone(parseBytes(MarshalZoneSizes, bytes, offset));
    offset += sizeof(MarshalZone);
  }

  obj.m_packetSessionDataMid = ParsePacketSessionDataMid(parseBytes(PacketSessionDataMidSizes, bytes, offset));
  offset += sizeof(PacketSessionDataMid);

  // same reasoning as above (loop limit of 56)
  for (std::uint8_t i = 0; i < 56; i++) {
    obj.m_weatherForecastSamples[i] =
        ParseWeatherForecastSample(parseBytes(WeatherForecastSampleSizes, bytes, offset));
    offset += sizeof(WeatherForecastSample);
  }

  obj.m_PacketSessionDataBot = ParsePacketSessionDataBot(parseBytes(PacketSessionDataBotSizes, bytes, offset));
  offset += sizeof(PacketSessionDataBot);

  return obj;
}
