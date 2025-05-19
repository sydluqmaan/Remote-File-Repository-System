#include "networking.h"
#include <curl/curl.h>
#include <string>
#include <iostream>


Networking::Networking() {
    curl = curl_easy_init();
}

static size_t WriteCallback(char *contents, size_t size, size_t nmemb, std::string *output) {
    size_t totalSize = size * nmemb;
    output->append(contents, totalSize);
    return totalSize;
}

std::string Networking::sendMessage(const std::string& method, const std::string& url, const std::string& jsonData, bool token) {

    std::string response;

    if (!curl) {
        throw std::runtime_error("CURL not initialized");
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method.c_str());

    // if (token) {
    //     curl_easy_setopt(curl, CURLOPT_HTTPHEADER, "Authorization: Bearer YOUR_TOKEN_HERE");
    // }

    if (jsonData.size() > 0) {
        // curl_easy_setopt(curl, CURLOPT_HTTPHEADER, "Content-Type: application/json"); #todo: server must accept content type
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
    }

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode result = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    return response;
}
