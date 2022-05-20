#ifndef __PARSER_H__
#define __PARSER_H__

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "json.h"

namespace Jsoooooon {

class Parser {
 public:
  Parser() {}

  Json ParseFromFile(const std::string& path);
  Json ParseFromString(const std::string& str);

 private:
  Json parse();
  void skip_whitespace();
  std::string parse_string();
  std::string parse_key();
  double parse_number();
  Json parse_object();
  Value parse_list();
  Value parse_value();
  bool parse_bool();
  void parse_null();

 private:
  std::string _data;
  int curr = 0;
};

}  // namespace Jsoooooon

#endif  // __PARSER_H__