#include "networking.h"
#include <crow.h>
#include "authentication.h"
#include "configInterface.h"
#include <filesystem>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>


networking::networking() {

    crow::SimpleApp app;

    CROW_ROUTE(app, "/login").methods(crow::HTTPMethod::Post)([this](const crow::request& req){ return this -> login(req); });
    CROW_ROUTE(app, "/list").methods(crow::HTTPMethod::Get)([this](const crow::request& req){ return this -> list(req); });
    CROW_ROUTE(app, "/download").methods(crow::HTTPMethod::Get)([this](const crow::request& req){ return this -> download(req); });
    app.port(18080).multithreaded().run();
}

crow::response networking::login(crow::request req) {
    auto body = crow::json::load(req.body);
    if (!body) {
        return crow::response(400, "Invalid JSON");
    }

    std::string username = body["username"].s();
    std::string password = body["password"].s();

    if (username == "admin" && password == "admin") {
        authentication auth;
        crow::json::wvalue result;
        // result["token"] = auth.generateToken(username);
        return crow::response(auth.generateToken(username));
        // return crow::response{result};
    }
    else {
        return crow::response(400, "Invalid credentials");
    }

}

crow::response networking::list(crow::request req) {
    configInterface configInterface;
    std::string root = configInterface.readConfigFile("rootDirectory") + (req.url_params.get("path") == "/" ? "" : req.url_params.get("path"));
    std::string directoryJSON = directoryToJson(root).dump();

    return crow::response(directoryJSON);
}

crow::response networking::download(crow::request req) {
    configInterface configInterface;
    std::string fileName = req.url_params.get("path");
    std::string filePath = configInterface.readConfigFile("rootDirectory") + fileName;
    std::ifstream file(filePath, std::ios::binary);

    if (!file.is_open()) {
        return crow::response(404, filePath);
    }

    else {
        std::ostringstream fileData;
        fileData << file.rdbuf();

        crow::response res;
        res.set_header("Content-Type", "application/octet-stream");
        res.set_header("Content-Disposition", "attachment; filename=\"" + fileName + "\"");
        res.write(fileData.str());
        res.end();
        return res;
    }
}

nlohmann::ordered_json networking::directoryToJson(const std::filesystem::path& path_str) {
    std::filesystem::path path(path_str);
    nlohmann::ordered_json node;
    node["name"] = path.filename().string();
    if (node["name"] == "") {
        node["name"] = "root";
    }
    node["type"] = std::filesystem::is_directory(path) ? "directory" : "file";

    if (std::filesystem::is_directory(path)) {
        std::vector<std::pair<std::filesystem::directory_entry, std::filesystem::file_time_type>> entries;

        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            entries.emplace_back(entry, std::filesystem::last_write_time(entry));
        }

        // Sort by most recently modified
        std::sort(entries.begin(), entries.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

        node["children"] = nlohmann::ordered_json::array();
        for (const auto& [entry, _] : entries) {
            node["children"].push_back(directoryToJson(entry.path()));
        }
    }

    return node;
}