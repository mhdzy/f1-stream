#pragma once

#include <cstdint>

#include "File.hpp"
#include "PacketHeader.hpp"

#pragma pack(push, 1)

struct MarshalZone {
  float m_zoneStart;       // Fraction (0..1) of way through the lap the marshal zone starts
  std::int8_t m_zoneFlag;  // -1 = invalid/unknown, 0 = none, 1 = green, 2 = blue, 3 = yellow, 4 = red
};

struct WeatherForecastSample {
  std::uint8_t m_sessionType;            // 0 = unknown, 1 = P1, 2 = P2, 3 = P3, 4 = Short P, 5 = Q1
                                         // 6 = Q2, 7 = Q3, 8 = Short Q, 9 = OSQ, 10 = R, 11 = R2
                                         // 12 = R3, 13 = Time Trial
  std::uint8_t m_timeOffset;             // Time in minutes the forecast is for
  std::uint8_t m_weather;                // Weather - 0 = clear, 1 = light cloud, 2 = overcast
                                         // 3 = light rain, 4 = heavy rain, 5 = storm
  std::int8_t m_trackTemperature;        // Track temp. in degrees Celsius
  std::int8_t m_trackTemperatureChange;  // Track temp. change – 0 = up, 1 = down, 2 = no change
  std::int8_t m_airTemperature;          // Air temp. in degrees celsius
  std::int8_t m_airTemperatureChange;    // Air temp. change – 0 = up, 1 = down, 2 = no change
  std::uint8_t m_rainPercentage;         // Rain percentage (0-100)
};

struct PacketSessionDataTop {
  std::uint8_t m_weather;              // Weather - 0 = clear, 1 = light cloud, 2 = overcast
                                       // 3 = light rain, 4 = heavy rain, 5 = storm
  std::int8_t m_trackTemperature;      // Track temp. in degrees celsius
  std::int8_t m_airTemperature;        // Air temp. in degrees celsius
  std::uint8_t m_totalLaps;            // Total number of laps in this race
  std::uint16_t m_trackLength;         // Track length in metres
  std::uint8_t m_sessionType;          // 0 = unknown, 1 = P1, 2 = P2, 3 = P3, 4 = Short P
                                       // 5 = Q1, 6 = Q2, 7 = Q3, 8 = Short Q, 9 = OSQ
                                       // 10 = R, 11 = R2, 12 = R3, 13 = Time Trial
  std::int8_t m_trackId;               // -1 for unknown, see appendix
  std::uint8_t m_formula;              // Formula, 0 = F1 Modern, 1 = F1 Classic, 2 = F2,
                                       // 3 = F1 Generic, 4 = Beta, 5 = Supercars
                                       // 6 = Esports, 7 = F2 2021
  std::uint16_t m_sessionTimeLeft;     // Time left in session in seconds
  std::uint16_t m_sessionDuration;     // Session duration in seconds
  std::uint8_t m_pitSpeedLimit;        // Pit speed limit in kilometres per hour
  std::uint8_t m_gamePaused;           // Whether the game is paused – network game only
  std::uint8_t m_isSpectating;         // Whether the player is spectating
  std::uint8_t m_spectatorCarIndex;    // Index of the car being spectated
  std::uint8_t m_sliProNativeSupport;  // SLI Pro support, 0 = inactive, 1 = active
  std::uint8_t m_numMarshalZones;      // Number of marshal zones to follow
};

struct PacketSessionDataMid {
  std::uint8_t m_safetyCarStatus;            // 0 = no safety car, 1 = full
                                             // 2 = virtual, 3 = formation lap
  std::uint8_t m_networkGame;                // 0 = offline, 1 = online
  std::uint8_t m_numWeatherForecastSamples;  // Number of weather samples to follow
};

struct PacketSessionDataBot {
  std::uint8_t m_forecastAccuracy;        // 0 = Perfect, 1 = Approximate
  std::uint8_t m_aiDifficulty;            // AI Difficulty rating – 0-110
  std::uint32_t m_seasonLinkIdentifier;   // Identifier for season - persists across saves
  std::uint32_t m_weekendLinkIdentifier;  // Identifier for weekend - persists across saves
  std::uint32_t m_sessionLinkIdentifier;  // Identifier for session - persists across saves
  std::uint8_t m_pitStopWindowIdealLap;   // Ideal lap to pit on for current strategy (player)
  std::uint8_t m_pitStopWindowLatestLap;  // Latest lap to pit on for current strategy (player)
  std::uint8_t m_pitStopRejoinPosition;   // Predicted position to rejoin at (player)
  std::uint8_t m_steeringAssist;          // 0 = off, 1 = on
  std::uint8_t m_brakingAssist;           // 0 = off, 1 = low, 2 = medium, 3 = high
  std::uint8_t m_gearboxAssist;           // 1 = manual, 2 = manual & suggested gear, 3 = auto
  std::uint8_t m_pitAssist;               // 0 = off, 1 = on
  std::uint8_t m_pitReleaseAssist;        // 0 = off, 1 = on
  std::uint8_t m_ERSAssist;               // 0 = off, 1 = on
  std::uint8_t m_DRSAssist;               // 0 = off, 1 = on
  std::uint8_t m_dynamicRacingLine;       // 0 = off, 1 = corners only, 2 = full
  std::uint8_t m_dynamicRacingLineType;   // 0 = 2D, 1 = 3D
  std::uint8_t m_gameMode;                // Game mode id - see appendix
  std::uint8_t m_ruleSet;                 // Ruleset - see appendix
  std::uint32_t m_timeOfDay;              // Local time of day - minutes since midnight
  std::uint8_t m_sessionLength;           // 0 = None, 2 = Very Short, 3 = Short, 4 = Medium,
                                          // 5 = Medium Long, 6 = Long, 7 = Full
};

struct PacketSessionData {
  PacketHeader m_header;  // Header

  PacketSessionDataTop m_packetSessionDataTop;         // top portion of struct fields
  MarshalZone m_marshalZones[21];                      // List of marshal zones – max 21
  PacketSessionDataMid m_packetSessionDataMid;         // middle portion of struct fields
  WeatherForecastSample m_weatherForecastSamples[56];  // Array of weather forecast samples
  PacketSessionDataBot m_PacketSessionDataBot;   // bottom portion of struct fields
};

#pragma pack(pop)

extern std::vector<std::size_t> MarshalZoneSizes;
extern std::vector<std::string> MarshalZoneNames;
extern std::string MarshalZoneCSVHeader(std::string sep = ",");
extern std::string MarshalZoneString(MarshalZone obj, std::string sep = ",");
extern MarshalZone ParseMarshalZone(std::vector<std::vector<unsigned char>> bytes);

extern std::vector<std::size_t> WeatherForecastSampleSizes;
extern std::vector<std::string> WeatherForecastSampleNames;
extern std::string WeatherForecastSampleCSVHeader(std::string sep = ",");
extern std::string WeatherForecastSampleString(WeatherForecastSample obj, std::string sep = ",");
extern WeatherForecastSample ParseWeatherForecastSample(std::vector<std::vector<unsigned char>> bytes);

extern std::vector<std::size_t> PacketSessionDataTopSizes;
extern std::vector<std::string> PacketSessionDataTopNames;
extern std::string PacketSessionDataTopCSVHeader();
extern std::string PacketSessionDataTopString(PacketSessionDataTop obj, std::string sep = ",");
extern PacketSessionDataTop ParsePacketSessionDataTop(std::vector<std::vector<unsigned char>> bytes);

extern std::vector<std::size_t> PacketSessionDataMidSizes;
extern std::vector<std::string> PacketSessionDataMidNames;
extern std::string PacketSessionDataMidCSVHeader();
extern std::string PacketSessionDataMidString(PacketSessionDataMid obj, std::string sep = ",");
extern PacketSessionDataMid ParsePacketSessionDataMid(std::vector<std::vector<unsigned char>> bytes);

extern std::vector<std::size_t> PacketSessionDataBotSizes;
extern std::vector<std::string> PacketSessionDataBotNames;
extern std::string PacketSessionDataBotCSVHeader();
extern std::string PacketSessionDataBotString(PacketSessionDataBot obj, std::string sep = ",");
extern PacketSessionDataBot ParsePacketSessionDataBot(std::vector<std::vector<unsigned char>> bytes);

extern std::string PacketSessionDataCSVHeader(std::string sep = ",", std::string compr = "/");
extern std::string PacketSessionDataString(PacketSessionData obj, std::string sep = ",", std::string compr = "/");
extern PacketSessionData ParsePacketSessionData(std::vector<unsigned char> bytes);
extern std::vector<std::size_t> PacketSessionDataSizes();
