#include "json.h"

#include <iostream>

#include "value.h"

// {"num": 111.000000,"str": "Hello World","subjson": {"bool": false}}
void test1() {
  Jsoooooon::Json json;
  Jsoooooon::Value value;
  value.SetNumber(111);
  json.AddNode("num", value);
  value.SetString("Hello World");
  json.AddNode("str", value);
  Jsoooooon::Json json2;
  value.SetBool(false);
  json2.AddNode("bool", value);
  value.SetJson(json2);
  json.AddNode("subjson", value);
  std::cout << "raw: " << json.ToString() << std::endl;
  Jsoooooon::Value number = json["num"];
  std::cout << "num: " << number.ToString() << std::endl;
  Jsoooooon::Value str = json["str"];
  std::cout << "str: " << str.ToString() << std::endl;
  Jsoooooon::Value object = json["subjson"];
  std::cout << "object: " << object.ToString() << std::endl;
  Jsoooooon::Value bol = json["subjson"]["bool"];
  std::cout << "subjson.bool: " << bol.ToString() << std::endl;
}

void test2() {
  std::vector<Jsoooooon::Value> l;
  Jsoooooon::Value value;
  value.SetBool(true);
  l.push_back(value);
  value.SetString("list");
  l.push_back(value);
  value.SetNull();
  l.push_back(value);
  Jsoooooon::Json json;
  Jsoooooon::Value lis;
  lis.SetList(l);
  json.AddNode("list", lis);
  lis.SetString("test");
  json.AddNode("str", lis);
  std::cout << json.ToString() << std::endl;
}

int main(int argc, char const *argv[]) {
  std::cout << "====================" << std::endl;
  test1();
  std::cout << "====================" << std::endl;
  test2();

  return 0;
}
