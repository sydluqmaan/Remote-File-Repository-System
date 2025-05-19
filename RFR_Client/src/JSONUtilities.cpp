#include "JSONUtilities.h"

std::string JSONUtilities::convertToJSON(std::vector<std::string> keys, std::vector<std::string> values) {
    std::string result = "{";
    for (size_t i = 0; i < keys.size(); ++i) {
        result += "\"" + keys[i] + "\":\"" + values[i] + "\"";
        if (i < keys.size() - 1) {
            result += ",";
        }
    }
    result += "}";
    return result;
}
