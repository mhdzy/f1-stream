#include "PacketSessionData.hpp"

std::string MarshalZoneCSVHeader() {
  std::string str = "m_ZoneStart,m_zoneFlag";

  return str;
}

std::string MarshalZoneString(MarshalZone obj, std::string sep) {
  const char *fmt = "%f%s%d";
  const char *ssep = sep.c_str();

  const int size = std::snprintf(nullptr, 0, fmt, obj.m_zoneStart, ssep, obj.m_zoneFlag);

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

std::vector<std::pair<int, std::string>> MarshalZonePairs{
    std::make_pair(sizeof(float), "m_zoneStart"),      // Fraction (0..1) of way through the lap the marshal zone starts
    std::make_pair(sizeof(std::int8_t), "m_zoneFlag")  // -1 = invalid/unknown, 0 = none, 1 = green, 2 = blue,
                                                       // 3 = yellow, 4 = red
};

std::string WeatherForecastSampleCSVHeader() {
  std::string str =
      "m_sessionType,m_timeOffset,m_weather,m_trackTemperature,m_trackTemperatureChange,m_airTemperature,m_"
      "airTemperatureChange,m_rainPercentage";
  return str;
}

std::string WeatherForecastSampleString(WeatherForecastSample obj, std::string sep) {
  const char *fmt = "%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s";
  const char *ssep = sep.c_str();

  const int size = std::snprintf(nullptr, 0, fmt, obj.m_sessionType, ssep, obj.m_timeOffset, ssep, obj.m_weather, ssep,
                                 obj.m_trackTemperature, ssep, obj.m_trackTemperatureChange, ssep, obj.m_airTemperature,
                                 ssep, obj.m_airTemperatureChange, ssep, obj.m_rainPercentage);

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

std::vector<std::pair<int, std::string>> WeatherForecastSamplePairs {
    std::make_pair(sizeof(std::uint8_t), "m_sessionType"),  // 0 = unknown, 1 = P1, 2 = P2, 3 = P3, 4 = Short P, 5 = Q1
                                                            // 6 =), "Q2, 7 = Q3, 8 = Short Q, 9 = OSQ, 10 = R, 11 = R2
                                                            // 12 =), "R3, 13 = Time Trial
    std::make_pair(sizeof(std::uint8_t), "m_timeOffset"),   // Time in minutes the forecast is for
    std::make_pair(sizeof(std::uint8_t), "m_weather"),      // Weather - 0 = clear, 1 = light cloud, 2 = overcast
                                                            // 3 =), "light rain, 4 = heavy rain, 5 = storm
    std::make_pair(sizeof(std::int8_t), "m_trackTemperature"),        // Track temp. in degrees Celsius
    std::make_pair(sizeof(std::int8_t), "m_trackTemperatureChange"),  // Track temp. change – 0 = up,
                                                                      // 1 = down, 2 = no change
    std::make_pair(sizeof(std::int8_t), "m_airTemperature"),          // Air temp. in degrees celsius
    std::make_pair(sizeof(std::int8_t), "m_airTemperatureChange"),    // Air temp. change – 0 = up, 1 = down,
                                                                      // 2 = no change
    std::make_pair(sizeof(std::uint8_t), "m_rainPercentage")          // Rain percentage (0-100)
};

std::string PacketSessionDataCSVHeader() {
  std::string str =
      "m_weather,m_trackTemperature,m_airTemperature,m_totalLaps,m_trackLength,m_SessionType,m_trackId,m_formula,m_"
      "sessionTimeLeft,m_sessionDuration,m_pitSpeedLimit,m_gamePaused,m_isSpectating,m_spectatorCarIndex,m_"
      "sliProNativeSupport,m_numMarshalZones,m_marshalZones,m_safetyCarStatus,m_networkGame,m_"
      "numWeatherForecastSamples,m_weatherForecastSamples,m_forecastAccuracy,m_aiDifficulty,m_seasonLinkIdentifier,m_"
      "weekendLinkIdentifier,m_sessionLinkIdentifier,m_pitStopWindowIdealLap,m_pitStopWindowLatestLap,m_"
      "pitStopRejoinPosition,m_steeringAssist,m_brakingAssist,m_gearboxAssist,m_pitAssist,m_pitReleaseAssist,m_"
      "ERSAssist,m_DRSAssist,m_dynamicRacingLine,m_dynamicRacingLineType,m_gameMode,m_ruleSet,m_timeOfDay,m_"
      "sessionLength";

  return str;
}

std::string PacketSessionDataString(PacketSessionData obj, std::string sep) {
  std::string str;

  return str;
}

PacketSessionData ParsePacketSessionData(std::vector<unsigned char> bytes) {
  PacketSessionData obj;
  std::uint8_t offset;

  // parse header
  offset = 0;
  obj.m_header = ParsePacketHeader(parse_bytes_to_pairs(PacketHeaderSizes(), bytes, offset));

  // marshal zones

  // weather forecast samples

  // write the rest directly to object

  return obj;
}

std::vector<std::pair<int, std::string>> PacketSessionDataPairs {

};
