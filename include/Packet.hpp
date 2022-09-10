#pragma once

#include <cstdint>
#include <cstdio>
#include <iostream>
#include <map>
#include <ostream>
#include <string>

#include "File.hpp"

enum PacketID : std::uint8_t {
  Motion = 0,               //
  Session = 1,              //
  Lap = 2,                  //
  Event = 3,                //
  Participants = 4,         //
  CarSetups = 5,            //
  CarTelemetry = 6,         //
  CarStatus = 7,            //
  FinalClassification = 8,  //
  LobbyInfo = 9,            //
  CarDamage = 10,           //
  SessionHistory = 11       //
};

extern const std::map<std::uint8_t, bool> allPacketPrints;

extern const std::map<std::uint16_t, std::uint8_t> allPacketSizes;

extern const std::map<std::uint8_t, std::string> allPacketNames;

/**
 * @brief Get a packet's print setting (on/off) from the id.
 *
 * @param id A packet ID.
 * @return true If the packet is to be printed.
 * @return false If the packet is not to be printed.
 */
extern bool getPacketPrint(std::uint8_t id);

/**
 * @brief Get a packet id from the packet size.
 *
 * @param size A packet size.
 * @return std::uint8_t A packet ID.
 */
extern std::uint8_t getPacketID(std::uint16_t size);

/**
 * @brief Get a packet name from the corresponding id.
 *
 * @param id A packet ID.
 * @return std::string A packet name.
 */
extern std::string getPacketName(std::uint8_t id);

/**
 * @brief Identify the numbers of loops needed to fully print a packet string.
 *
 * It's typical for Sessions and Events to be single row strings, SessionHistory includes 100 laps, else 22 loops for
 * each car on the grid.
 *
 * @param id
 * @return std::uint8_t
 */
extern std::uint8_t packetLoopLimit(std::uint8_t id);

template <class T>
extern std::vector<std::size_t> pSizes();

template <class T>
extern std::vector<std::string> pNames();

template <class T>
extern T parsePacketData(std::vector<unsigned char> bytes);

template <class T>
extern T parseSubpacketData(std::vector<std::vector<unsigned char>> bytes);

// just implement this here using other templated functions
template <class T>
extern T parseSubpacketDataT(std::vector<unsigned char> bytes, std::uint16_t offset) {
  return parseSubpacketData<T>(parseBytes(pSizes<T>(), bytes, offset));
};

template <class T>
extern std::string packetDataHeader(std::string sep = ",", std::string compr = "/");

template <class T>
extern std::string packetDataString(T obj, std::uint8_t id, std::string sep = ",", std::string compr = "/",
                                    std::string compr2 = ";");

template <class T>
extern std::string subpacketDataString(T obj, std::string sep = ",");
