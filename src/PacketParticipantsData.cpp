#include "../include/PacketParticipantsData.hpp"

std::vector<std::size_t> ParticipantDataSizes = {
    sizeof(((ParticipantData *)0)->m_aiControlled),  // Whether the vehicle is AI (1) or Human (0) controlled
    sizeof(((ParticipantData *)0)->m_driverId),      // Driver id - see appendix, 255 if network human
    sizeof(((ParticipantData *)0)->m_networkId),     // Network id – unique identifier for network players
    sizeof(((ParticipantData *)0)->m_teamId),        // Team id - see appendix
    sizeof(((ParticipantData *)0)->m_myTeam),        // My team flag – 1 = My Team, 0 = otherwise
    sizeof(((ParticipantData *)0)->m_raceNumber),    // Race number of the car
    sizeof(((ParticipantData *)0)->m_nationality),   // Nationality of the driver
    sizeof(((ParticipantData *)0)->m_name),          // Name of participant in UTF-8 format – null terminated
                                                     // Will be truncated with … (U+2026) if too long
    sizeof(((ParticipantData *)0)->m_yourTelemetry)  // The player's UDP setting, 0 = restricted, 1 = public
};

std::vector<std::string> ParticipantDataNames = {
    "m_aiControlled",  // Whether the vehicle is AI (1) or Human (0) controlled
    "m_driverId",      // Driver id - see appendix, 255 if network human
    "m_networkId",     // Network id – unique identifier for network players
    "m_teamId",        // Team id - see appendix
    "m_myTeam",        // My team flag – 1 = My Team, 0 = otherwise
    "m_raceNumber",    // Race number of the car
    "m_nationality",   // Nationality of the driver
    "m_name",          // Name of participant in UTF-8 format – null terminated
                       // Will be truncated with … (U+2026) if too long
    "m_yourTelemetry"  // The player's UDP setting, 0 = restricted, 1 = public
};

std::vector<std::size_t> ParticipantMetadataSizes = {
    sizeof(((ParticipantMetadata *)0)->m_numActiveCars)  // Number of active cars in the data – should match number of
                                                         // cars on HUD
};

std::vector<std::string> ParticipantMetadataNames = {
    "m_numActiveCars"  // Number of active cars in the data – should match number of
                       // cars on HUD
};

std::string ParticipantDataString(ParticipantData obj, std::string sep) {
  const char *fmt = "%d%s%d%s%d%s%d%s%d%s%d%s%d%s%s%s%d";
  const char *ssep = sep.c_str();

  const std::size_t size = std::snprintf(
      nullptr, 0, fmt, obj.m_aiControlled, ssep, obj.m_driverId, ssep, obj.m_networkId, ssep, obj.m_teamId, ssep,
      obj.m_myTeam, ssep, obj.m_raceNumber, ssep, obj.m_nationality, ssep, obj.m_name, ssep, obj.m_yourTelemetry);

  std::vector<char> buf(size + 1);  // note +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.m_aiControlled, ssep, obj.m_driverId, ssep, obj.m_networkId, ssep,
                obj.m_teamId, ssep, obj.m_myTeam, ssep, obj.m_raceNumber, ssep, obj.m_nationality, ssep, obj.m_name,
                ssep, obj.m_yourTelemetry);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));  // remove null terminator

  return str;
}

ParticipantData ParseParticipantData(std::vector<std::vector<unsigned char>> bytes) {
  ParticipantData obj;
  std::memcpy(&obj.m_aiControlled, &bytes.at(0).front(), sizeof obj.m_aiControlled);
  std::memcpy(&obj.m_driverId, &bytes.at(1).front(), sizeof obj.m_driverId);
  std::memcpy(&obj.m_networkId, &bytes.at(2).front(), sizeof obj.m_networkId);
  std::memcpy(&obj.m_teamId, &bytes.at(3).front(), sizeof obj.m_teamId);
  std::memcpy(&obj.m_myTeam, &bytes.at(4).front(), sizeof obj.m_myTeam);
  std::memcpy(&obj.m_raceNumber, &bytes.at(5).front(), sizeof obj.m_raceNumber);
  std::memcpy(&obj.m_nationality, &bytes.at(6).front(), sizeof obj.m_nationality);
  std::memcpy(&obj.m_name, &bytes.at(7).front(), sizeof obj.m_name);
  std::memcpy(&obj.m_yourTelemetry, &bytes.at(8).front(), sizeof obj.m_yourTelemetry);
  return obj;
}

std::string ParticipantMetadataString(ParticipantMetadata obj, std::string sep) {
  const char *fmt = "%d";
  // const char *ssep = sep.c_str();

  const std::size_t size = std::snprintf(nullptr, 0, fmt, obj.m_numActiveCars);

  std::vector<char> buf(size + 1);  // note +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.m_numActiveCars);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));  // remove null terminator

  return str;
}

ParticipantMetadata ParseParticipantMetadata(std::vector<std::vector<unsigned char>> bytes) {
  ParticipantMetadata obj;
  std::memcpy(&obj.m_numActiveCars, &bytes.at(0).front(), sizeof obj.m_numActiveCars);
  return obj;
}

std::string PacketParticipantsDataCSVHeader(std::string sep) {
  std::vector<std::string> vec = {
      vpaste(PacketHeaderNames, sep),         //
      vpaste(ParticipantMetadataNames, sep),  //
      vpaste(ParticipantDataNames, sep)       //
  };
  return vpaste(vec, sep);
}

template <>
std::string packetDataString(PacketParticipantsData obj, std::uint8_t id, std::string sep, std::string compr,
                             std::string compr2) {
  std::vector<std::string> vec = {
      PacketHeaderString(obj.m_header),              //
      ParticipantMetadataString(obj.m_participant),  //
      ParticipantDataString(obj.m_participants[id])  //
  };
  return vpaste(vec, sep);
}

template <>
PacketParticipantsData parsePacketData<PacketParticipantsData>(std::vector<unsigned char> bytes) {
  PacketParticipantsData obj;
  std::uint16_t offset = 0;

  // parse header
  obj.m_header = ParsePacketHeader(parse_bytes_to_vec(PacketHeaderSizes, bytes, offset));
  offset += sizeof(PacketHeader);

  // parse extra player car data
  obj.m_participant = ParseParticipantMetadata(parse_bytes_to_vec(ParticipantMetadataSizes, bytes, offset));
  offset += sizeof(ParticipantMetadata);

  // loop over the 22 car data packets and parse them
  for (std::uint8_t i = 0; i < 22; i++) {
    obj.m_participants[i] = ParseParticipantData(parse_bytes_to_vec(ParticipantDataSizes, bytes, offset));
    offset += sizeof(ParticipantData);
  }

  return obj;
}
