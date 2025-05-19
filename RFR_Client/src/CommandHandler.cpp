#include "../include/CommandHandler.h"
#include <iostream>
#include <ostream>
#include <string>
#include "../include/Cli.h"
#include "authentication.h"
#include <dpapi.h>
#include <string>
#include "configInterface.h"

CommandHandler::CommandHandler()
    : networking(),
      cli(),
      authentication(networking)
{}

void CommandHandler::handle(std::vector<std::string> args, int argumentCount) {

    if (args[1] == "help") {
        cli.printHelp();
    }
    else {
        bool tokenStatus = authentication.checkLocalToken();

        if (!tokenStatus) {
            authentication.authenticate();
        }

        else if (args[1] == "ls") {
            std::string path = "http://localhost:18080/list?path=/";
            std::string response = networking.sendMessage("GET", path, "", false);
            nlohmann::json directoryJSON = nlohmann::json::parse(response);
            cli.printDirectoryTree(directoryJSON);
        }

        else if (args[1] == "cd") {
            std::string path = "http://localhost:18080/list?path=/";
            std::string response = networking.sendMessage("GET", path, "", false);
            nlohmann::json directoryJSON = nlohmann::json::parse(response);

            if (args[2] == ".."){

            }
            else {}
        }

        else if (args[1] == "dnld") {

            std::string finalPath;

            if (argumentCount == 3){
                finalPath = args[2];
                std::string path = "http://localhost:18080/download?path=/" + finalPath;
                std::string response = networking.sendMessage("GET", finalPath, "", false);
            }
            else{
                std::cout << "Usage: download <remote_path>" << std::endl;
            }
        }
    }
}
