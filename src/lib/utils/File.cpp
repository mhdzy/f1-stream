#include "File.hpp"

int file_size(const char *filename)
{
  std::streampos size;
  std::ifstream file(filename, std::ios::binary);

  file.seekg(0, std::ios::end);
  size = file.tellg();
  // file.seekg(0, std::ios::beg);
  file.close();

  return (size);
};

std::vector<unsigned char> file_read(const char *filename)
{
  std::streampos size;
  size = file_size(filename);

  std::ifstream file(filename, std::ios::binary);

  std::vector<unsigned char> file_data(size);
  file.read((char *)&file_data[0], size);

  file.close();

  return (file_data);
};
