#ifndef __VALUE_H__
#define __VALUE_H__

#include <cassert>
#include <memory>
#include <string>
#include <vector>

namespace Jsoooooon {

class Json;

enum ValueType {
  J_UNKNOWN,
  J_LIST,
  J_OBJECT,
  J_NUMBER,
  J_STRING,
  J_BOOL,
  J_NULL,
};

class Value {
 public:
  Value() { _type = J_UNKNOWN; }
  ~Value() {}

  std::string ToString() const;

  Value& operator[](const std::string& index);

  ValueType GetType() const;
  void SetType(ValueType type);

  void SetNumber(double number);
  void SetString(const std::string& str);
  void SetBool(bool b);
  void SetList(std::vector<Value>& l);
  void SetNull();
  void SetJson(Json& json);
  void SetJson(std::shared_ptr<Json> json);

  double& GetNumber();
  bool& GetBool();
  std::string& GetString();
  std::vector<Value>& GetList();
  std::shared_ptr<Json> GetJson();

 private:
  ValueType _type;
  double _number;
  bool _bool;
  std::string _string;
  std::vector<Value> _list;
  std::shared_ptr<Json> _json_node;
};

}  // namespace Jsoooooon

#endif  // __VALUE_H__