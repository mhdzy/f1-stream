#pragma once

#include <filesystem>
#include <fstream>
#include <vector>

extern int file_size(const char *filename);
extern std::vector<unsigned char> file_read(const char *filename);
