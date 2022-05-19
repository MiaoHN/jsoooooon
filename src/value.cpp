#include "value.h"

#include <sstream>

#include "json.h"

namespace Jsoooooon {

Value& Value::operator[](const std::string& index) {
  return _json_node->operator[](index);
}

ValueType Value::GetType() const { return _type; }
void Value::SetType(ValueType type) { _type = type; }

void Value::SetNumber(double number) {
  SetType(J_NUMBER);
  _number = number;
}
void Value::SetString(const std::string& str) {
  SetType(J_STRING);
  _string = str;
}
void Value::SetBool(bool b) {
  SetType(J_BOOL);
  _bool = b;
}
void Value::SetList(std::vector<Value>& l) {
  SetType(J_LIST);
  _list = l;
}
void Value::SetNull() { SetType(J_NULL); }

void Value::SetJson(Json& json) {
  Json::ptr p = std::make_shared<Json>(json);
  SetJson(p);
}

void Value::SetJson(std::shared_ptr<Json> json) {
  SetType(J_OBJECT);
  _json_node = json;
}

double& Value::GetNumber() {
  assert(GetType() == J_NUMBER);
  return _number;
}
bool& Value::GetBool() {
  assert(GetType() == J_BOOL);
  return _bool;
}
std::string& Value::GetString() {
  assert(GetType() == J_STRING);
  return _string;
}
std::vector<Value>& Value::GetList() {
  assert(GetType() == J_LIST);
  return _list;
}
std::shared_ptr<Json> Value::GetJson() {
  assert(GetType() == J_OBJECT);
  return _json_node;
}

std::string Value::ToString() const {
  switch (GetType()) {
    case J_NUMBER:
      return std::to_string(_number);
    case J_STRING:
      return "\"" + _string + "\"";
    case J_NULL:
      return "null";
    case J_BOOL:
      return _bool ? "true" : "false";
    case J_OBJECT:
      return _json_node->ToString();
    case J_LIST: {
      std::stringstream ss;
      ss << "[";
      bool isfirst = true;
      for (auto& item : _list) {
        if (isfirst) {
          ss << item.ToString();
          isfirst = false;
        } else {
          ss << "," << item.ToString();
        }
      }
      ss << "]";
      return ss.str();
    }

    default:
      break;
  }
  return "";
}

}  // namespace Jsoooooon
