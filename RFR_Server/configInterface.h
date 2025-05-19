#include <string>

#ifndef CONFIGINTERFACE_H
#define CONFIGINTERFACE_H



class configInterface {
    public:
    std::string readConfigFile(const std::string& label);
};



#endif //CONFIGINTERFACE_H
