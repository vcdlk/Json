#pragma once

#include <string_view>

namespace json {

enum JsonType {
  JSON_NULL,
  JSON_FALSE,
  JSON_TRUE,
  JSON_NUMBER,
  JSON_STRING,
  JSON_ARRAY,
  JSON_OBJECT,
};


enum ErrorType{
  PARSE_OK = 0,
  PARSE_EXPECT_VALUE,
  PARSE_INVALID_VALUE,
  PARSE_ROOT_NOT_SINGULAR
};


struct Context{
  std::string_view json;
};


class JsonValue{
  public:
  JsonType m_type;
};


int JsonParse(const std::string_view& str, JsonValue* value);

int GetType(const JsonValue& value);

void ParseWhiteSpace(Context* context);

int ParseValue(Context* context, JsonValue* value);

int ParseNullTrueFalse(Context* context, JsonValue* value, const std::string_view& perfix);

}
