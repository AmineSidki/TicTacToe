#include "server.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

struct sockaddr_in server_address(int port)
{
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    return address;
}


void server_socket(struct sockaddr_in address, int *_socket)
{
    int opt = 1;

    // Creating socket file descriptor
    if ((*_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(*_socket, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    

    // Forcefully attaching socket to the port 8080
    if (bind(*_socket, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

void server_listen(struct sockaddr_in address, int *_socket, int *new_socket)
{
    socklen_t addrlen = sizeof(address);

    if (listen(*_socket, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    if ((*new_socket = accept(*_socket, (struct sockaddr*) &address, &addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
}