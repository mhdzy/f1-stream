#include "main.hpp"

int main() {
  std::string track = "brazil";
  std::string output_path = "data/" + track + "-session-data-parsed.csv";
  std::ofstream output_file;

  std::vector<std::string> filenames;
  std::vector<PacketMap> Packets;

  // collect all filenames
  const std::filesystem::path path{"data/" + track + "-single-lap/"};
  for (auto const &dir_entry : std::filesystem::directory_iterator{path}) filenames.push_back(dir_entry.path());

  // fetch metadata for each filetype
  for (std::string file : filenames) Packets.push_back(packet_map_populate(file));

  // open output file & write csv header (assuming PacketMotionData)
  output_file.open(output_path);
  // output_file << "m_carID," + PacketMotionDataCSVHeader() + "\n";
  output_file << PacketSessionDataCSVHeader() + "\n";

  for (PacketMap packet : Packets) {
    std::vector<unsigned char> filebytes = file_read(packet.file_name);

    if (packet.file_id == 0) {
      PacketMotionData pmd = ParsePacketMotionData(filebytes);

      // need to print 1 row per 'carID' (i)
      for (int i = 0; i < 22; i++) {
        // output_file << std::to_string(i) + "," + PacketMotionDataString(pmd, i) + "\n";
      }
    } else if (packet.file_id == 1) {
      for (std::size_t i = 0; i < filebytes.size(); i++) {
        printf("%2x", filebytes.at(i));
        if (i % 1 == 0) printf(" ");
        if (i % 6 == 5) printf("\n");
      }
      printf("\n\n");
      PacketSessionData psd = ParsePacketSessionData(filebytes);

      output_file << PacketSessionDataString(psd) + "\n";
    }
  }
  output_file.close();

  return 0;
};
