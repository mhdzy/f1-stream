#include "Maps.hpp"

std::vector<int> getMapKeys(std::map<int, std::string> map) {
  std::vector<int> keys;
  for (std::map<int, std::string>::iterator it = map.begin(); it != map.end(); ++it) {
    keys.push_back(it->first);
    std::cout << "key: " << it->first << std::endl;
  }
  return (keys);
};

std::vector<std::string> getMapValues(std::map<int, std::string> map) {
  std::vector<std::string> values;
  for (std::map<int, std::string>::iterator it = map.begin(); it != map.end(); ++it) {
    values.push_back(it->second);
    std::cout << "value: " << it->second << std::endl;
  }
  return (values);
};
