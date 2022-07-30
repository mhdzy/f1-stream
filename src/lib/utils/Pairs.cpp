#include "Pairs.hpp"

std::vector<std::pair<int, std::string>> init_pairs(std::vector<int> k, std::vector<std::string> v) {
  std::vector<std::pair<int, std::string>> pairs;
  for (int i = 0; i < k.size() - 1; i++) pairs.push_back(std::make_pair(k[i], v[i]));
  return (pairs);
};
