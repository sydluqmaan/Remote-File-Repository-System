#include "authentication.h"
#include <iostream>
#include "cli.h"
#include <vector>
#include "JSONUtilities.h"
#include "configInterface.h"

Authentication::Authentication(Networking networkingIn) {
    networking = networkingIn;
}

bool Authentication::checkLocalToken() {
    return true;
}

bool Authentication::authenticate() {

    Cli cli;
    JSONUtilities jsonUtilities;
    ConfigInterface configInterface;

    std::cout << "Authentication Required" << std::endl;
    std::string username =  cli.stringInputprompt("Username: ");
    std::string password =  cli.stringInputprompt("Password: ");

    std::vector<std::string> keys = {"username", "password"};
    std::vector<std::string> values = {username, password};

    std::string bodyContent = jsonUtilities.convertToJSON(keys, values);

    std::string response = networking.sendMessage("POST", "http://localhost:18080/login", bodyContent, false);
    configInterface.updateConfigFile("token", response);
    std::cout << "\033[32mAuthenticated Successfully\033[0m" << std::endl;

    return true;
}