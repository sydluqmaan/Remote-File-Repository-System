#include <vector>
#include <string>
#include "cli.h"
#include "authentication.h"
#include "networking.h"
#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H


class CommandHandler {

    public:
        CommandHandler();
        void handle(std::vector<std::string> args, int argumentCount);

    private:
        Cli cli;
        Networking networking;
        Authentication authentication;
};

#endif
