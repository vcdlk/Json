
#include <gtest/gtest.h>
#include <string_view>


#include "json.h"


TEST(AddTest, JsonParseNull) {

  std::string_view json = "null";

  json::JsonValue value;
  int ret = json::JsonParse(json, &value);

  EXPECT_EQ(ret , json::PARSE_OK);
  EXPECT_EQ(value.m_type, json::JSON_NULL);
}

TEST(AddTest, JsonParseTrue) {

  std::string_view json = "true";

  json::JsonValue value;
  int ret = json::JsonParse(json, &value);

  EXPECT_EQ(ret , json::PARSE_OK);
  EXPECT_EQ(value.m_type, json::JSON_TRUE);
}


TEST(AddTest, JsonParseFalse) {

  std::string_view json = "false";

  json::JsonValue value;
  int ret = json::JsonParse(json, &value);

  EXPECT_EQ(ret , json::PARSE_OK);
  EXPECT_EQ(value.m_type, json::JSON_FALSE);
}