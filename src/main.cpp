#include "main.hpp"

int main() {
  std::vector<std::string> filenames;
  std::vector<PacketMap> Packets;
  std::vector<PacketMap> MotionPackets;
  std::string track = "spa";

  // collect all filenames
  const std::filesystem::path path{"data/" + track + "-single-lap/"};
  for (auto const &dir_entry : std::filesystem::directory_iterator{path}) filenames.push_back(dir_entry.path());

  // fetch metadata for each filetype
  for (std::string file : filenames) {
    PacketMap pmap = packet_map_populate(file);
    Packets.push_back(pmap);

    if (pmap.file_id == 0) MotionPackets.push_back(pmap);
  }

  std::string output_path = "data/" + track + "-lap-data-parsed.csv";
  std::ofstream output_file;
  std::ofstream output_test;

  // open output file & write csv header
  output_file.open(output_path);
  output_file << PacketHeaderCSVHeader() + ",m_carID," + CarMotionDataCSVHeader() + "," + PacketMotionDataCSVHeader() +
                     "\n";

  output_test.open("data/debug.csv");
  output_test << "x,y\n";

  // parse & write each motion packet
  for (PacketMap packet : MotionPackets) {
    PacketMotionData pmd;

    // parse a file
    std::vector<unsigned char> filebytes = file_read(packet.file_name);

    // parse header
    std::vector<std::vector<unsigned char>> packet_header_bytes = parse_bytes_to_pairs(PacketHeaderPairs, filebytes, 0);
    pmd.m_header = ParsePacketHeader(packet_header_bytes);

    // parse footer?
    std::vector<std::vector<unsigned char>> packet_footer_bytes =
        parse_bytes_to_pairs(PacketMotionDataPairs, filebytes, sizeof(PacketHeader) + (sizeof(CarMotionData) * 22));
    // parse motion data writes directly to object; requires passing by reference
    ParsePacketMotionData(pmd, packet_footer_bytes);

    // loop over the 22 car data packets
    for (int i = 0; i < 22; i++) {
      std::vector<std::vector<unsigned char>> car_motion_data_bytes =
          parse_bytes_to_pairs(CarMotionDataPairs, filebytes, sizeof(PacketHeader) + (sizeof(CarMotionData) * i));
      pmd.m_carMotionData.at(i) = ParseCarMotionData(car_motion_data_bytes);

      // for each car data packet, write 1 entry in file
      output_file << PacketHeaderString(pmd.m_header, ",") + "," + std::to_string(i) + "," +
                         CarMotionDataString(pmd.m_carMotionData.at(i), ",") + "," + PacketMotionDataString(pmd, ",") +
                         "\n";
    }
  }

  output_file.close();
  output_test.close();

  return 0;
};
