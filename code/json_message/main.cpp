#include "doctest/doctest.h"
#include "fmt/format.h"
#include "json_message.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

#include <memory>
#include <string>
#include <vector>

[[maybe_unused]] constexpr auto example = R"(
{
  "array": [
    "first",
    "second,
    "third"
  ],
  "key1": "value1",
  "key2": "value2",
  "ObjectKey": {
    "key1": "ValueObjectKeyKey1",
    "key2": "ValueObjectKeyKey2",
    "key3": "ValueObjectKeyKey3"
  }
}
)";

using PrettyJsonWriter = rapidjson::PrettyWriter<rapidjson::StringBuffer>;
using JsonWriter = rapidjson::Writer<rapidjson::StringBuffer>;

class JsonMsg {
public:
  // first level array
  void AddArray(const std::string& val) {
    array_.push_back(val);
  }

  // first level
  void SetKey1(const std::string& val) {
    key1_ = val;
  }
  void SetKey2(const std::string& val) {
    key2_ = val;
  }

  // second level
  void SetObjectKeyKey1(const std::string& val) {
    object_key_key1_ = val;
  }
  void SetObjectKeyKey2(const std::string& val) {
    object_key_key2_ = val;
  }
  void SetKey3(const std::string& val) {
    object_key_key3_ = val;
  }

  template <typename WriterType = rapidjson::PrettyWriter<rapidjson::StringBuffer>>
  [[nodiscard]] auto OriginalJson() const -> std::string {
    using namespace rapidjson;
    StringBuffer buffer;
    WriterType writer(buffer);

    // first level
    writer.StartObject();

    // array
    if (!array_.empty()) {
      writer.Key("array");
      writer.StartArray();
      for (const auto& val : array_) {
        writer.String(val.c_str());
      }
      writer.EndArray();
    }

    if (!key1_.empty()) {
      writer.Key("key1");
      writer.String(key1_.c_str());
    }

    if (!key2_.empty()) {
      writer.Key("key2");
      writer.String(key2_.c_str());
    }

    // second level
    if (!object_key_key1_.empty() || !object_key_key2_.empty() || !object_key_key3_.empty()) {
      writer.Key("ObjectKey");
      writer.StartObject();

      if (!object_key_key1_.empty()) {
        writer.Key("key1");
        writer.String("ValueObjectKeyKey1");
      }

      if (!object_key_key2_.empty()) {
        writer.Key("key2");
        writer.String("ValueObjectKeyKey2");
      }

      if (!object_key_key3_.empty()) {
        writer.Key("key3");
        writer.String("ValueObjectKeyKey3");
      }

      writer.EndObject();
    }

    writer.EndObject();

    return buffer.GetString();
  }

  template <typename WriterType = PrettyJsonWriter>
  [[nodiscard]] auto FlatJson() const -> std::string {
    using namespace rapidjson;
    StringBuffer buffer;
    WriterType writer(buffer);

    // first level
    writer.StartObject();

    // array
    if (!array_.empty()) {
      writer.Key("array");
      writer.StartArray();
      for (const auto& val : array_) {
        writer.String(val.c_str());
      }
      writer.EndArray();
    }

    if (!key1_.empty()) {
      writer.Key("key1");
      writer.String(key1_.c_str());
    }

    if (!key2_.empty()) {
      writer.Key("key2");
      writer.String(key2_.c_str());
    }

    if (!object_key_key1_.empty()) {
      writer.Key("key1");
      writer.String("ValueObjectKeyKey1");
    }

    if (!object_key_key2_.empty()) {
      writer.Key("key2");
      writer.String("ValueObjectKeyKey2");
    }

    if (!object_key_key3_.empty()) {
      writer.Key("key3");
      writer.String("ValueObjectKeyKey3");
    }

    writer.EndObject();

    return buffer.GetString();
  }

private:
  std::vector<std::string> array_;
  std::string key1_;
  std::string key2_;
  std::string object_key_key1_;
  std::string object_key_key2_;
  std::string object_key_key3_;
};

auto TestName() {
  return doctest::detail::g_cs->currentTest->m_name;
}

TEST_CASE("level full") {
  JsonMsg msg;

  for (const auto* val : {"first", "second", "third"}) {
    msg.AddArray(val);
  }

  msg.SetKey1("value1");
  msg.SetKey2("value2");

  msg.SetObjectKeyKey1("ValueObjectKeyKey1");
  msg.SetObjectKeyKey2("ValueObjectKeyKey2");
  msg.SetKey3("ValueObjectKeyKey3");

  fmt::print("{}:\n{}\n", TestName(), msg.OriginalJson());
  fmt::print("{}\n\n", msg.OriginalJson<JsonWriter>());
  std::fflush(stdout);
}

TEST_CASE("level no array") {
  JsonMsg msg;

  msg.SetKey1("value1");
  msg.SetKey2("value2");

  msg.SetObjectKeyKey1("ValueObjectKeyKey1");
  msg.SetObjectKeyKey2("ValueObjectKeyKey2");
  msg.SetKey3("ValueObjectKeyKey3");

  fmt::print("{}:\n{}\n", TestName(), msg.OriginalJson());
  std::fflush(stdout);
}

TEST_CASE("level no inner object") {
  JsonMsg msg;

  for (const auto* val : {"first", "second", "third"}) {
    msg.AddArray(val);
  }

  msg.SetKey1("value1");
  msg.SetKey2("value2");

  fmt::print("{}:\n{}\n", TestName(), msg.OriginalJson());
  std::fflush(stdout);
}

TEST_CASE("flatted") {
  JsonMsg msg;

  for (const auto* val : {"first", "second", "third"}) {
    msg.AddArray(val);
  }

  msg.SetKey1("value1");
  msg.SetKey2("value2");

  msg.SetObjectKeyKey1("ValueObjectKeyKey1");
  msg.SetObjectKeyKey2("ValueObjectKeyKey2");
  msg.SetKey3("ValueObjectKeyKey3");

  fmt::print("{}:\n{}\n", TestName(), msg.FlatJson());
  fmt::print("{}\n\n", msg.FlatJson<JsonWriter>());
  std::fflush(stdout);
}

TEST_CASE("JsonGenerate full") {
  JsonMessage msg;
  msg.SetKey1("value1");
  msg.SetKey2("value2");
  msg.SetKey3("value3");
  msg.SetKey4("value4");
  msg.SetKey5("value5");

  msg.AddArrayKey1("arrayValue1");
  msg.AddArrayKey1("arrayValue2");
  msg.AddArrayKey1("arrayValue3");
  msg.AddArrayKey1("arrayValue4");
  msg.AddArrayKey1("arrayValue5");

  msg.SetObjectKey1Key1("objectvalue1");
  msg.SetObjectKey1Key2("objectvalue2");

  fmt::print("{}:\n{}\n\n", TestName(), msg.ToJson());
  std::fflush(stdout);
}

TEST_CASE("JsonGenerate no inner objecet") {
  JsonMessage msg;
  msg.SetKey1("value1");
  msg.SetKey2("value2");
  msg.SetKey3("value3");
  msg.SetKey4("value4");
  msg.SetKey5("value5");

  msg.AddArrayKey1("arrayValue1");
  msg.AddArrayKey1("arrayValue2");
  msg.AddArrayKey1("arrayValue3");
  msg.AddArrayKey1("arrayValue4");
  msg.AddArrayKey1("arrayValue5");

  fmt::print("{}:\n{}\n\n", TestName(), msg.ToJson());
  std::fflush(stdout);
}
