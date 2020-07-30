#include "doctest/doctest.h"
#include "fmt/format.h"
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

class JsonMessage {
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
  [[nodiscard]] auto FlatJosn() const -> std::string {
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

TEST_CASE("leveled") {
  SUBCASE("full") {
    JsonMessage msg;

    for (const auto* val : {"first", "second", "third"}) {
      msg.AddArray(val);
    }

    msg.SetKey1("value1");
    msg.SetKey2("value2");

    msg.SetObjectKeyKey1("ValueObjectKeyKey1");
    msg.SetObjectKeyKey2("ValueObjectKeyKey2");
    msg.SetKey3("ValueObjectKeyKey3");

    fmt::print("leveld_full:\n{}\n", msg.OriginalJson());
    fmt::print("{}\n\n", msg.OriginalJson<JsonWriter>());
    std::fflush(stdout);
  }

  SUBCASE("no array") {
    JsonMessage msg;

    msg.SetKey1("value1");
    msg.SetKey2("value2");

    msg.SetObjectKeyKey1("ValueObjectKeyKey1");
    msg.SetObjectKeyKey2("ValueObjectKeyKey2");
    msg.SetKey3("ValueObjectKeyKey3");

    fmt::print("leveld_no_array:\n{}\n\n", msg.OriginalJson());
    std::fflush(stdout);
  }

  SUBCASE("no inner object") {
    JsonMessage msg;

    for (const auto* val : {"first", "second", "third"}) {
      msg.AddArray(val);
    }

    msg.SetKey1("value1");
    msg.SetKey2("value2");

    fmt::print("leveld_no_inner_object:\n{}\n\n", msg.OriginalJson());
    std::fflush(stdout);
  }
}

TEST_CASE("flatted") {
  JsonMessage msg;

  for (const auto* val : {"first", "second", "third"}) {
    msg.AddArray(val);
  }

  msg.SetKey1("value1");
  msg.SetKey2("value2");

  msg.SetObjectKeyKey1("ValueObjectKeyKey1");
  msg.SetObjectKeyKey2("ValueObjectKeyKey2");
  msg.SetKey3("ValueObjectKeyKey3");

  fmt::print("flatted:\n{}\n", msg.FlatJosn());
  fmt::print("{}\n\n", msg.FlatJosn<JsonWriter>());
  std::fflush(stdout);
}