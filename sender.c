#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int main() {
    int sock;
    struct sockaddr_in server;
    char message[] = "Hello Sockets";
    
    // Create a socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = INADDR_ANY;

    // Connect to the receiver
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connection failed");
        exit(1);
    }

    // Send the message
    send(sock, message, strlen(message), 0);
    printf("Message sent: %s\n", message);

    // Close the socket
    close(sock);
    return 0;
}
