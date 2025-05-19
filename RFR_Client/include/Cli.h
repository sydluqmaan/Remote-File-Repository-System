#ifndef CLI_H
#define CLI_H
#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>


class Cli {
    public:
        void printHelp();
        bool yesNoPrompt();
        std::string stringInputprompt(std::string prompt);
        void printDirectoryTree(const nlohmann::json& node, std::vector<bool> lastAncestors = {}, bool isRoot = true);


    private:
        std::string convertEscapes(const std::string& input);
};
#endif //CLI_H
