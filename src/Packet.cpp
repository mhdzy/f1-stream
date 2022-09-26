#include "../include/Packet.hpp"

const std::map<std::uint8_t, bool> allPacketPrints = {
    {PacketID::Motion, true},                // Motion
    {PacketID::Session, false},              // Session
    {PacketID::Lap, false},                  // Lap
    {PacketID::Event, false},                // Event
    {PacketID::Participants, true},          // Participants
    {PacketID::CarSetups, false},            // CarSetups
    {PacketID::CarTelemetry, true},          // CarTelemetry
    {PacketID::CarStatus, false},            // CarStatus
    {PacketID::FinalClassification, false},  // FinalClassification
    {PacketID::LobbyInfo, false},            // LobbyInfo
    {PacketID::CarDamage, false},            // CarDamage
    {PacketID::SessionHistory, false},       // SessionHistory
};

const std::map<std::uint16_t, std::uint8_t> allPacketSizes = {
    {1464, PacketID::Motion},               //
    {632, PacketID::Session},               //
    {972, PacketID::Lap},                   //
    {40, PacketID::Event},                  //
    {87, PacketID::Event},                  // this is here because the Event union struct is larger than in the og spec
    {1257, PacketID::Participants},         //
    {1102, PacketID::CarSetups},            //
    {1347, PacketID::CarTelemetry},         //
    {1058, PacketID::CarStatus},            //
    {1015, PacketID::FinalClassification},  //
    {1191, PacketID::LobbyInfo},            //
    {948, PacketID::CarDamage},             //
    {1155, PacketID::SessionHistory}        //
};

const std::map<std::uint8_t, std::string> allPacketNames = {
    {PacketID::Motion, "Motion"},                            //
    {PacketID::Session, "Session"},                          //
    {PacketID::Lap, "Lap"},                                  //
    {PacketID::Event, "Event"},                              //
    {PacketID::Participants, "Participants"},                //
    {PacketID::CarSetups, "CarSetups"},                      //
    {PacketID::CarTelemetry, "CarTelemetry"},                //
    {PacketID::CarStatus, "CarStatus"},                      //
    {PacketID::FinalClassification, "FinalClassification"},  //
    {PacketID::LobbyInfo, "LobbyInfo"},                      //
    {PacketID::CarDamage, "CarDamage"},                      //
    {PacketID::SessionHistory, "SessionHistory"}             //
};

extern bool getPacketPrint(std::uint8_t id) { return allPacketPrints.find(id)->second; }

std::uint8_t getPacketID(std::uint16_t size) { return allPacketSizes.find(size)->second; }

std::string getPacketName(std::uint8_t id) { return allPacketNames.find(id)->second; }

std::uint8_t packetLoopLimit(std::uint8_t id) {
  switch (id) {
    case PacketID::Session:
    case PacketID::Event:
      return 0;
    case PacketID::SessionHistory:
      return 100;
    default:
      return 22;
  }
}
