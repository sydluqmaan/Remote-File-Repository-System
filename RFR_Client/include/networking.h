#ifndef NETWORKING_H
#define NETWORKING_H
#include <curl/curl.h>
#include <string>

class Networking {
    public:
        Networking();
        std::string sendMessage(const std::string& method, const std::string& url, const std::string& jsonData = "", bool token = true);
    private:
        CURL *curl;
};

#endif //NETWORKING_H
