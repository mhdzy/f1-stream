#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

extern std::vector<std::vector<unsigned char>> parse_bytes_to_pairs(std::vector<std::size_t> sizes,
                                                                    std::vector<unsigned char> filebytes, int offset);

extern int file_size(std::string filename);

extern std::vector<unsigned char> file_read(std::string filename);