#include <cstring> 
#include <string>
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>

#include "terminal.h"

// pre-def
void cdCommand(std::string commandInput);
void interactWithTerminal_TEST(std::string commandInput);

// create, initialize, and bind a socket to an address
int initServerSocket(int port = 8080) {

    // create socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // specify local address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET; // IPv4 family
    serverAddress.sin_port = htons(port); // port in network byte order
    serverAddress.sin_addr.s_addr = INADDR_ANY; // bind to all interfaces

    // bind socket to address
    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    return serverSocket;
}

void connectionActivity(int clientSocket) {

    // establishing max data (in bytes) to be read
    char buffer[1024]{0};

    // directory handling
    char currDir[PATH_MAX];

    // loop for cont. input
    while (true) {

        // reset buffer, get bytes
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

        // read and output data
        if (bytesReceived > 0) {

            buffer[bytesReceived] = '\0'; // null (safe string)
            std::string commandInput {buffer};

            // move client here to quit early
            if (commandInput == "QUIT") {
                std::cout << "Closing simulated terminal.";
                break;
            }
            else if (commandInput.substr(0, 2) == "cd") {
                cdCommand(commandInput);
                continue; // skip out of this part
            }

            // no return yet (return char* later for output to client)
            interactWithTerminal_OG(commandInput, currDir);
        }

    }

}

int main() {

    std::cout << "Starting server...\n";

    // init socket in main
    int serverSocket {initServerSocket()};
    
    // listen for prospective clients
    listen(serverSocket, 5);

    // temporary loop flag
    bool shutdownServer {false};

    // while server is not shutdown
    while (!shutdownServer) {

        // accept a client
        int clientSocket = accept(serverSocket, nullptr, nullptr);

        // do something
        connectionActivity(clientSocket);

        // close and shutdown server
        close(clientSocket);
        shutdownServer = true;
    }

    // close sockets
    close(serverSocket);

    return 0;
}
