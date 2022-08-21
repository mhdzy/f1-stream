#pragma once

#include <sys/stat.h>

#include <fstream>
#include <string>
#include <vector>

extern std::string csvHeader(std::vector<std::string> fields, std::string sep = ",");
extern int createDir(std::string directory);

extern std::vector<unsigned char> file_read(std::string filename);
extern int file_size(std::string filename);

extern std::vector<std::vector<unsigned char>> parse_bytes_to_vec(std::vector<std::size_t> sizes,
                                                                  std::vector<unsigned char> filebytes, int offset);
