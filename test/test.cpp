#include <gtest/gtest.h>

#include "jsoooooon.h"

TEST(Json, Basic) {
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
  EXPECT_STREQ(json["str"].GetString().c_str(), "Hello World");
  EXPECT_EQ(json["subjson"]["bool"].GetBool(), false);
}

TEST(Json, Morden) {
  Jsoooooon::Json json;
  json["number"] = 2;
  json["string"] = "string";
  json["temp"] = 4;
  EXPECT_EQ(json["number"].GetNumber(), 2);
  EXPECT_STREQ(json["string"].GetString().c_str(), "string");
  EXPECT_EQ(json["temp"].GetNumber(), 4);
  json["temp"] = "temp";
  EXPECT_STREQ(json["temp"].GetString().c_str(), "temp");
  json["bool"].SetBool(false);
  EXPECT_EQ(json["bool"].GetBool(), false);
}

TEST(Parse, Number) {
  Jsoooooon::Parser parser;
  Jsoooooon::Json json = parser.ParseFromFile(
      "/home/miaohn/codes/jsoooooon/test/json/number.json");
  EXPECT_EQ(json["num1"].GetNumber(), 0);
  EXPECT_EQ(json["num2"].GetNumber(), 1);
  EXPECT_EQ(json["num3"].GetNumber(), 1.3e3);
  EXPECT_EQ(json["num4"].GetNumber(), -0.1e5);
  EXPECT_EQ(json["num5"].GetNumber(), -3.57e-2);
}

TEST(Parse, ValueType) {
  Jsoooooon::Parser parser;
  Jsoooooon::Json json =
      parser.ParseFromFile("/home/miaohn/codes/jsoooooon/test/json/value.json");
  EXPECT_EQ(json["string"].GetType(), Jsoooooon::J_STRING);
  EXPECT_EQ(json["number"].GetType(), Jsoooooon::J_NUMBER);
  EXPECT_EQ(json["null"].GetType(), Jsoooooon::J_NULL);
  EXPECT_EQ(json["bool"].GetType(), Jsoooooon::J_BOOL);
  EXPECT_EQ(json["list"].GetType(), Jsoooooon::J_LIST);
  for (auto& item : json["list"].GetList()) {
    EXPECT_EQ(item.GetType(), Jsoooooon::J_STRING);
  }
  EXPECT_EQ(json["object"].GetType(), Jsoooooon::J_OBJECT);
  EXPECT_EQ(json["object"]["object.string"].GetType(), Jsoooooon::J_STRING);
}

TEST(Parse, List) {
  Jsoooooon::Parser parser;
  Jsoooooon::Json json =
      parser.ParseFromFile("/home/miaohn/codes/jsoooooon/test/json/list.json");
  auto vec = json["list"].GetList();
  EXPECT_EQ(vec[0].GetNumber(), 1);
  EXPECT_STREQ(vec[1].GetString().c_str(), "item1");
  EXPECT_EQ(vec[2].GetType(), Jsoooooon::J_NULL);
  EXPECT_EQ(vec[3].GetBool(), true);
  EXPECT_STREQ(vec[4]["str"].GetString().c_str(), "string");
  EXPECT_STREQ(vec[5].GetList()[0].GetString().c_str(), "temp");
}