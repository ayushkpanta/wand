
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

int main() {

    std::string commandInput {};
    // std::string currDir {};

    char currDir[PATH_MAX];

    std::cout << "Simulated Terminal:\n";
    while (true) {

        // print dir
        getcwd(currDir, sizeof(currDir));
        std::cout << currDir << " $ ";

        // get command
        std::getline(std::cin >> std::ws, commandInput);

        // quit sim
        if (commandInput == "QUIT") {
            std::cout << "Quitting Simulated Terminal.\n";
            break;
        }

        // handle cd
        if (commandInput.substr(0, 2) == "cd") {
            cdCommand(commandInput);
            continue;
        }

        // actual terminal execution
        const char* sysCommand {commandInput.c_str()};
        system(sysCommand);

    }

    return 0;

}
