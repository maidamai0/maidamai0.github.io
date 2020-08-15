"""@ read a json schema and generate a cpp file
assume all value types are std::string
"""

import json
import argparse
import os
import sys

headers = ''' #pragma once

// DON't edit this file, generated with scipt automatically

# include "rapidjson/prettywriter.h"
# include "rapidjson/stringbuffer.h"
# include "rapidjson/writer.h"

# include <memory>
# include <string>
# include <vector>

using PrettyJsonWriter = rapidjson::PrettyWriter<rapidjson::StringBuffer>;
using JsonWriter = rapidjson::Writer<rapidjson::StringBuffer>;

class JsonMessage {
public:
'''


def underscore_to_camelcase(name):
    """ convert under score names to
    camelcase names
    function_name -> FunctionName

    member are underscore style
    setter funtions are camelcase style
    """
    output = ""
    for word in name.split("_"):
        output += word.capitalize()
    return output


def write_member(properties, cpp, prefix=""):
    """write members
    array   -> std::vector<std::string> key_name_
    object  -> std::string object_name_key_name_;
    others  -> std::string key_name_;
    """
    for key in properties:
        value = properties[key]
        value_type = value["type"]
        if value_type == "string":
            cpp.write("std::string " + prefix + key + "_;\n")
        elif value_type == "object":
            write_member(value["properties"], cpp, key+"_")
        elif value_type == "array":
            cpp.write("std::vector<std::string> " + prefix + key + "_;\n\n")


def write_setters(properties, cpp, prefix=""):
    """ Set values of member
    array   -> Add* add a value to the array
    object  -> SetObjectNameKey
    others  -> SetKey
    """
    for key in properties:
        member = prefix + key + "_"
        value = properties[key]
        value_type = value["type"]
        if value_type == "string":
            cpp.write(
                f"auto Set{underscore_to_camelcase(member)} (const std::string & val) -> void {{ {member} = val;}}\n\n")
        elif value_type == "object":
            write_setters(value["properties"], cpp, key + "_")
        elif value_type == "array":
            cpp.write(
                f"auto Add{underscore_to_camelcase(member)} (const std::string & val) -> void {{ {member}.push_back(val);}}\n\n")


def write_to_json(properties, cpp, prefix=""):
    """Get a json string using rapidjson API
    """
    for key in properties:
        member = prefix+key + "_"
        value = properties[key]
        value_type = value["type"]
        if value_type == "string":
            cpp.write(f"if(!{member}.empty()){{\n")
            cpp.write(
                f'''writer.Key("{key}");writer.String({member}.c_str());''')
            cpp.write("}\n\n")
        elif value_type == "array":
            cpp.write(f'''if (!{member}.empty()) {{
                    writer.Key("{key}");
                    writer.StartArray(); ''')
            cpp.write(f''' for (const auto & val: {member}) {{
                    writer.String(val.c_str());
                }}''')
            cpp.write("writer.EndArray();}\n\n")
        elif value_type == "object":
            check = ""
            for sub_key in value["properties"]:
                if value["properties"][sub_key]["type"] == "object":
                    continue
                sub_member = prefix + key + "_" + sub_key + "_"
                if(check):
                    check = f"{check} || !{sub_member}.empty()"
                else:
                    check = f"!{sub_member}.empty()"
            cpp.write(f"if({check}) {{\n")
            cpp.write(f'writer.Key("{key}");')
            cpp.write("writer.StartObject();")
            write_to_json(value["properties"], cpp, key+"_")
            cpp.write("writer.EndObject();")
            cpp.write("}\n")


def generate(src, dest):
    src = os.path.abspath(src)
    dest = os.path.abspath(dest)
    print(f"read {src} and generate to {dest}")

    # open dest file to write
    cpp = open(dest, "w")
    cpp.write(headers)

    f = open(src)
    schema = json.load(f)
    properties = schema["properties"]

    # Setters
    write_setters(properties, cpp)

    # to json
    cpp.write("[[nodiscard]] auto ToJson() const -> std::string {\n")
    cpp.write('''using namespace rapidjson;
    StringBuffer buffer;
    JsonWriter writer(buffer);

    writer.StartObject();\n''')
    write_to_json(properties, cpp)
    cpp.write("writer.EndObject();return buffer.GetString();}\n")

    # private memner
    cpp.write("private:\n")
    write_member(properties, cpp)

    # end class
    cpp.write("};\n")
    cpp.close()

    # format cpp code using clang-format with google style
    os.system(f"clang-format -i -style=google {dest}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="generate cpp class with json schema")
    parser.add_argument("--src", "-s",
                        help="json schecma path")
    parser.add_argument("--dest", "-d",
                        help="destination folder")

    args = parser.parse_args()
    if len(sys.argv) < 3:
        parser.print_help()
    else:
        generate(args.src, args.dest)
