#include "File.hpp"

std::vector<std::vector<unsigned char>> parse_bytes_to_pairs(std::vector<std::size_t> sizes,
                                                             std::vector<unsigned char> filebytes, int offset = 0) {
  std::vector<std::vector<unsigned char>> parsed_bytes;

  for (std::size_t size : sizes) {
    std::vector<unsigned char> bytes;
    std::vector<unsigned char> tmp_bytes;

    tmp_bytes = {filebytes.begin() + offset, filebytes.begin() + offset + size};

    std::copy(tmp_bytes.begin(), tmp_bytes.end() + 1, std::back_inserter(bytes));
    parsed_bytes.push_back(bytes);
    offset = offset + size;
  }

  return (parsed_bytes);
}

int file_size(std::string filename) {
  std::streampos size;
  std::ifstream file(filename, std::ios::binary);

  file.seekg(0, std::ios::end);
  size = file.tellg();
  // file.seekg(0, std::ios::beg);
  file.close();

  return (size);
};

std::vector<unsigned char> file_read(std::string filename) {
  std::streampos size;
  size = file_size(filename);

  std::ifstream file(filename, std::ios::binary);

  std::vector<unsigned char> file_data(size);
  file.read((char *)&file_data[0], size);

  file.close();

  return (file_data);
};
