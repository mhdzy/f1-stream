#include "PacketCarDamageData.hpp"

std::vector<std::size_t> CarDamageDataSizes = {
    sizeof(((CarDamageData *)0)->m_tyresWear),             // Tyre wear (percentage)
    sizeof(((CarDamageData *)0)->m_tyresDamage),           // Tyre damage (percentage)
    sizeof(((CarDamageData *)0)->m_brakesDamage),          // Brakes damage (percentage)
    sizeof(((CarDamageData *)0)->m_frontLeftWingDamage),   // Front left wing damage (percentage)
    sizeof(((CarDamageData *)0)->m_frontRightWingDamage),  // Front right wing damage (percentage)
    sizeof(((CarDamageData *)0)->m_rearWingDamage),        // Rear wing damage (percentage)
    sizeof(((CarDamageData *)0)->m_floorDamage),           // Floor damage (percentage)
    sizeof(((CarDamageData *)0)->m_diffuserDamage),        // Diffuser damage (percentage)
    sizeof(((CarDamageData *)0)->m_sidepodDamage),         // Sidepod damage (percentage)
    sizeof(((CarDamageData *)0)->m_drsFault),              // Indicator for DRS fault, 0 = OK, 1 = fault
    sizeof(((CarDamageData *)0)->m_ersFault),              // Indicator for ERS fault, 0 = OK, 1 = fault
    sizeof(((CarDamageData *)0)->m_gearBoxDamage),         // Gear box damage (percentage)
    sizeof(((CarDamageData *)0)->m_engineDamage),          // Engine damage (percentage)
    sizeof(((CarDamageData *)0)->m_engineMGUHWear),        // Engine wear MGU-H (percentage)
    sizeof(((CarDamageData *)0)->m_engineESWear),          // Engine wear ES (percentage)
    sizeof(((CarDamageData *)0)->m_engineCEWear),          // Engine wear CE (percentage)
    sizeof(((CarDamageData *)0)->m_engineICEWear),         // Engine wear ICE (percentage)
    sizeof(((CarDamageData *)0)->m_engineMGUKWear),        // Engine wear MGU-K (percentage)
    sizeof(((CarDamageData *)0)->m_engineTCWear),          // Engine wear TC (percentage)
    sizeof(((CarDamageData *)0)->m_engineBlown),           // Engine blown, 0 = OK, 1 = fault
    sizeof(((CarDamageData *)0)->m_engineSeized)           // Engine seized, 0 = OK, 1 = fault
};

std::vector<std::string> CarDamageDataNames = {
    "m_tyresWear",             // Tyre wear (percentage)
    "m_tyresDamage",           // Tyre damage (percentage)
    "m_brakesDamage",          // Brakes damage (percentage)
    "m_frontLeftWingDamage",   // Front left wing damage (percentage)
    "m_frontRightWingDamage",  // Front right wing damage (percentage)
    "m_rearWingDamage",        // Rear wing damage (percentage)
    "m_floorDamage",           // Floor damage (percentage)
    "m_diffuserDamage",        // Diffuser damage (percentage)
    "m_sidepodDamage",         // Sidepod damage (percentage)
    "m_drsFault",              // Indicator for DRS fault, 0 = OK, 1 = fault
    "m_ersFault",              // Indicator for ERS fault, 0 = OK, 1 = fault
    "m_gearBoxDamage",         // Gear box damage (percentage)
    "m_engineDamage",          // Engine damage (percentage)
    "m_engineMGUHWear",        // Engine wear MGU-H (percentage)
    "m_engineESWear",          // Engine wear ES (percentage)
    "m_engineCEWear",          // Engine wear CE (percentage)
    "m_engineICEWear",         // Engine wear ICE (percentage)
    "m_engineMGUKWear",        // Engine wear MGU-K (percentage)
    "m_engineTCWear",          // Engine wear TC (percentage)
    "m_engineBlown",           // Engine blown, 0 = OK, 1 = fault
    "m_engineSeized"           // Engine seized, 0 = OK, 1 = fault
};

std::string CarDamageDataString(CarDamageData obj, std::string sep) {
  const char *fmt = "%s%s%s%s%s%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d%s%d";
  const char *ssep = sep.c_str();
  const std::string csep = "/";

  std::string m_tyresWear(vpaste(
      std::vector<std::string>{
          ftos(obj.m_tyresWear[0]),  //
          ftos(obj.m_tyresWear[1]),  //
          ftos(obj.m_tyresWear[2]),  //
          ftos(obj.m_tyresWear[3])   //
      },
      csep));

  std::string m_tyresDamage(vpaste(
      std::vector<std::string>{
          std::to_string(obj.m_tyresDamage[0]),  //
          std::to_string(obj.m_tyresDamage[1]),  //
          std::to_string(obj.m_tyresDamage[2]),  //
          std::to_string(obj.m_tyresDamage[3])   //
      },
      csep));

  std::string m_brakesDamage(vpaste(
      std::vector<std::string>{
          std::to_string(obj.m_brakesDamage[0]),  //
          std::to_string(obj.m_brakesDamage[1]),  //
          std::to_string(obj.m_brakesDamage[2]),  //
          std::to_string(obj.m_brakesDamage[3])   //
      },
      csep));

  // TODO: figure out why this is segfaulting
  const std::size_t size = std::snprintf(
      nullptr, 0, fmt, m_tyresWear.c_str(), ssep, m_tyresDamage.c_str(), ssep, m_brakesDamage.c_str(), ssep,
      obj.m_frontLeftWingDamage, ssep, obj.m_frontRightWingDamage, ssep, obj.m_rearWingDamage, ssep, obj.m_floorDamage,
      ssep, obj.m_diffuserDamage, ssep, obj.m_sidepodDamage, ssep, obj.m_drsFault, ssep, obj.m_ersFault, ssep,
      obj.m_gearBoxDamage, ssep, obj.m_engineDamage, ssep, obj.m_engineMGUHWear, ssep, obj.m_engineESWear, ssep,
      obj.m_engineCEWear, ssep, obj.m_engineICEWear, ssep, obj.m_engineMGUKWear, ssep, obj.m_engineTCWear, ssep,
      obj.m_engineBlown, ssep, obj.m_engineSeized);

  std::vector<char> buf(size + 1);  // note +1 for null terminator
  std::snprintf(&buf[0], buf.size(), fmt, m_tyresWear.c_str(), ssep, m_tyresDamage.c_str(), ssep,
                m_brakesDamage.c_str(), ssep, obj.m_frontLeftWingDamage, ssep, obj.m_frontRightWingDamage, ssep,
                obj.m_rearWingDamage, ssep, obj.m_floorDamage, ssep, obj.m_diffuserDamage, ssep, obj.m_sidepodDamage,
                ssep, obj.m_drsFault, ssep, obj.m_ersFault, ssep, obj.m_gearBoxDamage, ssep, obj.m_engineDamage, ssep,
                obj.m_engineMGUHWear, ssep, obj.m_engineESWear, ssep, obj.m_engineCEWear, ssep, obj.m_engineICEWear,
                ssep, obj.m_engineMGUKWear, ssep, obj.m_engineTCWear, ssep, obj.m_engineBlown, ssep,
                obj.m_engineSeized);

  std::string str(buf.begin(), buf.end());
  str.erase(str.find('\0'));

  return str;
}

CarDamageData ParseCarDamageData(std::vector<std::vector<unsigned char>> bytes) {
  CarDamageData obj;
  std::uint8_t idx[4] = {0, 1, 2, 3};

  for (std::uint8_t i : idx)
    std::memcpy(&obj.m_tyresWear[i], &bytes.at(0).front() + (i * sizeof obj.m_tyresWear[i]), sizeof obj.m_tyresWear[i]);

  for (std::uint8_t i : idx)
    std::memcpy(&obj.m_tyresDamage[i], &bytes.at(1).front() + (i * sizeof obj.m_tyresDamage[i]),
                sizeof obj.m_tyresDamage[i]);

  for (std::uint8_t i : idx)
    std::memcpy(&obj.m_brakesDamage[i], &bytes.at(2).front() + (i * sizeof obj.m_brakesDamage[i]),
                sizeof obj.m_brakesDamage[i]);

  std::memcpy(&obj.m_frontLeftWingDamage, &bytes.at(3).front(), sizeof obj.m_frontLeftWingDamage);
  std::memcpy(&obj.m_frontRightWingDamage, &bytes.at(4).front(), sizeof obj.m_frontRightWingDamage);
  std::memcpy(&obj.m_rearWingDamage, &bytes.at(5).front(), sizeof obj.m_rearWingDamage);
  std::memcpy(&obj.m_floorDamage, &bytes.at(6).front(), sizeof obj.m_floorDamage);
  std::memcpy(&obj.m_diffuserDamage, &bytes.at(7).front(), sizeof obj.m_diffuserDamage);
  std::memcpy(&obj.m_sidepodDamage, &bytes.at(8).front(), sizeof obj.m_sidepodDamage);
  std::memcpy(&obj.m_drsFault, &bytes.at(9).front(), sizeof obj.m_drsFault);
  std::memcpy(&obj.m_ersFault, &bytes.at(10).front(), sizeof obj.m_ersFault);
  std::memcpy(&obj.m_gearBoxDamage, &bytes.at(11).front(), sizeof obj.m_gearBoxDamage);
  std::memcpy(&obj.m_engineDamage, &bytes.at(12).front(), sizeof obj.m_engineDamage);
  std::memcpy(&obj.m_engineMGUHWear, &bytes.at(13).front(), sizeof obj.m_engineMGUHWear);
  std::memcpy(&obj.m_engineESWear, &bytes.at(14).front(), sizeof obj.m_engineESWear);
  std::memcpy(&obj.m_engineCEWear, &bytes.at(15).front(), sizeof obj.m_engineCEWear);
  std::memcpy(&obj.m_engineICEWear, &bytes.at(16).front(), sizeof obj.m_engineICEWear);
  std::memcpy(&obj.m_engineMGUKWear, &bytes.at(17).front(), sizeof obj.m_engineMGUKWear);
  std::memcpy(&obj.m_engineTCWear, &bytes.at(18).front(), sizeof obj.m_engineTCWear);
  std::memcpy(&obj.m_engineBlown, &bytes.at(19).front(), sizeof obj.m_engineBlown);
  std::memcpy(&obj.m_engineSeized, &bytes.at(20).front(), sizeof obj.m_engineSeized);

  return obj;
}

std::string PacketCarDamageDataCSVHeader(std::string sep) {
  std::vector<std::string> vec = {
      vpaste(PacketHeaderNames, sep),  //
      vpaste(CarDamageDataNames, sep)  //
  };

  return vpaste(vec, sep);
}

std::string PacketCarDamageDataString(PacketCarDamageData obj, std::uint8_t carID, std::string sep) {
  std::vector<std::string> vec = {
      PacketHeaderString(obj.m_header),                //
      CarDamageDataString(obj.m_carDamageData[carID])  //
  };
  return vpaste(vec, sep);
}

PacketCarDamageData ParsePacketCarDamageData(std::vector<unsigned char> bytes) {
  PacketCarDamageData obj;
  std::uint16_t offset = 0;

  // parse header
  obj.m_header = ParsePacketHeader(parse_bytes_to_vec(PacketHeaderSizes, bytes, offset));
  offset += sizeof(PacketHeader);

  // loop over the 22 car data packets and parse them
  for (std::uint8_t i = 0; i < 22; i++) {
    obj.m_carDamageData[i] = ParseCarDamageData(parse_bytes_to_vec(CarDamageDataSizes, bytes, offset));
    offset += sizeof(CarDamageData);
  }

  return obj;
}
