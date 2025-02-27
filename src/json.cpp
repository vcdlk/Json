#include "json.h"
#include "log.h"
#include <cassert>
#include <cstddef>
#include <cstring>
#include <string_view>

#include <iostream>

namespace json {

int JsonParse(const std::string_view &str, JsonValue *value) {
  assert(value != nullptr);
  Context context;
  context.json = str;
  value->m_type = JSON_NULL;

  // 处理前缀空字符
  ParseWhiteSpace(&context);
  // 解析json
  LOG("context.json: %s", context.json.data());
  return ParseValue(&context, value);
}

void ParseWhiteSpace(Context *context) {
  const std::string_view json = context->json;
  const size_t pos = json.find_first_not_of(" \t\n\r");
  if (pos != std::string_view::npos) {
    context->json.remove_prefix(pos);
  } else {
    context->json.remove_prefix(context->json.size());
  }
  LOG("context.json: %s", json.data());
}

int ParseValue(Context *context, JsonValue *value) {
  const std::string_view json = context->json;
  LOG("json: %s", json.data());

  if (json.empty()) {
    return PARSE_EXPECT_VALUE;
  }

  const char first = json.at(0);
  LOG("first: %c", first);

  switch (first) {
  case 'n': {
    return ParseNullTrueFalse(context, value, "null");
    break;
  }
  case 't': {
    return ParseNullTrueFalse(context, value, "true");
    break;
  }
  case 'f': {
    return ParseNullTrueFalse(context, value, "false");
    break;
  }
  case '\0': {
    return PARSE_EXPECT_VALUE;
  }
  default:
    return PARSE_INVALID_VALUE;
  }
  return PARSE_EXPECT_VALUE;
}

int ParseNullTrueFalse(Context *context, JsonValue *value,
                       const std::string_view &perfix) {
  std::string_view json = context->json;
  if (json.size() < perfix.size()) {
    return PARSE_EXPECT_VALUE;
  }
  LOG("first: %s", json.data());
  LOG("perfix: %s", perfix.data());

  bool is_same_perfix = (json.compare(0, perfix.size(), perfix) == 0);

  LOG("is_same_perfix: %d", is_same_perfix);

  if (!is_same_perfix) {
    return PARSE_EXPECT_VALUE;
  } else {
    if (perfix == "true") {
      value->m_type = JSON_TRUE;
      LOG("JSON_TRUE: %d", JSON_TRUE);

    } else if (perfix == "false") {
      value->m_type = JSON_FALSE;
      LOG("JSON_FALSE: %d", JSON_FALSE);

    } else if (perfix == "null") {
      value->m_type = JSON_NULL;
      LOG("JSON_NULL: %d", JSON_NULL);
    }
    context->json = context->json.substr(perfix.size());
    return PARSE_OK;
  }
  return PARSE_EXPECT_VALUE;
}

} // namespace json