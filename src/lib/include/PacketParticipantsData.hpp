#pragma once

#include <cstdint>
#include "PacketHeader.hpp"

#pragma pack(push, 1)

struct ParticipantData
{
  std::uint8_t m_aiControlled;  // Whether the vehicle is AI (1) or Human (0) controlled
  std::uint8_t m_driverId;      // Driver id - see appendix, 255 if network human
  std::uint8_t m_networkId;     // Network id – unique identifier for network players
  std::uint8_t m_teamId;        // Team id - see appendix
  std::uint8_t m_myTeam;        // My team flag – 1 = My Team, 0 = otherwise
  std::uint8_t m_raceNumber;    // Race number of the car
  std::uint8_t m_nationality;   // Nationality of the driver
  char m_name[48];              // Name of participant in UTF-8 format – null terminated
                                // Will be truncated with … (U+2026) if too long
  std::uint8_t m_yourTelemetry; // The player's UDP setting, 0 = restricted, 1 = public
};

struct PacketParticipantsData
{
  PacketHeader m_header; // Header

  std::uint8_t m_numActiveCars; // Number of active cars in the data – should match number of
                                // cars on HUD
  ParticipantData m_participants[22];
};

#pragma pack(pop)
