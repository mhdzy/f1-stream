#pragma once

#include <cstdint>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <string>

#include "File.hpp"

template <class T>
extern std::vector<std::size_t> pSizes();

template <class T>
extern std::vector<std::string> pNames();

template <class T>
extern T parsePacketData(std::vector<unsigned char> bytes);

template <class T>
extern T parseSubpacketData(std::vector<std::vector<unsigned char>> bytes);

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
