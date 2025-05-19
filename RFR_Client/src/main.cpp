#include <iostream>
#include <string>
#include <vector>
#include "CommandHandler.h"

int main(int argc, char* argv[]) {

    SetConsoleOutputCP(CP_UTF8);

    SetConsoleCP(CP_UTF8);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    CommandHandler cmdHandler;

    std::vector<std::string> args(argv, argv + argc);

    cmdHandler.handle(args, argc);
    while (true) {
        continue;
    }
    return 0;
}
