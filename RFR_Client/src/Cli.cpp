#include "../include/Cli.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>
#include <nlohmann/json.hpp>


std::string Cli::stringInputprompt(std::string prompt) {
    std::cout << prompt;

    std::string input;
    std::getline(std::cin, input);

    return input;
}

bool Cli::yesNoPrompt() {
    while (true) {
        std::string response;
        std::cin >> response;
        if (response == "y") {
            return true;
        }
        else if (response == "n") {
            return false;
        }
        else {
            std::cout << "Invalid input" << std::endl;
        }
    }
}

void Cli::printHelp() {
    std::ifstream inputFile("D:/Projects/RFR_CLIENT/src/help.txt");     // TODO: fix path
    std::string line;

    if (inputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            std::cout << convertEscapes(line) << std::endl;
        }

        while (true) {  // TODO: remove
            continue;
        }

        inputFile.close();  // Close the file
    }
    else {
        std::cerr << "unable to load command list" << std::endl;
    }
}

std::string Cli::convertEscapes(const std::string& input) {
    std::string output;
    size_t pos = 0, prev = 0;
    while ((pos = input.find("\\033", prev)) != std::string::npos) {
        output.append(input.substr(prev, pos - prev));
        output.push_back('\033');
        prev = pos + 4;
    }
    output.append(input.substr(prev));
    return output;
}

void Cli::printDirectoryTree(const nlohmann::json& node, std::vector<bool> lastAncestors, bool isRoot) {
    std::string indent;

    for (size_t i = 0; i + 1 < lastAncestors.size(); ++i) {
        indent += lastAncestors[i] ? "    " : "│   ";
    }

    if (isRoot) {
        std::cout << node["name"].get<std::string>() << "\n";
    }
    else {
        bool isDir = node["type"] == "directory";
        std::string branch = lastAncestors.back() ? "└── " : "├── ";
        std::string name = node["name"].get<std::string>();
        if (isDir) {
            name = "\033[36m" + name + "\033[0m";  // Cyan for directories
        }
        std::cout << indent << branch << name << "\n";
    }

    if (node.contains("children") && node["children"].is_array()) {
        const auto& children = node["children"];
        for (size_t i = 0; i < children.size(); ++i) {
            bool isLast = (i == children.size() - 1);
            auto newAncestors = lastAncestors;
            newAncestors.push_back(isLast);
            printDirectoryTree(children[i], newAncestors, false);
        }
    }
}
