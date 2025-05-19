#ifndef NETWORKING_H
#define NETWORKING_H
#include <crow.h>
#include <nlohmann/json.hpp>

class networking {
public:
    networking();
    crow::response login(crow::request req);
    crow::response list(crow::request req);
    crow::response download(crow::request req);
    nlohmann::ordered_json directoryToJson(const std::filesystem::path& path_str);
};



#endif //NETWORKING_H
