#include "json.h"

#include <iostream>
#include <sstream>

namespace Jsoooooon {

Value& Json::operator[](const std::string& key) {
  auto iter = _map.find(key);
  if (iter != _map.end()) {
    return iter->second;
  }
  // 添加一个 key: value 对
  Value value;
  value.SetNull();
  AddNode(key, value);
  iter = _map.find(key);
  return iter->second;
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
