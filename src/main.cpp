#include "main.hpp"

int main() {
  std::vector<std::string> filenames;
  std::vector<PacketMap> Packets;
  std::vector<PacketMap> MotionPackets;
  std::string track = "brazil";

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

  // open output file & write csv header
  output_file.open(output_path);
  output_file << "m_carID," + PacketMotionDataCSVHeader() + "\n";

  // parse & write each motion packet
  for (PacketMap packet : MotionPackets) {
    // parse a file
    std::vector<unsigned char> filebytes = file_read(packet.file_name);

    PacketMotionData pmd = ParsePacketMotionData(filebytes);

    // need to extract 
    for (int i = 0; i < 22; i++) {
      output_file << std::to_string(i) + "," + PacketMotionDataString(pmd, i) + "\n";
    }
  }

output_file.close();

return 0;
};
