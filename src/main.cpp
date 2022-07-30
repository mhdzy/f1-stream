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

  printf("motion packets total: %lu\n", MotionPackets.size());
  // print metadata for each packet
  /*
  for (PacketMap pmap : Packets) {
      printf("%17s :: %4d bytes :: id %2d (%s)\n", pmap.file_name.c_str(), pmap.file_size, pmap.file_id,
  pmap.file_packet_name.c_str());
  }
  printf("\n");
  */

  std::ofstream output_file;
  output_file.open("data/" + track + "-lap-data-parsed.csv");
  output_file
      << "m_packetFormat,m_gameMajorVersion,m_gameMinorVersion,m_packetVersion,m_packetId,m_sessionUID,m_sessionTime,m_"
         "frameIdentifier,m_playerCarIndex,m_secondaryPlayerCarIndex,";
  output_file
      << "m_carID,m_worldPositionX,m_worldPositionY,m_worldPositionZ,m_worldVelocityX,m_worldVelocityY,m_"
         "worldVelocityZ,m_"
         "worldForwardDirX,m_worldForwardDirY,m_worldForwardDirZ,m_worldRightDirX,m_worldRightDirY,m_worldRightDirZ,m_"
         "gForceLateral,m_gForceLongitudinal,m_gForceVertical,m_yaw,m_pitch,m_roll\n ";
  for (PacketMap packet : MotionPackets) {
    // parse a file
    std::vector<unsigned char> filebytes = file_read(packet.file_name);

    /*
    // print all parsed file bytes
    for (int i = 0; i < sizeof(PacketHeader); i++)
    {
      printf("%2x ", filebytes.at(i));
      if (i % 6 == 5)
        printf("\n");
    }
    printf("\n");

    // print remainder of parsed bytes
    for (int i = sizeof(PacketHeader); i < sizeof(PacketHeader) +
    sizeof(CarMotionData); i++)
    {
      printf("%2x ", filebytes.at(i));
      if (i % 6 == 5)
        printf("\n");
    }
    printf("\n");
    */

    for (int i = 1; i <= 22; i++) {
      std::vector<std::vector<unsigned char>> packet_header_bytes =
          parse_bytes_to_pairs(PacketHeaderPairs, filebytes, 0);
      PacketHeader packet_header = ParsePacketHeader(packet_header_bytes);
      // PrintPacketHeader(packet_header);
      // printf("\n");
      output_file << packet_header.m_packetFormat << "," << static_cast<std::uint32_t>(packet_header.m_gameMajorVersion)
                  << "," << static_cast<std::uint32_t>(packet_header.m_gameMinorVersion) << ","
                  << static_cast<std::uint32_t>(packet_header.m_packetVersion) << ","
                  << static_cast<std::uint32_t>(packet_header.m_packetId) << "," << packet_header.m_sessionUID << ","
                  << packet_header.m_sessionTime << "," << packet_header.m_frameIdentifier << ","
                  << static_cast<std::uint32_t>(packet_header.m_playerCarIndex) << ","
                  << static_cast<std::uint32_t>(packet_header.m_secondaryPlayerCarIndex) << ",";

      std::vector<std::vector<unsigned char>> car_motion_data_bytes =
          parse_bytes_to_pairs(CarMotionDataPairs, filebytes, sizeof(PacketHeader) * i);
      CarMotionData car_motion_data = ParseCarMotionData(car_motion_data_bytes);
      // PrintCarMotionData(car_motion_data);
      // printf("\n");

      output_file << i << "," << car_motion_data.m_worldPositionX << "," << car_motion_data.m_worldPositionY << ","
                  << car_motion_data.m_worldPositionZ << "," << car_motion_data.m_worldVelocityX << ","
                  << car_motion_data.m_worldVelocityY << "," << car_motion_data.m_worldVelocityZ << ","
                  << car_motion_data.m_worldForwardDirX << "," << car_motion_data.m_worldForwardDirY << ","
                  << car_motion_data.m_worldForwardDirZ << "," << car_motion_data.m_worldRightDirX << ","
                  << car_motion_data.m_worldRightDirY << "," << car_motion_data.m_worldRightDirZ << ","
                  << car_motion_data.m_gForceLateral << "," << car_motion_data.m_gForceLongitudinal << ","
                  << car_motion_data.m_gForceVertical << "," << car_motion_data.m_yaw << "," << car_motion_data.m_pitch
                  << "," << car_motion_data.m_roll << "\n";
    }
  }
  output_file.close();

  return (0);
};
