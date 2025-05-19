#include <crow.h>
#include <filesystem>
#include "fileInterface.h"


crow::response serve_file_chunked(const crow::request& req, crow::response& res) {
    if (!std::filesystem::exists(req.url_params.get("path"))) {
        return crow::response(404, "File/Directory does not exist");
    }

    const int fileSize = std::filesystem::file_size(req.url_params.get("path"));
}
