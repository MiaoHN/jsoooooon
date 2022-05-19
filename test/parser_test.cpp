#include "parser.h"

#include <iostream>

#include "json.h"

void test1() {
  Jsoooooon::Parser parser;
  Jsoooooon::Json json =
      parser.ParseFromFile("/home/miaohn/codes/jsoooooon/test/test.json");
  std::cout << "personData.result: " << json["result"].ToString() << std::endl;
}

int main(int argc, char const *argv[]) {
  test1();
  return 0;
}
