#ifndef CONFIGINTERFACE_H
#define CONFIGINTERFACE_H
#include <string>

class ConfigInterface {
    public:
    void updateConfigFile(std::string key, std::string value);
    std::string readConfigFile(const std::string& label);

};
#endif //CONFIGINTERFACE_H
