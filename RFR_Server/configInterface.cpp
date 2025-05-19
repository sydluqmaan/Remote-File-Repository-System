#include "configInterface.h"
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>


std::string configInterface::readConfigFile(const std::string& label) {
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