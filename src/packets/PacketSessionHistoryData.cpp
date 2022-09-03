#include "PacketSessionHistoryData.hpp"

std::vector<std::size_t> LapMetaDataSizes = {
    sizeof(((LapMetaData *)0)->m_carIdx),             // Index of the car this lap data relates to
    sizeof(((LapMetaData *)0)->m_numLaps),            // Num laps in the data (including current partial lap)
    sizeof(((LapMetaData *)0)->m_numTyreStints),      // Number of tyre stints in the data
    sizeof(((LapMetaData *)0)->m_bestLapTimeLapNum),  // Lap the best lap time was achieved on
    sizeof(((LapMetaData *)0)->m_bestSector1LapNum),  // Lap the best Sector 1 time was achieved on
    sizeof(((LapMetaData *)0)->m_bestSector2LapNum),  // Lap the best Sector 2 time was achieved on
    sizeof(((LapMetaData *)0)->m_bestSector3LapNum)   // Lap the best Sector 3 time was achieved on
};

std::vector<std::string> LapMetaDataNames = {
    "m_carIdx",             // Index of the car this lap data relates to
    "m_numLaps",            // Num laps in the data (including current partial lap)
    "m_numTyreStints",      // Number of tyre stints in the data
    "m_bestLapTimeLapNum",  // Lap the best lap time was achieved on
    "m_bestSector1LapNum",  // Lap the best Sector 1 time was achieved on
    "m_bestSector2LapNum",  // Lap the best Sector 2 time was achieved on
    "m_bestSector3LapNum"   // Lap the best Sector 3 time was achieved on
};

std::vector<std::size_t> LapHistoryDataSizes = {
    sizeof(((LapHistoryData *)0)->m_lapTimeInMS),      // Lap time in milliseconds
    sizeof(((LapHistoryData *)0)->m_sector1TimeInMS),  // Sector 1 time in milliseconds
    sizeof(((LapHistoryData *)0)->m_sector2TimeInMS),  // Sector 2 time in milliseconds
    sizeof(((LapHistoryData *)0)->m_sector3TimeInMS),  // Sector 3 time in milliseconds
    sizeof(((LapHistoryData *)0)->m_lapValidBitFlags)  // 0x01 bit set-lap valid,      0x02 bit set-sector 1 valid
                                                       // 0x04 bit set-sector 2 valid, 0x08 bit set-sector 3 valid
};

std::vector<std::string> LapHistoryDataNames = {
    "m_lapTimeInMS",      // Lap time in milliseconds
    "m_sector1TimeInMS",  // Sector 1 time in milliseconds
    "m_sector2TimeInMS",  // Sector 2 time in milliseconds
    "m_sector3TimeInMS",  // Sector 3 time in milliseconds
    "m_lapValidBitFlags"  // 0x01 bit set-lap valid,      0x02 bit set-sector 1 valid
                          // 0x04 bit set-sector 2 valid, 0x08 bit set-sector 3 valid
};

std::vector<std::size_t> TyreStintHistoryDataSizes = {
    sizeof(((TyreStintHistoryData *)0)->m_endLap),              // Lap the tyre usage ends on (255 of current tyre)
    sizeof(((TyreStintHistoryData *)0)->m_tyreActualCompound),  // Actual tyres used by this driver
    sizeof(((TyreStintHistoryData *)0)->m_tyreVisualCompound)   // Visual tyres used by this driver
};

std::vector<std::string> TyreStintHistoryDataNames = {
    "m_endLap",              // Lap the tyre usage ends on (255 of current tyre)
    "m_tyreActualCompound",  // Actual tyres used by this driver
    "m_tyreVisualCompound"   // Visual tyres used by this driver
};

std::string LapMetaDataString(LapMetaData obj, std::string sep) {
  const char *fmt = "%d%s%d%s%d%s%d%s%d%s%d%s%d";
  const char *ssep = sep.c_str();

  const std::size_t size = std::snprintf(nullptr, 0, fmt, obj.m_carIdx, ssep, obj.m_numLaps, ssep, obj.m_numTyreStints,
                                         ssep, obj.m_bestLapTimeLapNum, ssep, obj.m_bestSector1LapNum, ssep,
                                         obj.m_bestSector2LapNum, ssep, obj.m_bestSector3LapNum);

  std::vector<char> buf(size + 1);  // note +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.m_carIdx, ssep, obj.m_numLaps, ssep, obj.m_numTyreStints, ssep,
                obj.m_bestLapTimeLapNum, ssep, obj.m_bestSector1LapNum, ssep, obj.m_bestSector2LapNum, ssep,
                obj.m_bestSector3LapNum);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));  // remove null terminator

  return str;
}

LapMetaData ParseLapMetaData(std::vector<std::vector<unsigned char>> bytes) {
  LapMetaData obj;
  std::memcpy(&obj.m_carIdx, &bytes.at(0).front(), sizeof obj.m_carIdx);
  std::memcpy(&obj.m_numLaps, &bytes.at(1).front(), sizeof obj.m_numLaps);
  std::memcpy(&obj.m_numTyreStints, &bytes.at(2).front(), sizeof obj.m_numTyreStints);
  std::memcpy(&obj.m_bestLapTimeLapNum, &bytes.at(3).front(), sizeof obj.m_bestLapTimeLapNum);
  std::memcpy(&obj.m_bestSector1LapNum, &bytes.at(4).front(), sizeof obj.m_bestSector1LapNum);
  std::memcpy(&obj.m_bestSector2LapNum, &bytes.at(5).front(), sizeof obj.m_bestSector2LapNum);
  std::memcpy(&obj.m_bestSector3LapNum, &bytes.at(6).front(), sizeof obj.m_bestSector3LapNum);
  return obj;
}

std::string LapHistoryDataString(LapHistoryData obj, std::string sep) {
  const char *fmt = "%d%s%d%s%d%s%d%s%d";
  const char *ssep = sep.c_str();

  const std::size_t size =
      std::snprintf(nullptr, 0, fmt, obj.m_lapTimeInMS, ssep, obj.m_sector1TimeInMS, ssep, obj.m_sector2TimeInMS, ssep,
                    obj.m_sector3TimeInMS, ssep, obj.m_lapValidBitFlags);

  std::vector<char> buf(size + 1);  // note +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.m_lapTimeInMS, ssep, obj.m_sector1TimeInMS, ssep, obj.m_sector2TimeInMS,
                ssep, obj.m_sector3TimeInMS, ssep, obj.m_lapValidBitFlags);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));  // remove null terminator

  return str;
}

LapHistoryData ParseLapHistoryData(std::vector<std::vector<unsigned char>> bytes) {
  LapHistoryData obj;
  std::memcpy(&obj.m_lapTimeInMS, &bytes.at(0).front(), sizeof obj.m_lapTimeInMS);
  std::memcpy(&obj.m_sector1TimeInMS, &bytes.at(1).front(), sizeof obj.m_sector1TimeInMS);
  std::memcpy(&obj.m_sector2TimeInMS, &bytes.at(2).front(), sizeof obj.m_sector2TimeInMS);
  std::memcpy(&obj.m_sector3TimeInMS, &bytes.at(3).front(), sizeof obj.m_sector3TimeInMS);
  std::memcpy(&obj.m_lapValidBitFlags, &bytes.at(4).front(), sizeof obj.m_lapValidBitFlags);
  return obj;
}

std::string TyreStintHistoryDataString(TyreStintHistoryData obj, std::string sep) {
  const char *fmt = "%d%s%d%s%d%s%d%s%d";
  const char *ssep = sep.c_str();

  const std::size_t size =
      std::snprintf(nullptr, 0, fmt, obj.m_endLap, ssep, obj.m_tyreActualCompound, ssep, obj.m_tyreVisualCompound);

  std::vector<char> buf(size + 1);  // note +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, obj.m_endLap, ssep, obj.m_tyreActualCompound, ssep, obj.m_tyreVisualCompound);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));  // remove null terminator

  return str;
}

TyreStintHistoryData ParseTyreStintHistoryData(std::vector<std::vector<unsigned char>> bytes) {
  TyreStintHistoryData obj;
  std::memcpy(&obj.m_endLap, &bytes.at(0).front(), sizeof obj.m_endLap);
  std::memcpy(&obj.m_tyreActualCompound, &bytes.at(1).front(), sizeof obj.m_tyreActualCompound);
  std::memcpy(&obj.m_tyreVisualCompound, &bytes.at(2).front(), sizeof obj.m_tyreVisualCompound);
  return obj;
}

std::string PacketSessionHistoryDataCSVHeader(std::string sep, std::string compr) {
  std::vector<std::string> vec = {
      vpaste(PacketHeaderNames, sep),           //
      vpaste(LapMetaDataNames, sep),            //
      vpaste(LapHistoryDataNames, sep),         //
      vpaste(TyreStintHistoryDataNames, compr)  //
  };
  return vpaste(vec, sep);
}

/**
 * @brief
 *
 * @param obj
 * @param lapID
 * @param sep
 * @param compr outside 'compression' string
 * @param compr2 inside 'compression' string
 * @return std::string
 */
std::string PacketSessionHistoryDataString(PacketSessionHistoryData obj, std::uint8_t lapID, std::string sep,
                                           std::string compr, std::string compr2) {
  std::string compr_TyreStintsHistoryDataString;

  // the eight tyre stints of m_tyreStinsHistoryData are collapsed to a single string
  for (std::uint8_t i = 0; i < 8; i++) {
    compr_TyreStintsHistoryDataString += TyreStintHistoryDataString(obj.m_tyreStintsHistoryData[i], compr) + compr2;
  }
  if (!compr_TyreStintsHistoryDataString.empty()) compr_TyreStintsHistoryDataString.pop_back();

  std::vector<std::string> vec = {
      PacketHeaderString(obj.m_header),                   //
      LapMetaDataString(obj.m_lapMetaData),               //
      LapHistoryDataString(obj.m_lapHistoryData[lapID]),  //
      compr_TyreStintsHistoryDataString                   //
  };
  return vpaste(vec, sep);
}

PacketSessionHistoryData ParsePacketSessionHistoryData(std::vector<unsigned char> bytes) {
  PacketSessionHistoryData obj;
  std::uint16_t offset = 0;

  obj.m_header = ParsePacketHeader(parse_bytes_to_vec(PacketHeaderSizes, bytes, offset));
  offset += sizeof(PacketHeader);

  obj.m_lapMetaData = ParseLapMetaData(parse_bytes_to_vec(LapMetaDataSizes, bytes, offset));
  offset += sizeof(LapMetaData);

  // iterate over all marshal zone array indices to correctly set the offset
  for (std::uint8_t i = 0; i < 100; i++) {
    obj.m_lapHistoryData[i] = ParseLapHistoryData(parse_bytes_to_vec(LapHistoryDataSizes, bytes, offset));
    offset += sizeof(LapHistoryData);
  }

  for (std::uint8_t i = 0; i < 8; i++) {
    obj.m_tyreStintsHistoryData[i] =
        ParseTyreStintHistoryData(parse_bytes_to_vec(TyreStintHistoryDataSizes, bytes, offset));
    offset += sizeof(TyreStintHistoryData);
  }

  return obj;
}
