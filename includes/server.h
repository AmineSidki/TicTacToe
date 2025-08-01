#pragma once
#include <netinet/in.h>


/**
 * This function creates an address
 * @param port The port in which the server listen
 */
struct sockaddr_in server_address(int port);


/**
 * This function creates a socket, and binds it and performs errors checks
 * @param address the socket's address
 * @param _socket the pointer that holds the return value of the function
 */
void server_socket(struct sockaddr_in address, int *_socket);

/**
 * This function makes the server listen
 * @param address the server's address
 * @param _socket the server's socket
 * @param new_socket the variable that holds the new socket
 */
void server_listen(struct sockaddr_in address, int *_socket, int *new_socket);

