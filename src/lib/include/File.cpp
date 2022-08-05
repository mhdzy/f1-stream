#include "File.hpp"

std::vector<std::vector<unsigned char>> parse_bytes_to_vec(std::vector<std::size_t> sizes,
                                                           std::vector<unsigned char> filebytes, int offset = 0) {
  std::vector<std::vector<unsigned char>> pbytes;

  for (std::size_t size : sizes) {
    std::vector<unsigned char> bytes;
    std::vector<unsigned char> tbytes;

    tbytes = {filebytes.begin() + offset, filebytes.begin() + offset + size};
    std::copy(tbytes.begin(), tbytes.end() + 1, std::back_inserter(bytes));
    pbytes.push_back(bytes);

    offset = offset + size;
  }

  return pbytes;
}

int file_size(std::string filename) {
  std::streampos size;
  std::ifstream file(filename, std::ios::binary);

  file.seekg(0, std::ios::end);
  size = file.tellg();
  // file.seekg(0, std::ios::beg);
  file.close();

  return size;
}

std::vector<unsigned char> file_read(std::string filename) {
  std::streampos size = file_size(filename);
  std::ifstream file(filename, std::ios::binary);
  std::vector<unsigned char> file_data(size);

  file.read((char *)&file_data[0], size);
  file.close();

  return file_data;
}

std::string csvHeader(std::vector<std::string> fields, std::string sep) {
  std::string str;

  for (std::string s : fields) str += s + sep;

  // remove final 'sep' character from string
  if (!str.empty()) str.pop_back();

  return str;
}
