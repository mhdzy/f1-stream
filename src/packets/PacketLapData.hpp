#pragma once

#include <cstdint>

#include "../utils/File.hpp"
#include "PacketHeader.hpp"

#pragma pack(push, 1)

struct LapData {
  std::uint32_t m_lastLapTimeInMS;             // Last lap time in milliseconds
  std::uint32_t m_currentLapTimeInMS;          // Current time around the lap in milliseconds
  std::uint16_t m_sector1TimeInMS;             // Sector 1 time in milliseconds
  std::uint16_t m_sector2TimeInMS;             // Sector 2 time in milliseconds
  float m_lapDistance;                         // Distance vehicle is around current lap in metres – could
                                               // be negative if line hasn’t been crossed yet
  float m_totalDistance;                       // Total distance travelled in session in metres – could
                                               // be negative if line hasn’t been crossed yet
  float m_safetyCarDelta;                      // Delta in seconds for safety car
  std::uint8_t m_carPosition;                  // Car race position
  std::uint8_t m_currentLapNum;                // Current lap number
  std::uint8_t m_pitStatus;                    // 0 = none, 1 = pitting, 2 = in pit area
  std::uint8_t m_numPitStops;                  // Number of pit stops taken in this race
  std::uint8_t m_sector;                       // 0 = sector1, 1 = sector2, 2 = sector3
  std::uint8_t m_currentLapInvalid;            // Current lap invalid - 0 = valid, 1 = invalid
  std::uint8_t m_penalties;                    // Accumulated time penalties in seconds to be added
  std::uint8_t m_warnings;                     // Accumulated number of warnings issued
  std::uint8_t m_numUnservedDriveThroughPens;  // Num drive through pens left to serve
  std::uint8_t m_numUnservedStopGoPens;        // Num stop go pens left to serve
  std::uint8_t m_gridPosition;                 // Grid position the vehicle started the race in
  std::uint8_t m_driverStatus;                 // Status of driver - 0 = in garage, 1 = flying lap
                                               // 2 = in lap, 3 = out lap, 4 = on track
  std::uint8_t m_resultStatus;                 // Result status - 0 = invalid, 1 = inactive, 2 = active
                                               // 3 = finished, 4 = didnotfinish, 5 = disqualified
                                               // 6 = not classified, 7 = retired
  std::uint8_t m_pitLaneTimerActive;           // Pit lane timing, 0 = inactive, 1 = active
  std::uint16_t m_pitLaneTimeInLaneInMS;       // If active, the current time spent in the pit lane in ms
  std::uint16_t m_pitStopTimerInMS;            // Time of the actual pit stop in ms
  std::uint8_t m_pitStopShouldServePen;        // Whether the car should serve a penalty at this stop
};

struct LapDataIdx {
  std::uint8_t m_timeTrialPBCarIdx;     // Index of Personal Best car in time trial (255 if invalid)
  std::uint8_t m_timeTrialRivalCarIdx;  // Index of Rival car in time trial (255 if invalid)
};

struct PacketLapData {
  PacketHeader m_header;  // Header

  LapData m_lapData[22];    // Lap data for all cars on track
  LapDataIdx m_lapDataIdx;  // Lap data index information (pb and rival)
};

#pragma pack(pop)

extern std::vector<std::size_t> LapDataSizes;
extern std::vector<std::string> LapDataNames;
extern std::string LapDataString(LapData obj, std::string sep = ",");
extern LapData ParseLapData(std::vector<std::vector<unsigned char>> bytes);

extern std::vector<std::size_t> LapDataIdxSizes;
extern std::vector<std::string> LapDataIdxNames;
extern std::string LapDataIdxString(LapDataIdx obj, std::string sep = ",");
extern LapDataIdx ParseLapDataIdx(std::vector<std::vector<unsigned char>> bytes);

extern std::string PacketLapDataCSVHeader(std::string sep = ",", std::string compr = "/");
extern std::string PacketLapDataString(PacketLapData obj, std::uint8_t carID, std::string sep = ",",
                                       std::string compr = "/", std::string compr2 = ";");
extern PacketLapData ParsePacketLapData(std::vector<unsigned char> bytes);
