#include "main.hpp"

int main() {
  // make all messages visible
  spdlog::set_level(spdlog::level::debug);
  spdlog::info(" === le F1 2022 UDP parser === ");

  spdlog::info(" track: {}", TRACK);

  // used to store metadata about each packet
  std::vector<PacketMap> Packets;

  // TODO: implement output file per-packet
  std::vector<std::string> raw_filenames;
  std::vector<std::string> output_filenames;
  std::vector<std::ofstream> output_files;

  // quick check to ensure output dirs exist
  if (createDir(LOG_DATA_PATH) == 0) spdlog::warn("log data output path does not exist; creating");
  if (createDir(RAW_DATA_PATH) == 0) spdlog::warn("raw data output path does not exist; creating");
  if (createDir(OUT_DATA_PATH) == 0) spdlog::warn("out data output path does not exist; creating");

  // extract all packet string names (to be used as filenames)
  for (auto const& p : packet_id_to_string) output_filenames.push_back(p.second);
  spdlog::info("extracted output filenames (packet names)");

  // collect all raw packet filenames
  for (auto const& dir_entry : std::filesystem::directory_iterator{std::filesystem::path{RAW_DATA_PATH}})
    raw_filenames.push_back(dir_entry.path());
  spdlog::info("extracted raw filenames (packet bytes as files)");

  // fetch metadata for each raw packet
  for (std::string file : raw_filenames) Packets.push_back(packet_map_populate(file));
  spdlog::info("extracted packet metadata");

  // open output file & write csv header (assuming PacketMotionData)
  // open output file for all packet types
  for (auto const& file : output_filenames) {
    auto i = &file - &output_filenames[0];
    std::string tmp_filename = OUT_DATA_PATH + output_filenames.at(i) + ".csv";
    output_files.emplace_back(std::ofstream{tmp_filename});
  }
  spdlog::debug("opened each output file (csv) for each packet type");

  output_files.at(MotionPacketID) << "m_carID," + PacketMotionDataCSVHeader() + "\n";
  output_files.at(SessionPacketID) << PacketSessionDataCSVHeader() + "\n";
  output_files.at(LapDataPacketID) << "m_carID," + PacketLapDataCSVHeader() + "\n";
  output_files.at(CarSetupsPacketID) << "m_carID," + PacketCarSetupDataCSVHeader() + "\n";
  output_files.at(CarTelemetryPacketID) << "m_carID," + PacketCarTelemetryDataCSVHeader() + "\n";

  spdlog::debug("wrote headers in for each file");

  for (PacketMap packet : Packets) {
    std::vector<unsigned char> filebytes = file_read(packet.file_name);

    if (packet.file_id == MotionPacketID) {
      if (DEBUG) spdlog::debug("parsing motion packet");
      PacketMotionData obj = ParsePacketMotionData(filebytes);

      for (std::uint8_t i = 0; i < 22; i++)
        output_files.at(MotionPacketID) << std::to_string(i) + "," + PacketMotionDataString(obj, i) + "\n";
    } else if (packet.file_id == SessionPacketID) {
      if (DEBUG) spdlog::debug("parsing session packet");
      PacketSessionData obj = ParsePacketSessionData(filebytes);

      output_files.at(SessionPacketID) << PacketSessionDataString(obj) + "\n";
    } else if (packet.file_id == LapDataPacketID) {
      if (DEBUG) spdlog::debug("parsing lap data packet");
      PacketLapData obj = ParsePacketLapData(filebytes);

      for (std::uint8_t i = 0; i < 22; i++)
        output_files.at(LapDataPacketID) << std::to_string(i) + "," + PacketLapDataString(obj, i) + "\n";
    } else if (packet.file_id == CarSetupsPacketID) {
      if (DEBUG) spdlog::debug("parsing car setups packet");
      PacketCarSetupData obj = ParsePacketCarSetupData(filebytes);

      for (std::uint8_t i = 0; i < 22; i++)
        output_files.at(CarSetupsPacketID) << std::to_string(i) + "," + PacketCarSetupDataString(obj, i) + "\n";
    } else if (packet.file_id == CarTelemetryPacketID) {
      if (DEBUG) spdlog::debug("parsing car telemetry packet");
      PacketCarTelemetryData obj = ParsePacketCarTelemetryData(filebytes);

      for (std::uint8_t i = 0; i < 22; i++)
        output_files.at(CarTelemetryPacketID) << std::to_string(i) + "," + PacketCarTelemetryDataString(obj, i) + "\n";
    }
  }
  spdlog::debug("parsed all packets");

  // close output files
  for (auto& file : output_files) file.close();
  spdlog::debug("closed output files");

  return 0;
};
