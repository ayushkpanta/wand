#include <cstring> 
#include <string>
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>

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

    // read and output data
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Client Connection Established.\nMessage: " << buffer << '\n';

}

int main() {

    std::cout << "Starting server...\n";

    // init socket in main
    int serverSocket {initServerSocket()};
    
    // listen for prospective clients
    listen(serverSocket, 5);

    // accept a client
    int clientSocket = accept(serverSocket, nullptr, nullptr);

    // ha
    connectionActivity(clientSocket);

    // close sockets
    close(serverSocket);
    close(clientSocket);

    return 0;
}
