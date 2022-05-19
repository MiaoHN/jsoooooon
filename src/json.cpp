#include "json.h"

#include <iostream>
#include <sstream>

namespace Jsoooooon {

Value& Json::operator[](const std::string& key) {
  auto iter = _map.find(key);
  if (iter != _map.end()) {
    return iter->second;
  }
  std::cout << "no such key: " << key << std::endl;
  exit(-1);
}

std::string Json::ToString() const {
  std::stringstream ss;
  ss << "{";
  bool is_first = true;
  for (auto& item : _map) {
    if (is_first) {
      ss << "\"" << item.first << "\": " << item.second.ToString();
      is_first = false;
    } else {
      ss << ",\"" << item.first << "\": " << item.second.ToString();
    }
  }
  ss << "}";
  return ss.str();
}

}  // namespace Jsoooooon
