#ifndef __JSON_H__
#define __JSON_H__

#include <map>
#include <memory>
#include <string>

#include "value.h"

namespace Jsoooooon {

class Json {
 public:
  using ptr = std::shared_ptr<Json>;

  Json() {}
  ~Json() {}

  void AddNode(const std::string& key, const Value& value) {
    _map[key] = value;
  }

  void DelNode(const std::string& key) { _map.erase(key); }

  // key: value
  // json[key] = value
  Value& operator[](const std::string& key);

  std::string ToString() const;

 private:
  std::map<std::string, Value> _map;
};

}  // namespace Jsoooooon

#endif  // __JSON_H__