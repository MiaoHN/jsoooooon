#include <gtest/gtest.h>

#include "jsoooooon.h"

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
  EXPECT_EQ(json["num"].GetNumber(), 111);
  EXPECT_STREQ(json["str"].ToString().c_str(), "\"Hello World\"");
  EXPECT_EQ(json["subjson"]["bool"].GetBool(), false);
}

TEST(Parse, parseNumber) {
  Jsoooooon::Parser parser;
  Jsoooooon::Json json = parser.ParseFromFile(
      "/home/miaohn/codes/jsoooooon/test/json/number.json");
  EXPECT_EQ(json["num1"].GetNumber(), 0);
  EXPECT_EQ(json["num2"].GetNumber(), 1);
  EXPECT_EQ(json["num3"].GetNumber(), 1.3e3);
  EXPECT_EQ(json["num4"].GetNumber(), -0.1e5);
  EXPECT_EQ(json["num5"].GetNumber(), -3.57e-2);
}

TEST(Parse, parseValue) {
  Jsoooooon::Parser parser;
  Jsoooooon::Json json =
      parser.ParseFromFile("/home/miaohn/codes/jsoooooon/test/json/value.json");
  EXPECT_EQ(json["string"].GetType(), Jsoooooon::J_STRING);
  EXPECT_EQ(json["number"].GetType(), Jsoooooon::J_NUMBER);
  EXPECT_EQ(json["null"].GetType(), Jsoooooon::J_NULL);
  EXPECT_EQ(json["bool"].GetType(), Jsoooooon::J_BOOL);
  EXPECT_EQ(json["list"].GetType(), Jsoooooon::J_LIST);
  for (auto &item : json["list"].GetList()) {
    EXPECT_EQ(item.GetType(), Jsoooooon::J_STRING);
  }
  EXPECT_EQ(json["object"].GetType(), Jsoooooon::J_OBJECT);
  EXPECT_EQ(json["object"]["object.string"].GetType(), Jsoooooon::J_STRING);
}