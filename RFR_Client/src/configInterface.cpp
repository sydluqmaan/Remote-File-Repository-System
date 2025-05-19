#include "configInterface.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include <rapidjson/filewritestream.h>
#include <rapidjson/filereadstream.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>


void ConfigInterface::updateConfigFile(std::string key, std::string value) { // TODO: implement proper error handling

    FILE* fp = std::fopen("D:/Projects/RFR_CLIENT/src/config.json", "r"); // TODO: replace directory path
    if (!fp) {
        throw std::runtime_error("Failed to open config.json for reading");
    }

    char buffer[1024];
    rapidjson::FileReadStream is(fp, buffer, 1024);

    rapidjson::Document document;
    document.ParseStream(is);
    std::fclose(fp);

    if (document.HasParseError()) {
        std::cerr << "Config file parse error: " << document.GetParseError() << std::endl;
        throw std::runtime_error("Config file parse error");
    }

    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    if (document.HasMember(key.c_str())) {
        document[key.c_str()].SetString(value.c_str(), allocator);
    } else {
        rapidjson::Value keyVal(key.c_str(), allocator);
        rapidjson::Value valueVal(value.c_str(), allocator);
        document.AddMember(keyVal, valueVal, allocator);
    }

    FILE* fp_out = std::fopen("D:/Projects/RFR_CLIENT/src/config.json", "w"); // TODO: replace directory path
    rapidjson::FileWriteStream os(fp_out, buffer, 1024);
    rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
    document.Accept(writer);
    std::fclose(fp_out);
}

std::string ConfigInterface::readConfigFile(const std::string& label) {
    const std::string& file_path = "D:/Projects/RFR_SERVER/config.json";    // TODO: fix path
    std::ifstream file(file_path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open JSON file: " + file_path);
    }

    nlohmann::json j;
    file >> j;

    if (!j.contains(label)) {
        throw std::runtime_error("Label '" + label + "' not found in JSON.");
    }

    // Return string representation based on type
    if (j[label].is_string()) {
        return j[label].get<std::string>();
    } else {
        return j[label].dump(); // Convert numbers, objects, arrays, etc. to string
    }
}