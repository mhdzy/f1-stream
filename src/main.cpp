#include "main.hpp"

int main()
{
  std::vector<std::string> filenames;
  std::vector<PacketMap> Packets;
  std::vector<PacketMap> MotionPackets;

  // collect all filenames
  const std::filesystem::path path{"data/"};
  for (auto const &dir_entry : std::filesystem::directory_iterator{path})
    filenames.push_back(dir_entry.path());

  // fetch metadata for each filetype
  for (std::string file : filenames)
  {
    PacketMap pmap = packet_map_populate(file);
    Packets.push_back(pmap);

    if (pmap.file_id == 0)
      MotionPackets.push_back(pmap);
  }

  // print metadata for each packet
  printf("motion packets total: %lu\n", MotionPackets.size());
  for (PacketMap pmap : Packets)
  {
    printf(
        "=== %s ===\n%d bytes\nid: %d (%s)\n---\n",
        pmap.file_name, pmap.file_size, pmap.file_id, pmap.file_packet_name);
  }

  // parse a file
  std::vector<unsigned char> filebytes = file_read(MotionPackets[MotionPackets.size() - 1].file_name);

  // print all parsed file bytes
  for (int i = 0; i < sizeof(PacketHeader); i++)
  {
    printf("%2x ", filebytes.at(i));
    if (i % 6 == 5)
      printf("\n");
  }
  printf("\n");

  std::vector<std::vector<unsigned char>> allbytes;
  int it = 0;
  for (std::pair<int, std::string> p : PacketHeaderPairs)
  {
    // print packet metadata info (each item size)
    printf("k_: %d, v_: %s\n", p.first, p.second.c_str());

    // extract each element into its own vector item
    std::vector<unsigned char> tmp_bytes = {
        filebytes.begin() + it,
        filebytes.begin() + it + p.first};
    std::vector<unsigned char> bytes;
    std::copy(tmp_bytes.begin(), tmp_bytes.end() + 1, std::back_inserter(bytes));
    allbytes.push_back(bytes);
    it = it + p.first;
  }

  PacketHeader test_header = ParsePacketHeader(allbytes);
  PrintPacketHeader(test_header);

  // test to see how little vs big endian encoding prints out
  unsigned char bytes[4] = {0xc3, 0xd9, 0x98, 0x42};
  float value;
  std::memcpy(&value, bytes, sizeof(float));

  printf("\nfloat is %2f\n", value);

  return (0);
};
