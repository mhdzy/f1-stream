#pragma once

#include <cstdint>

#include "Bytes.hpp"
#include "File.hpp"
#include "PacketHeader.hpp"

#pragma pack(push, 1)

struct FinalClassificationData {
  std::uint8_t m_position;              // Finishing position
  std::uint8_t m_numLaps;               // Number of laps completed
  std::uint8_t m_gridPosition;          // Grid position of the car
  std::uint8_t m_points;                // Number of points scored
  std::uint8_t m_numPitStops;           // Number of pit stops made
  std::uint8_t m_resultStatus;          // Result status - 0 = invalid, 1 = inactive, 2 = active
                                        // 3 = finished, 4 = didnotfinish, 5 = disqualified
                                        // 6 = not classified, 7 = retired
  std::uint32_t m_bestLapTimeInMS;      // Best lap time of the session in milliseconds
  double m_totalRaceTime;               // Total race time in seconds without penalties
  std::uint8_t m_penaltiesTime;         // Total penalties accumulated in seconds
  std::uint8_t m_numPenalties;          // Number of penalties applied to this driver
  std::uint8_t m_numTyreStints;         // Number of tyres stints up to maximum
  std::uint8_t m_tyreStintsActual[8];   // Actual tyres used by this driver
  std::uint8_t m_tyreStintsVisual[8];   // Visual tyres used by this driver
  std::uint8_t m_tyreStintsEndLaps[8];  // The lap number stints end on
};

struct FinalClassificationMeta {
  std::uint8_t m_numCars;  // Number of cars in the final classification
};

struct PacketFinalClassificationData {
  PacketHeader m_header;  // Header
  FinalClassificationMeta m_classificationMeta;
  FinalClassificationData m_classificationData[22];
};

#pragma pack(pop)

extern std::vector<std::size_t> FinalClassificationDataSizes;
extern std::vector<std::string> FinalClassificationDataNames;
extern std::string FinalClassificationDataString(FinalClassificationData obj, std::string sep = ",");
extern FinalClassificationData ParseFinalClassificationData(std::vector<std::vector<unsigned char>> bytes);

extern std::vector<std::size_t> FinalClassificationMetaSizes;
extern std::vector<std::string> FinalClassificationMetaNames;
extern std::string FinalClassificationMetaString(FinalClassificationMeta obj, std::string sep = ",");
extern FinalClassificationMeta ParseFinalClassificationMeta(std::vector<std::vector<unsigned char>> bytes);

extern std::string PacketFinalClassificationDataCSVHeader(std::string sep = ",");
extern std::string PacketFinalClassificationDataString(PacketFinalClassificationData obj, std::uint8_t carID,
                                                       std::string sep = ",");
extern PacketFinalClassificationData ParsePacketFinalClassificationData(std::vector<unsigned char> bytes);
