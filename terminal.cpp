
#include <iostream>
#include <string>
#include <cstdio>  // pipe
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h> // send()
#include <limits.h>
#include <vector>

// changes cwd for cd commands
void cdCommand(std::string commandInput) {

    std::string newDir {};
    newDir = (commandInput.length() == 2) ? getenv("HOME") : commandInput.substr(3);
    chdir(newDir.c_str());

}

// pointer instead of string copy
void interactWithTerminal_OG(std::string commandInput, int clientSocket) {



    // system(commandInput.c_str()); // if we just want to display locally


    // pipe for sending to client

    FILE* pipe = popen(commandInput.c_str(), "r");
    if (!pipe) {
        std::string errorMsg {"Failed to open pipe!"};
        send(clientSocket, errorMsg.c_str(), errorMsg.length(), 0);
        return;
    }

    char buffer[128];
    std::string result;
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }

    int returnCode {pclose(pipe)};

    if (returnCode != 0) {
        result += "Command failed. Return Code: " + std::to_string(returnCode) + '\n';
    }

    std::cout << result << std::endl;

    

    send(clientSocket, result.c_str(), result.length(), 0);
    // // // const char* sysCommand {commandInput.c_str()};
    // // // system(sysCommand);

}
