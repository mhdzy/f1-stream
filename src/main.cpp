#include "main.hpp"

typedef unsigned char byte;

int get_file_size(const char *filename)
{
  // open file
  std::streampos file_size;
  std::ifstream file(filename, std::ios::binary);

  // get its size
  file.seekg(0, std::ios::end);
  file_size = file.tellg();
  file.seekg(0, std::ios::beg);

  // close file
  file.close();

  return (file_size);
}

std::vector<byte> file_read(const char *filename)
{
  // get its size
  std::streampos file_size;
  file_size = get_file_size(filename);

  // open file
  std::ifstream file(filename, std::ios::binary);

  // read the data
  std::vector<byte> file_data(file_size);
  file.read((char *)&file_data[0], file_size);

  // close the buffer (is this necessary?)
  file.close();

  return (file_data);
}

int main()
{
  std::vector<std::string> filenames;

  const std::filesystem::path path{"data/"};
  for (auto const &dir_entry : std::filesystem::directory_iterator{path})
    filenames.push_back(dir_entry.path());

  struct PacketMap
  {
    char *file_name;
    char *file_packet_name;
    int file_size;
    int file_id;
  };

  std::vector<PacketMap> Packets;
  std::vector<PacketMap> MotionPackets;

  for (int i = 0; i < filenames.size(); i++)
  {
    PacketMap PM;
    PM.file_name = const_cast<char *>(filenames[i].c_str());
    PM.file_size = (int)get_file_size(const_cast<char *>(filenames[i].c_str()));
    PM.file_id = packet_size_to_id.find(PM.file_size)->second;
    PM.file_packet_name = const_cast<char *>(packet_id_to_string.find(PM.file_id)->second.c_str());
    Packets.push_back(PM);
    if (PM.file_id == 0)
      MotionPackets.push_back(PM);
  }

  /*
  for (int i = 0; i < MotionPackets.size(); i++)
  {
    PacketMap pm = Packets[i];
    printf(
        "=== %s ===\n%d bytes\nid: %d (%s)\n---\n",
        pm.file_name,
        pm.file_size,
        pm.file_id,
        pm.file_packet_name);
  }
  */

  std::vector<byte> vals = file_read(MotionPackets[MotionPackets.size() - 1].file_name);

  PacketHeader PHD;
  for (int i = 0; i < sizeof(PHD); i++)
  {
    printf("byte %4d | %2x\n", i, vals.at(i));
  }
  printf("______________\n");

  PacketMotionData PMD;
  for (int i = 0; i < sizeof(PMD); i++)
  {
    printf("byte %4d | %2x\n", i, vals.at(i));
  }

  printf("total bytes: %lu\n", vals.size());

  /*
  printf("%lu\n", sizeof(std::uint8_t));
  printf("%lu\n", sizeof(std::int8_t));
  printf("%lu\n", sizeof(std::uint16_t));
  printf("%lu\n", sizeof(std::int16_t));
  printf("%lu\n", sizeof(std::uint32_t));
  printf("%lu\n", sizeof(float));
  printf("%lu\n", sizeof(std::uint64_t));
  */

  return (0);
}
