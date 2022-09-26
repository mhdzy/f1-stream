#pragma once

#include <cstdio>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <vector>

extern void print_hexb(std::vector<unsigned char> bytes, std::uint8_t width = 79, bool spaces = false);

extern std::string ftos(float f);
