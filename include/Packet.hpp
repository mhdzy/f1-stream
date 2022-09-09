#pragma once

#include <cstdint>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <string>

template <class T>
extern std::string packetDataString(T obj, std::uint8_t id, std::string sep = ",", std::string compr = "/",
                                    std::string compr2 = ";");

template <class T>
extern T parsePacketData(std::vector<unsigned char> bytes);

template <class T>
extern T parseSubpacketData(std::vector<std::vector<unsigned char>> bytes);
