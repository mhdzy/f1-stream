#pragma once

#include <cstdint>

#include "File.hpp"
#include "PacketHeader.hpp"

#pragma pack(push, 1)

struct ParticipantData {
  std::uint8_t m_aiControlled;   // Whether the vehicle is AI (1) or Human (0) controlled
  std::uint8_t m_driverId;       // Driver id - see appendix, 255 if network human
  std::uint8_t m_networkId;      // Network id – unique identifier for network players
  std::uint8_t m_teamId;         // Team id - see appendix
  std::uint8_t m_myTeam;         // My team flag – 1 = My Team, 0 = otherwise
  std::uint8_t m_raceNumber;     // Race number of the car
  std::uint8_t m_nationality;    // Nationality of the driver
  char m_name[48];               // Name of participant in UTF-8 format – null terminated
                                 // Will be truncated with … (U+2026) if too long
  std::uint8_t m_yourTelemetry;  // The player's UDP setting, 0 = restricted, 1 = public
};

struct ParticipantMetadata {
  std::uint8_t m_numActiveCars;  // Number of active cars in the data – should match number of
                                 // cars on HUD
};

struct PacketParticipantsData {
  PacketHeader m_header;  // Header
  ParticipantMetadata m_participant; // contains info about m_participants
  ParticipantData m_participants[22];
};

#pragma pack(pop)

extern std::vector<std::size_t> ParticipantDataSizes;
extern std::vector<std::string> ParticipantDataNames;
extern std::string ParticipantDataString(ParticipantData obj, std::string sep = ",");
extern ParticipantData ParseParticipantData(std::vector<std::vector<unsigned char>> bytes);

extern std::vector<std::size_t> ParticipantMetadataSizes;
extern std::vector<std::string> ParticipantMetadataNames;
extern std::string ParticipantMetadataString(ParticipantMetadata obj, std::string sep = ",");
extern ParticipantMetadata ParseParticipantMetadata(std::vector<std::vector<unsigned char>> bytes);

extern std::string PacketParticipantsDataCSVHeader(std::string sep = ",");
extern std::string PacketParticipantsDataString(PacketParticipantsData obj, std::uint8_t carID, std::string sep = ",");
extern PacketParticipantsData ParsePacketParticipantsData(std::vector<unsigned char> bytes);
