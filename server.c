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
    //defining the sockets
    int sockfd, ret;
    struct sockaddr_in server_address;

    socklen_t addr_size;
    int new_socket;
    struct sockaddr_in new_address;
    pid_t childpid;

    /// creating server socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("Couldn't establish the connection!\n");
        exit(-1);
    }
    printf("Server socket is created.\n");

    // define the server address
    memset(&server_address, '\0', sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(4444);
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");

    ret = bind(sockfd, (struct sockaddr *)&server_address, sizeof(server_address));
    if (ret == -1)
    {
        printf("Couldn't bind to the port!\n");
        exit(-1);
    }

    if (listen(sockfd, 10) == 0)
    {
        printf("Listening....\n");
    }

    while (1)
    {
        new_socket = accept(sockfd, (struct sockaddr *)&new_address, &addr_size);
        if (new_socket == -1)
        {
            printf("Could not accept the connection\n");
            exit(-1);
        }
        printf("Accepted connection from %s:%d\n", inet_ntoa(new_address.sin_addr), ntohs(new_address.sin_port));

        if ((childpid = fork()) == 0)
        {
            close(sockfd);
            while (1)
            {
                // while client doesnt send "exit", recieve and send reversed text
                int currentSize = 100000;
                char *string = malloc(currentSize);
                currentSize = recvAll(new_socket, string, currentSize);
                if (strcmp(string, "exit") == 0)
                {
                    printf("Disconnected from %s:%d\n", inet_ntoa(new_address.sin_addr), ntohs(new_address.sin_port));
                    sendAll(new_socket, string, currentSize);
                    break;
                }
                else
                {
                    reverse(string, currentSize);
                    sendAll(new_socket, string, currentSize);
                    printf("Reversed string sent to the client %s:%d\n", inet_ntoa(new_address.sin_addr), ntohs(new_address.sin_port));
                    free(string);
                }
            }
        }
    }
    close(new_socket);

    return 0;
}