#include "../include/main.hpp"

/**
 * @brief All packets holding core info in arrays can be printed using this function.
 * This is declared in main to avoid dealing with troubles passing ostream objects.

 * @param packetid An int representing the packetid (from enum PacketID).
 * @param obj An (auto) object, passed to the templated packetDataString().
 * @param debug A flag to enable extra output.
 */
void printPacket(auto obj, bool debug) {
  std::uint8_t packetid = getPacketID(sizeof(obj));
  for (std::uint8_t i = 0; i < packetLoopLimit(packetid); i++) {
    std::string str = packetDataString(obj, i);
    OUTPUT_FILES.at(packetid) << std::to_string(i) + "," + str + "\n";
    if (debug) printf("%s,%s\n", std::to_string(i).c_str(), str.c_str());
  }
}

/**
 * @brief Parses and prints a packet based on its ID (identified from the size of the packet bytes).
 *
 * @param bytes A vector of filebytes to parse, then print.
 * @param debug A boolean flag.
 */
void parseAndPrintPacket(std::vector<unsigned char> bytes, bool debug) {
  std::uint8_t packetid = getPacketID(bytes.size());

  if (DEBUG) spdlog::debug("packet id: {}", packetid);
  if (DEBUG) spdlog::debug("packet size: {}", bytes.size());

  switch (packetid) {
    case PacketID::Motion: {
      auto obj = parsePacketData<PacketMotionData>(bytes);
      if (getPacketPrint(packetid)) printPacket(obj, DEBUG);
      break;
    }
    case PacketID::Session: {
      auto obj = parsePacketData<PacketSessionData>(bytes);
      if (getPacketPrint(packetid)) printPacket(obj, DEBUG);
      break;
    }
    case PacketID::Lap: {
      auto obj = parsePacketData<PacketLapData>(bytes);
      if (getPacketPrint(packetid)) printPacket(obj, DEBUG);
      break;
    }
    case PacketID::Event: {
      auto obj = parsePacketData<PacketEventData>(bytes);
      if (getPacketPrint(packetid)) printPacket(obj, DEBUG);
      break;
    }
    case PacketID::Participants: {
      auto obj = parsePacketData<PacketParticipantsData>(bytes);
      if (getPacketPrint(packetid)) printPacket(obj, DEBUG);
      break;
    }
    case PacketID::CarSetups: {
      auto obj = parsePacketData<PacketCarSetupData>(bytes);
      if (getPacketPrint(packetid)) printPacket(obj, DEBUG);
      break;
    }
    case PacketID::CarTelemetry: {
      auto obj = parsePacketData<PacketCarTelemetryData>(bytes);
      if (getPacketPrint(packetid)) printPacket(obj, DEBUG);
      break;
    }
    case PacketID::CarStatus: {
      auto obj = parsePacketData<PacketCarStatusData>(bytes);
      if (getPacketPrint(packetid)) printPacket(obj, DEBUG);
      break;
    }
    case PacketID::FinalClassification: {
      auto obj = parsePacketData<PacketFinalClassificationData>(bytes);
      if (getPacketPrint(packetid)) printPacket(obj, DEBUG);
      break;
    }
    case PacketID::LobbyInfo: {
      auto obj = parsePacketData<PacketLobbyInfoData>(bytes);
      if (getPacketPrint(packetid)) printPacket(obj, DEBUG);
      break;
    }
    case PacketID::CarDamage: {
      auto obj = parsePacketData<PacketCarDamageData>(bytes);
      if (getPacketPrint(packetid)) printPacket(obj, DEBUG);
      break;
    }
    case PacketID::SessionHistory: {
      auto obj = parsePacketData<PacketSessionHistoryData>(bytes);
      if (getPacketPrint(packetid)) printPacket(obj, DEBUG);
      break;
    }
    default:
      break;
  }
}

/**
 * @brief Prints the header for a struct T with a prefix.
 *
 * @tparam T
 * @param packetid An integer representing the packetid (from the enum PacketID).
 * @param prefix A string to prefix the header string.
 */
template <class T>
void printHeader(std::string prefix) {
  OUTPUT_FILES.at(getPacketID(sizeof(T))) << prefix + packetDataHeader<T>() + "\n";
}

/**
 * @brief Wrapper function to write each header to its respective output file.
 *
 */
void printHeaders() {
  printHeader<PacketMotionData>("m_carID");
  printHeader<PacketSessionData>("m_nopID");
  printHeader<PacketLapData>("m_carID");
  printHeader<PacketEventData>("m_nopID");
  printHeader<PacketParticipantsData>("m_carID");
  printHeader<PacketCarSetupData>("m_carID");
  printHeader<PacketCarTelemetryData>("m_carID");
  printHeader<PacketCarStatusData>("m_carID");
  printHeader<PacketFinalClassificationData>("m_carID");
  printHeader<PacketLobbyInfoData>("m_carID");
  printHeader<PacketCarDamageData>("m_carID");
  printHeader<PacketSessionHistoryData>("m_lapID");
}

/**
 * @brief
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char** argv) {
  const char* USAGE = "Usage: ./main <track> [live|batch]\n";

  if (argc < 2) {
    std::perror(USAGE);
    return 0;
  }

  spdlog::set_level(spdlog::level::debug);  // make all logging visible

  // not const since this can shrink if in batch mode
  std::uint32_t MAXPACKETS = pow(2, 20);

  const std::string TRACK(argv[1]);
  const std::string MODE(argv[2]);

  const std::string DATA_PATH = "data/";
  const std::string TRACK_PATH = DATA_PATH + TRACK;
  const std::string LOG_DATA_PATH = TRACK_PATH + "/logs/";
  const std::string RAW_DATA_PATH = TRACK_PATH + "/raw/";     // source for 'batch'
  const std::string OUT_DATA_PATH = TRACK_PATH + "/parsed/";  // destination for all modes

  /* setup UDP socket vars */
  struct sockaddr_in myaddr;           /* our address */
  struct sockaddr_in remaddr;          /* remote address */
  socklen_t addrlen = sizeof(remaddr); /* length of addresses */
  std::uint32_t recvlen;               /* num bytes received */
  std::uint32_t fd;                    /* our socket */
  unsigned char buf[BUFSIZE];          /* receive buffer */

  // SETUP
  /*
    batch mode sets up 'raw' files to parse and restricts max packets
    live mode sets up output dirs
  */
  if (MODE == "batch") {
    // check that the batch folder source exists
    if (createDir(RAW_DATA_PATH) == 0) {
      std::perror("raw source data path does not exist\n");
      return 0;
    }

    // collect all raw packet filenames
    for (auto const& dir_entry : std::filesystem::directory_iterator{std::filesystem::path{RAW_DATA_PATH}})
      RAW_NAMES.push_back(dir_entry.path());
    spdlog::info("extracted raw filenames (packet bytes as files)");

    // restrict the main loop to exit after parsing all known data files
    MAXPACKETS = RAW_NAMES.size();
  } else if (MODE == "live") {
    // check that the live output folder exists
    if (createDir(TRACK_PATH) == 0) {
      spdlog::info("creating output dir at '{}'", TRACK_PATH);
      // createDir for all subdirs (needed)
      std::vector<std::string> out_paths = {OUT_DATA_PATH, RAW_DATA_PATH, LOG_DATA_PATH};
      std::for_each(out_paths.begin(), out_paths.end(), &createDir);
    }

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

  // CREATE OUTPUT DIRS
  // we can create if logs & output dirs don't exist
  if (createDir(LOG_DATA_PATH) == 0) spdlog::warn("log data output path does not exist; creating");
  if (createDir(OUT_DATA_PATH) == 0) spdlog::warn("out data output path does not exist; creating");

  // EXTRACT PACKET NAMES
  // extract all packet string names
  for (auto const& p : allPacketNames) OUTPUT_NAMES.push_back(p.second);
  if (DEBUG) spdlog::debug("extracted output filenames (packet names)");

  // OPEN OUTPUT FILES
  // open output file & write csv header for all packet types
  for (auto const& file : OUTPUT_NAMES) {
    auto i = &file - &OUTPUT_NAMES[0];
    std::string tmp_name = OUT_DATA_PATH + OUTPUT_NAMES.at(i) + ".csv";
    OUTPUT_FILES.emplace_back(std::ofstream{tmp_name});
  }
  if (DEBUG) spdlog::debug("opened each output file (csv) for each packet type");

  // WRITE HEADERS
  printHeaders();
  if (DEBUG) spdlog::debug("wrote headers in for each file");

  spdlog::info(" === F1 2022 UDP parser === ");
  spdlog::info(" track: {}", TRACK);
  spdlog::info(" mode: {}", MODE);
  spdlog::info(" maxp: {}", MAXPACKETS);
  if (MODE == "live") spdlog::info(" port {}", PORT);

  // main loop
  for (std::uint32_t i = 0; i < MAXPACKETS; i++) {
    std::vector<unsigned char> filebytes;

    // receive raw bytes & fit into vector
    if (MODE == "live") {
      recvlen = recvfrom(fd, buf, BUFSIZE, 0, (struct sockaddr*)&remaddr, &addrlen);
      if (DEBUG) spdlog::debug("(%d) %s %d %s\n", i, "received", recvlen, "bytes");

      if (recvlen > 0) buf[recvlen] = 0;
      filebytes = std::vector<unsigned char>(buf, buf + recvlen);

      // write bytes to file
      std::string raw_filename = RAW_DATA_PATH + "data" + std::to_string(i) + ".raw";
      std::ofstream raw_file(raw_filename);
      std::copy(filebytes.cbegin(), filebytes.cend(), std::ostream_iterator<char>(raw_file));
    } else if (MODE == "batch") {
      filebytes = file_read(RAW_NAMES[i]);
    }

    // parse packet & print it to its csv
    parseAndPrintPacket(filebytes, DEBUG);
  }

  spdlog::debug("parsed all packets");

  // close output files
  for (auto& file : OUTPUT_FILES) file.close();
  spdlog::debug("closed output files");

  return 0;
};
