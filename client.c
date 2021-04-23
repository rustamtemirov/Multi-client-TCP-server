#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "functions.h"

int main()
{
    //create socket
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (network_socket == -1)
    {
        printf("Could not establish connection with remote socket \n\n");
        exit(-1);
    }

    // specify an address for the socket
    struct sockaddr_in server_address;
    memset(&server_address, '\0', sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(4444);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    int connection_status = connect(network_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    if (connection_status == -1)
    {
        printf("Could not establish connection with remote socket \n\n");
        exit(-1);
    }
    printf("Hello, please enter the text you want to reverse, or enter exit to close the program!\n");
    while (1)
    {
        printf("[YOU]: ");
        //Send the data to the server
        unsigned long int len_max = MAX;
        char *client_message = malloc(len_max);
        len_max = longScanf(client_message, len_max);
        sendAll(network_socket, client_message, len_max);
        free(client_message);

        //receive the data from the server
        unsigned long int currentSize = 100000;
        char *server_response = malloc(currentSize);
        recvAll(network_socket, server_response, currentSize);

        if (strcmp(server_response, "exit") == 0)
        {
            printf("Disconnected from server!\n");
            exit(-1);
        }

        printf("[SERVER]: %s\n", server_response);

        // freeing the space of text
        free(server_response);
    }

    // closing the socket
    close(network_socket);
    return 0;
}