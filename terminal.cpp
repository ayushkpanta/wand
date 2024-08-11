
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <limits.h>
#include <vector>

// changes cwd for cd commands
void cdCommand(std::string commandInput) {

    std::string newDir {};
    newDir = (commandInput.length() == 2) ? getenv("HOME") : commandInput.substr(3);
    chdir(newDir.c_str());

}

void interactWithTerminal_OG(std::string commandInput, char* currDir) {

    std::cout << "Simulated Terminal:\n";

    // getcwd(currDir, sizeof(currDir));
    std::cout << currDir << " $ ";

    const char* sysCommand {commandInput.c_str()};
    system(sysCommand);

}

