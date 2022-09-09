
#include "../include/PacketEventData.hpp"

// stores metadata about each event type (key) with short info (.first) and long info (.second)
std::map<std::string, std::pair<std::string, std::string>> Events = {
    {"SSTA", std::make_pair("Session Started", "Sent when the session starts")},
    {"SEND", std::make_pair("Session Ended", "Sent when the session ends")},
    {"FLTP", std::make_pair("Fastest Lap", "When a driver achieves the fastest lap")},
    {"RTMT", std::make_pair("Retirement", "When a driver retires")},
    {"DRSE", std::make_pair("DRS enabled", "Race control have enabled DRS")},
    {"DRSD", std::make_pair("DRS disabled", "Race control have disabled DRS")},
    {"TMPT", std::make_pair("Team mate in pits", "Your team mate has entered the pits")},
    {"CHQF", std::make_pair("Chequered flag", "The chequered flag has been waved")},
    {"RCWN", std::make_pair("Race Winner", "The race winner is announced")},
    {"PENA", std::make_pair("Penalty Issued", "A penalty has been issued – details in event")},
    {"SPTP", std::make_pair("Speed Trap Triggered", "Speed trap has been triggered by fastest speed")},
    {"STLG", std::make_pair("Start lights", "Start lights – number shown")},
    {"LGOT", std::make_pair("Lights out", "Lights out")},
    {"DTSV", std::make_pair("Drive through served", "Drive through penalty served")},
    {"SGSV", std::make_pair("Stop go served", "Stop go penalty served")},
    {"FLBK", std::make_pair("Flashback", "Flashback activated")},
    {"BUTN", std::make_pair("Button status", "Button status changed")}};

std::vector<std::size_t> EventDataDetailsSizes = {
    // unused
};

std::vector<std::string> EventDataDetailsNames = {
    "eventCode",                   // string representation of the event code
    "vehicleIdx",                  // Vehicle index of car achieving fastest lap
    "lapTime",                     // Lap time is in seconds
    "penaltyType",                 // Penalty type – see Appendices
    "infringementType",            // Infringement type – see Appendices
    "otherVehicleIdx",             // Vehicle index of the other car involved
    "time",                        // Time gained, or time spent doing action in seconds
    "lapNum",                      // Lap the penalty occurred on
    "placesGained",                // Number of places gained by this
    "speed",                       // Top speed achieved in kilometres per hour
    "isOverallFastestInSession",   // Overall fastest speed in session = 1, otherwise 0
    "isDriverFastestInSession",    // Fastest speed for driver in session = 1, otherwise 0
    "fastestVehicleIdxInSession",  // Vehicle index of the vehicle that is the fastest in this session
    "fastestSpeedInSession",       // Speed of the vehicle that is the fastest in this session
    "numLights",                   // Number of lights showing
    "flashbackFrameIdentifier",    // Frame identifier flashed back to
    "flashbackSessionTime",        // Session time flashed back to
    "m_buttonStatus",              // Bit flags specifying which buttons are being pressed currently - see appendices
};

std::string EventDataDetailsString(EventDataDetails obj, std::string sep) {
  const char *fmt = "%s%s%d%s%f%s%d%s%d%s%d%s%d%s%d%s%d%s%f%s%d%s%d%s%d%s%f%s%d%s%d%s%f%s%d";
  const char *ssep = sep.c_str();

  const std::size_t size = std::snprintf(
      nullptr, 0, fmt, obj.eventCode.c_str(), ssep, obj.vehicleIdx, ssep, obj.lapTime, ssep, obj.penaltyType, ssep,
      obj.infringementType, ssep, obj.otherVehicleIdx, ssep, obj.time, ssep, obj.lapNum, ssep, obj.placesGained, ssep,
      obj.speed, ssep, obj.isOverallFastestInSession, ssep, obj.isDriverFastestInSession, ssep,
      obj.fastestVehicleIdxInSession, ssep, obj.fastestSpeedInSession, ssep, obj.numLights, ssep,
      obj.flashbackFrameIdentifier, ssep, obj.flashbackSessionTime, ssep, obj.m_buttonStatus);

  std::vector<char> buf(size + 1);  // note +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.eventCode.c_str(), ssep, obj.vehicleIdx, ssep, obj.lapTime, ssep,
                obj.penaltyType, ssep, obj.infringementType, ssep, obj.otherVehicleIdx, ssep, obj.time, ssep,
                obj.lapNum, ssep, obj.placesGained, ssep, obj.speed, ssep, obj.isOverallFastestInSession, ssep,
                obj.isDriverFastestInSession, ssep, obj.fastestVehicleIdxInSession, ssep, obj.fastestSpeedInSession,
                ssep, obj.numLights, ssep, obj.flashbackFrameIdentifier, ssep, obj.flashbackSessionTime, ssep,
                obj.m_buttonStatus);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));

  return str;
}

EventDataDetails ParseEventDataDetails(std::vector<std::vector<unsigned char>> bytes) {
  EventDataDetails obj;
  // could be used to parse the event struct, but requires taking in a "ec" event code,
  // vector<uchar> and offset
  return obj;
}

std::string PacketEventDataCSVHeader(std::string sep, std::string compr) {
  std::vector<std::string> vec = {
      vpaste(PacketHeaderNames, sep),     //
      vpaste(EventDataDetailsNames, sep)  //
  };
  return vpaste(vec, sep);
}

template <>
std::string packetDataString(PacketEventData obj, std::uint8_t id, std::string sep, std::string compr,
                             std::string compr2) {
  std::vector<std::string> vec = {
      PacketHeaderString(obj.m_header),           //
      EventDataDetailsString(obj.m_eventDetails)  //
  };
  return vpaste(vec, sep);
}

template <>
PacketEventData parsePacketData<PacketEventData>(std::vector<unsigned char> bytes) {
  PacketEventData obj;
  std::uint16_t offset = 0;

  obj.m_header = ParsePacketHeader(parseBytes(PacketHeaderSizes, bytes, offset));
  offset += sizeof(PacketHeader);

  // extract packet type
  for (std::uint8_t i : {0, 1, 2, 3})
    // don't use "&bytes.at().front()" since it's only a 1d vector (not 2d)
    std::memcpy(&obj.m_eventStringCode[i], &bytes.at(offset) + (i * sizeof obj.m_eventStringCode[i]),
                sizeof obj.m_eventStringCode[i]);
  offset += sizeof obj.m_eventStringCode;

  obj.m_eventDetails.eventCode = std::string{(char *)obj.m_eventStringCode};
  std::string ec = obj.m_eventDetails.eventCode;

  if (ec == "FTLP" || ec == "RTMT" || ec == "TMPT" || ec == "RCWN" || ec == "SPTP" || ec == "DTSV" || ec == "SGSV") {
    // the vehicle idx is the first uint8 field for all of these events
    std::memcpy(&obj.m_eventDetails.vehicleIdx, &bytes.at(offset), sizeof obj.m_eventDetails.vehicleIdx);
    offset += sizeof obj.m_eventDetails.vehicleIdx;
  }

  if (ec == "FTLP") {
    // there is an extra field here
    std::memcpy(&obj.m_eventDetails.lapTime, &bytes.at(offset), sizeof obj.m_eventDetails.lapTime);
    offset += sizeof obj.m_eventDetails.lapTime;
  } else if (ec == "PENA") {
    // lots of other uint8 fields
    std::memcpy(&obj.m_eventDetails.penaltyType, &bytes.at(offset), sizeof obj.m_eventDetails.penaltyType);
    offset += sizeof obj.m_eventDetails.penaltyType;

    std::memcpy(&obj.m_eventDetails.infringementType, &bytes.at(offset), sizeof obj.m_eventDetails.infringementType);
    offset += sizeof obj.m_eventDetails.infringementType;

    std::memcpy(&obj.m_eventDetails.vehicleIdx, &bytes.at(offset), sizeof obj.m_eventDetails.vehicleIdx);
    offset += sizeof obj.m_eventDetails.vehicleIdx;

    std::memcpy(&obj.m_eventDetails.otherVehicleIdx, &bytes.at(offset), sizeof obj.m_eventDetails.otherVehicleIdx);
    offset += sizeof obj.m_eventDetails.otherVehicleIdx;

    std::memcpy(&obj.m_eventDetails.time, &bytes.at(offset), sizeof obj.m_eventDetails.time);
    offset += sizeof obj.m_eventDetails.time;

    std::memcpy(&obj.m_eventDetails.lapNum, &bytes.at(offset), sizeof obj.m_eventDetails.lapNum);
    offset += sizeof obj.m_eventDetails.lapNum;

    std::memcpy(&obj.m_eventDetails.placesGained, &bytes.at(offset), sizeof obj.m_eventDetails.placesGained);
    offset += sizeof obj.m_eventDetails.placesGained;
  } else if (ec == "SPTP") {
    // lots of other fields
    std::memcpy(&obj.m_eventDetails.speed, &bytes.at(offset), sizeof obj.m_eventDetails.speed);
    offset += sizeof obj.m_eventDetails.speed;

    std::memcpy(&obj.m_eventDetails.isOverallFastestInSession, &bytes.at(offset),
                sizeof obj.m_eventDetails.isOverallFastestInSession);
    offset += sizeof obj.m_eventDetails.isOverallFastestInSession;

    std::memcpy(&obj.m_eventDetails.isDriverFastestInSession, &bytes.at(offset),
                sizeof obj.m_eventDetails.isDriverFastestInSession);
    offset += sizeof obj.m_eventDetails.isDriverFastestInSession;

    std::memcpy(&obj.m_eventDetails.fastestVehicleIdxInSession, &bytes.at(offset),
                sizeof obj.m_eventDetails.fastestVehicleIdxInSession);
    offset += sizeof obj.m_eventDetails.fastestVehicleIdxInSession;

    std::memcpy(&obj.m_eventDetails.fastestSpeedInSession, &bytes.at(offset),
                sizeof obj.m_eventDetails.fastestSpeedInSession);
    offset += sizeof obj.m_eventDetails.fastestSpeedInSession;
  } else if (ec == "STLG") {
    std::memcpy(&obj.m_eventDetails.numLights, &bytes.at(offset), sizeof obj.m_eventDetails.numLights);
    offset += sizeof obj.m_eventDetails.numLights;
  } else if (ec == "FLBK") {
    std::memcpy(&obj.m_eventDetails.flashbackFrameIdentifier, &bytes.at(offset),
                sizeof obj.m_eventDetails.flashbackFrameIdentifier);
    offset += sizeof obj.m_eventDetails.flashbackFrameIdentifier;

    std::memcpy(&obj.m_eventDetails.flashbackSessionTime, &bytes.at(offset),
                sizeof obj.m_eventDetails.flashbackSessionTime);
    offset += sizeof obj.m_eventDetails.flashbackSessionTime;
  } else if (ec == "BUTN") {
    std::memcpy(&obj.m_eventDetails.m_buttonStatus, &bytes.at(offset), sizeof obj.m_eventDetails.m_buttonStatus);
    offset += sizeof obj.m_eventDetails.m_buttonStatus;
  }

  return obj;
}
