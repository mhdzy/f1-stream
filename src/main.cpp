#include "main.hpp"

#define PORT 20777
#define BUFSIZE 4096

const bool DEBUG = true;

const std::vector<std::uint8_t> IMPLEMENTED_PACKET_IDS = {
    0,  // motion data
    1,  // session data
    2,  // lap data
    3,  // event data
    4,  // participants data
    5,  // (car) setup
    6,  // (car) telemetry
    7,  // (car) status
    10  // (car) damage
};

/**
 * @brief
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char** argv) {
  const char* USAGE = "Usage: ./f1stream <track> [live|batch]\n";

  if (argc < 2) {
    std::perror(USAGE);
    return 0;
  }

  spdlog::set_level(spdlog::level::debug);  // make all logging visible

  const std::uint32_t MAXPACKETS = pow(2, 20);

  const std::string TRACK(argv[1]);
  const std::string MODE(argv[2]);

  const std::string DATA_PATH = "data/";
  const std::string LOG_DATA_PATH = DATA_PATH + TRACK + "/logs/";
  const std::string RAW_DATA_PATH = DATA_PATH + TRACK + "/raw/";     // source for 'batch'
  const std::string OUT_DATA_PATH = DATA_PATH + TRACK + "/parsed/";  // destination for all modes

  std::vector<PacketMap> Packets;             // stores metadata for each raw file (batch mode)
  std::vector<std::string> raw_filenames;     // raw input files (for batch mode)
  std::vector<std::string> output_filenames;  // output string names
  std::vector<std::ofstream> output_files;    // output streams

  /* setup UDP socket vars */
  struct sockaddr_in myaddr;           /* our address */
  struct sockaddr_in remaddr;          /* remote address */
  socklen_t addrlen = sizeof(remaddr); /* length of addresses */
  std::uint32_t recvlen;               /* num bytes received */
  std::uint32_t fd;                    /* our socket */
  unsigned char buf[BUFSIZE];          /* receive buffer */

  if (MODE == "batch") {
    // check that the batch folder source exists
    if (createDir(RAW_DATA_PATH) == 0) {
      std::perror("raw source data path does not exist\n");
      return 0;
    }

    // collect all raw packet filenames
    for (auto const& dir_entry : std::filesystem::directory_iterator{std::filesystem::path{RAW_DATA_PATH}})
      raw_filenames.push_back(dir_entry.path());
    spdlog::info("extracted raw filenames (packet bytes as files)");

    // fetch metadata for each raw packet
    for (std::string file : raw_filenames) Packets.push_back(packet_map_populate(file));
    spdlog::info("extracted packet metadata");
  } else if (MODE == "live") {
    /* create a UDP socket */
    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
      std::perror("cannot create socket\n");
      return 0;
    }

    /* bind the socket to any valid IP address and a specific port */
    memset((char*)&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddr.sin_port = htons(PORT);

    if (bind(fd, (struct sockaddr*)&myaddr, sizeof(myaddr)) < 0) {
      std::perror("bind failed\n");
      return 0;
    }
  } else {
    std::perror(USAGE);
    return 0;
  }

  // we can create if logs & output dirs don't exist
  if (createDir(LOG_DATA_PATH) == 0) spdlog::warn("log data output path does not exist; creating");
  if (createDir(OUT_DATA_PATH) == 0) spdlog::warn("out data output path does not exist; creating");

  // extract all packet string names
  for (auto const& p : packet_id_to_string) output_filenames.push_back(p.second);
  spdlog::info("extracted output filenames (packet names)");

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
  output_files.at(EventPacketID) << PacketEventDataCSVHeader() + "\n";
  output_files.at(ParticipantsPacketID) << "m_carID," + PacketParticipantsDataCSVHeader() + "\n";
  output_files.at(CarSetupsPacketID) << "m_carID," + PacketCarSetupDataCSVHeader() + "\n";
  output_files.at(CarTelemetryPacketID) << "m_carID," + PacketCarTelemetryDataCSVHeader() + "\n";
  output_files.at(CarStatusPacketID) << "m_carID," + PacketCarStatusDataCSVHeader() + "\n";
  output_files.at(CarDamagePacketID) << "m_carID," + PacketCarDamageDataCSVHeader() + "\n";
  spdlog::debug("wrote headers in for each file");

  spdlog::info(" === F1 2022 UDP parser === ");
  spdlog::info(" track: {}", TRACK);
  spdlog::info(" mode: {}", MODE);
  if (MODE == "live") spdlog::info(" port {}", PORT);

  for (std::uint16_t i = 0; i < MAXPACKETS; i++) {
    PacketMap packet;
    std::vector<unsigned char> filebytes;

    if (MODE == "live") {
      recvlen = recvfrom(fd, buf, BUFSIZE, 0, (struct sockaddr*)&remaddr, &addrlen);

      if (DEBUG) spdlog::debug("(%d) %s %d %s\n", i, "received", recvlen, "bytes");
      if (recvlen > 0) buf[recvlen] = 0;

      packet = parse_raw_packet(recvlen);
      filebytes = std::vector<unsigned char>(buf, buf + recvlen);
    } else if (MODE == "batch") {
      packet = Packets[i];
      filebytes = file_read(packet.file_name);
    }

    if (DEBUG) {
      spdlog::debug("packet id : {}", packet.file_id);
      spdlog::debug("packet name: {}", packet.file_packet_name);
      spdlog::debug("packet size: {}", packet.file_size);
    }

    if (packet.file_id == MotionPacketID) {
      // MOTION

      if (DEBUG) spdlog::debug("parsing motion packet");
      PacketMotionData obj = ParsePacketMotionData(filebytes);
      for (std::uint8_t i = 0; i < 22; i++)
        output_files.at(MotionPacketID) << std::to_string(i) + "," + PacketMotionDataString(obj, i) + "\n";

    } else if (packet.file_id == SessionPacketID) {
      // SESSION~

      if (DEBUG) spdlog::debug("parsing session packet");
      PacketSessionData obj = ParsePacketSessionData(filebytes);
      output_files.at(SessionPacketID) << PacketSessionDataString(obj) + "\n";

    } else if (packet.file_id == LapDataPacketID) {
      // LAP DATA

      if (DEBUG) spdlog::debug("parsing lap data packet");
      PacketLapData obj = ParsePacketLapData(filebytes);
      for (std::uint8_t i = 0; i < 22; i++)
        output_files.at(LapDataPacketID) << std::to_string(i) + "," + PacketLapDataString(obj, i) + "\n";

    } else if (packet.file_id == EventPacketID) {
      // EVENT

      if (DEBUG) spdlog::debug("parsing event data packet");
      PacketEventData obj = ParsePacketEventData(filebytes);
      output_files.at(EventPacketID) << PacketEventDataString(obj) + "\n";

    } else if (packet.file_id == ParticipantsPacketID) {
      // PARTICIPANTS

      if (DEBUG) spdlog::debug("parsing participants packet");
      PacketParticipantsData obj = ParsePacketParticipantsData(filebytes);
      for (std::uint8_t i = 0; i < 22; i++)
        output_files.at(ParticipantsPacketID) << std::to_string(i) + "," + PacketParticipantsDataString(obj, i) + "\n";

    } else if (packet.file_id == CarSetupsPacketID) {
      // SETUPS

      if (DEBUG) spdlog::debug("parsing car setups packet");
      PacketCarSetupData obj = ParsePacketCarSetupData(filebytes);
      for (std::uint8_t i = 0; i < 22; i++)
        output_files.at(CarSetupsPacketID) << std::to_string(i) + "," + PacketCarSetupDataString(obj, i) + "\n";

    } else if (packet.file_id == CarTelemetryPacketID) {
      // TELEMETRY

      if (DEBUG) spdlog::debug("parsing car telemetry packet");
      PacketCarTelemetryData obj = ParsePacketCarTelemetryData(filebytes);
      for (std::uint8_t i = 0; i < 22; i++)
        output_files.at(CarTelemetryPacketID) << std::to_string(i) + "," + PacketCarTelemetryDataString(obj, i) + "\n";

    } else if (packet.file_id == CarStatusPacketID) {
      // STATUS

      if (DEBUG) spdlog::debug("parsing car status packet");
      PacketCarStatusData obj = ParsePacketCarStatusData(filebytes);
      for (std::uint8_t i = 0; i < 22; i++)
        output_files.at(CarStatusPacketID) << std::to_string(i) + "," + PacketCarStatusDataString(obj, i) + "\n";
    } else if (packet.file_id == CarDamagePacketID) {
      // DAMAGE

      if (DEBUG) spdlog::debug("parsing car damage packet");
      PacketCarDamageData obj = ParsePacketCarDamageData(filebytes);
      for (std::uint8_t i = 0; i < 22; i++)
        output_files.at(CarDamagePacketID) << std::to_string(i) + "," + PacketCarDamageDataString(obj, i) + "\n";
    }
    if (DEBUG) spdlog::debug("\n");
  }
  spdlog::debug("parsed all packets");

  // close output files
  for (auto& file : output_files) file.close();
  spdlog::debug("closed output files");

  return 0;
};
