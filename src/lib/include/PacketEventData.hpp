#pragma once

#include <cstdint>
#include <cstring>
#include <vector>

#include "PacketHeader.hpp"

#pragma pack(push, 1)

// The event details packet is different for each type of event.
// Make sure only the correct type is interpreted.
union EventDataDetails {
  struct {
    std::uint8_t vehicleIdx;  // Vehicle index of car achieving fastest lap
    float lapTime;            // Lap time is in seconds
  } FastestLap;

  struct {
    std::uint8_t vehicleIdx;  // Vehicle index of car retiring
  } Retirement;

  struct {
    std::uint8_t vehicleIdx;  // Vehicle index of team mate
  } TeamMateInPits;

  struct {
    std::uint8_t vehicleIdx;  // Vehicle index of the race winner
  } RaceWinner;

  struct {
    std::uint8_t penaltyType;       // Penalty type – see Appendices
    std::uint8_t infringementType;  // Infringement type – see Appendices
    std::uint8_t vehicleIdx;        // Vehicle index of the car the penalty is applied to
    std::uint8_t otherVehicleIdx;   // Vehicle index of the other car involved
    std::uint8_t time;              // Time gained, or time spent doing action in seconds
    std::uint8_t lapNum;            // Lap the penalty occurred on
    std::uint8_t placesGained;      // Number of places gained by this
  } Penalty;

  struct {
    std::uint8_t vehicleIdx;                  // Vehicle index of the vehicle triggering speed trap
    float speed;                              // Top speed achieved in kilometres per hour
    std::uint8_t isOverallFastestInSession;   // Overall fastest speed in session = 1, otherwise 0
    std::uint8_t isDriverFastestInSession;    // Fastest speed for driver in session = 1, otherwise 0
    std::uint8_t fastestVehicleIdxInSession;  // Vehicle index of the vehicle that is the fastest
                                              // in this session
    float fastestSpeedInSession;              // Speed of the vehicle that is the fastest
                                              // in this session
  } SpeedTrap;

  struct {
    std::uint8_t numLights;  // Number of lights showing
  } StartLIghts;

  struct {
    std::uint8_t vehicleIdx;  // Vehicle index of the vehicle serving drive through
  } DriveThroughPenaltyServed;

  struct {
    std::uint8_t vehicleIdx;  // Vehicle index of the vehicle serving stop go
  } StopGoPenaltyServed;

  struct {
    std::uint32_t flashbackFrameIdentifier;  // Frame identifier flashed back to
    float flashbackSessionTime;              // Session time flashed back to
  } Flashback;

  struct {
    std::uint32_t m_buttonStatus;  // Bit flags specifying which buttons are being pressed
                                   // currently - see appendices
  } Buttons;
};

// The event details packet is different for each type of event.
// Make sure only the correct type is interpreted.
struct EventDataDetailsStruct {
  std::string eventCode;  // string representation of the event code

  std::uint8_t vehicleIdx;  // Vehicle index of car achieving fastest lap

  // FastestLap
  float lapTime;  // Lap time is in seconds

  // Retirement
  // std::uint8_t vehicleIdx;  // Vehicle index of car retiring

  // TeamMateInPits
  // std::uint8_t vehicleIdx;  // Vehicle index of team mate

  // RaceWinner
  // std::uint8_t vehicleIdx;  // Vehicle index of the race winner

  // Penalty
  std::uint8_t penaltyType;       // Penalty type – see Appendices
  std::uint8_t infringementType;  // Infringement type – see Appendices
  // std::uint8_t vehicleIdx;        // Vehicle index of the car the penalty is applied to
  std::uint8_t otherVehicleIdx;  // Vehicle index of the other car involved
  std::uint8_t time;             // Time gained, or time spent doing action in seconds
  std::uint8_t lapNum;           // Lap the penalty occurred on
  std::uint8_t placesGained;     // Number of places gained by this

  // SpeedTrap;
  // std::uint8_t vehicleIdx;                  // Vehicle index of the vehicle triggering speed trap
  float speed;                              // Top speed achieved in kilometres per hour
  std::uint8_t isOverallFastestInSession;   // Overall fastest speed in session = 1, otherwise 0
  std::uint8_t isDriverFastestInSession;    // Fastest speed for driver in session = 1, otherwise 0
  std::uint8_t fastestVehicleIdxInSession;  // Vehicle index of the vehicle that is the fastest
                                            // in this session
  float fastestSpeedInSession;              // Speed of the vehicle that is the fastest
                                            // in this session

  // StartLights;
  std::uint8_t numLights;  // Number of lights showing

  // DriveThroughPenaltyServed;
  // std::uint8_t vehicleIdx;  // Vehicle index of the vehicle serving drive through

  // StopGoPenaltyServed;
  // std::uint8_t vehicleIdx;  // Vehicle index of the vehicle serving stop go

  // Flashback;
  std::uint32_t flashbackFrameIdentifier;  // Frame identifier flashed back to
  float flashbackSessionTime;              // Session time flashed back to

  // Buttons;
  std::uint32_t m_buttonStatus;  // Bit flags specifying which buttons are being pressed
                                 // currently - see appendices
};

struct PacketEventData {
  PacketHeader m_header;  // Header

  std::uint8_t m_eventStringCode[4];  // Event string code, see below
  EventDataDetails m_eventDetails;    // Event details - should be interpreted differently
                                      // for each type
};

#pragma pack(pop)

extern std::vector<std::size_t> EventDataDetailsSizes;
extern std::vector<std::string> EventDataDetailsNames;
extern std::string EventDataDetailsString(EventDataDetails obj, std::string sep = ",");
extern EventDataDetails ParseEventDataDetails(std::vector<std::vector<unsigned char>> bytes);

extern std::string PacketEventDataCSVHeader(std::string sep = ",", std::string compr = "/");
extern std::string PacketEventDataString(PacketEventData obj, std::string sep = ",");
extern PacketEventData ParsePacketEventData(std::vector<unsigned char> bytes);
