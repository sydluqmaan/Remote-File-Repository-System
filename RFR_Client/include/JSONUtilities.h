#include <string>
#include <vector>
#ifndef JSONUTILITIES_H
#define JSONUTILITIES_H


class JSONUtilities {
    public:
    std::string convertToJSON(std::vector<std::string> keys, std::vector<std::string> values);
};

#endif //JSONUTILITIES_H
