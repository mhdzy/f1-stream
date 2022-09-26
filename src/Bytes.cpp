#include "../include/Bytes.hpp"

void print_hexb(std::vector<unsigned char> bytes, std::uint8_t width, bool spaces) {
  for (std::size_t i = 0; i < bytes.size(); i++) {
    std::printf("%02x", bytes[i]);
    if (i % 1 == 0) std::printf(" ");
    if (i % width == (width - 1)) std::printf("\n");
  }
  std::printf("\n");
}

std::string ftos(float f) {
  std::stringstream stream;
  stream << std::fixed << std::setprecision(8) << f;
  return stream.str();
}
