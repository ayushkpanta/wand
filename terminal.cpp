
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <limits.h>
#include <vector>

void cdCommand(std::string commandInput) {

    std::string newDir {};
    // conditional operator!
    newDir = (commandInput.length() == 2) ? getenv("HOME") : commandInput.substr(3);
    chdir(newDir.c_str());

}

void interactWithTerminal_TEST(std::string commandInput) {

    // std::string commandInput {command};
    // std::string currDir {};

    char currDir[PATH_MAX];

    std::cout << "Simulated Terminal (one command only):\n";

        // actual terminal execution
        const char* sysCommand {commandInput.c_str()};
        system(sysCommand);

    // return 0;
}


// needs to be cleaned up...
void interactWithTerminal_OG(std::string commandInput, char* currDir_temp) {

    // std::string commandInput {};
    // std::string currDir {};

    char currDir[PATH_MAX];

    // will have to move stuff out:
        // the currDir function (for persistence to calls)

    std::cout << "Simulated Terminal:\n";
    // while (true) {

        // print dir
        getcwd(currDir, sizeof(currDir));
        std::cout << currDir << " $ ";

        // get command -> pass it in instead
        // std::getline(std::cin >> std::ws, commandInput);

        // quit sim -> MOVED OUT
        // if (commandInput == "QUIT") {
        //     std::cout << "Quitting Simulated Terminal.\n";
        //     break;
        // }

        // handle cd
        if (commandInput.substr(0, 2) == "cd") {
            cdCommand(commandInput);
            // continue; // we skip usually
        }
        else {
            // actual other terminal execution
            const char* sysCommand {commandInput.c_str()};
            system(sysCommand);
        }



    // }

    // return 0;

}

