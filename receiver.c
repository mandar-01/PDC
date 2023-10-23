#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 8080

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server;
    char buffer[1024];

    // Create a socket for the server
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    // Bind the server socket
    if (bind(server_sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Binding failed");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_sock, 5) < 0) {
        perror("Listening failed");
        exit(1);
    }

    printf("Receiver is waiting for a connection...\n");
    
    // Accept the connection
    client_sock = accept(server_sock, NULL, NULL);

    // Receive data from the sender
    recv(client_sock, buffer, sizeof(buffer), 0);
    printf("Received message: %s\n", buffer);

    // Close the sockets
    close(client_sock);
    close(server_sock);
    
    return 0;
}
