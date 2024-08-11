#include <cstring> 
#include <string>
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>

#include "terminal.h"

// pre-def
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

    char currDir[PATH_MAX];

    // loop for more input
    while (true) {

        memset(buffer, 0, sizeof(buffer));
        ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);

        // want to have a skip-line possibility later on...

        // read and output data
        if (bytesReceived > 0) {

            buffer[bytesReceived] = '\0'; // null terminate for safe string command
            std::string commandInput {buffer};

            // move client here to quit early
            if (commandInput == "QUIT") {
                std::cout << "Closing simulated terminal.";
                break;
            }

            // will have to return str or char later so I can send results back to client (for visualization purposes)
            interactWithTerminal_OG(commandInput, currDir);

            // send(clientSocket, result.c_str(), result.size(), 0);
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

    while (!shutdownServer) {

        // accept a client
        int clientSocket = accept(serverSocket, nullptr, nullptr);

        // do something
        connectionActivity(clientSocket);

        close(clientSocket);
        shutdownServer = true;
        
    }

    // close sockets
    close(serverSocket);

    return 0;
}
