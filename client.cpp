// C++ program to illustrate the client application in the 
// socket programming 
#include <cstring> 
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h>
// #include <boost/asio.hpp> 

// create, initialize, and connect a socket to an address
// this is almost identical to the initialization of the server socket
int initClientSocket(int port = 8080) {

    // create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // specify local address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET; // IPv4 family
    serverAddress.sin_port = htons(port); // port in network byte order
    serverAddress.sin_addr.s_addr = INADDR_ANY; // bind to all interfaces

    // connect socket to address
    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    return clientSocket;
}

// whatever activity the client may do
// keeping it simple for now
void clientActivity(int clientSocket) {
    
    // requests user input from console, sends to socket
    std::string userInput;

    // continuous
    while (true) {

        std::cout << "Enter a message to send to the server:\n";
        std::getline(std::cin, userInput);
        const char* sendableMessage = userInput.c_str(); 
        send(clientSocket, sendableMessage, strlen(sendableMessage), 0); 
        
        if (userInput == "QUIT") {
            std::cout << "Stopping client.\n";
            break;
        }
    }


}

int main() { 
    // init socket in main
    int clientSocket {initClientSocket()};

	// activity and sending to server
    clientActivity(clientSocket);

	// closing socket 
	close(clientSocket); 

	return 0; 
}
