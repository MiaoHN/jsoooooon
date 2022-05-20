#include <gtest/gtest.h>

#include "json.h"
#include "parser.h"
#include "value.h"

TEST(Json, number) {
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
  EXPECT_STREQ(json["num"].ToString().c_str(), "111.000000");
  EXPECT_STREQ(json["str"].ToString().c_str(), "\"Hello World\"");
  EXPECT_STREQ(json["subjson"]["bool"].ToString().c_str(), "false");
}

TEST(Parse, parse) {
  Jsoooooon::Parser parser;
  Jsoooooon::Json json =
      parser.ParseFromFile("/home/miaohn/codes/jsoooooon/test/json/test.json");
  EXPECT_STREQ(json["result"].ToString().c_str(), "1.000000");
}