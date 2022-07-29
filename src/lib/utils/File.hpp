#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

extern int file_size(std::string filename);
extern std::vector<unsigned char> file_read(std::string filename);
