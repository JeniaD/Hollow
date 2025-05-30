#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "config.h"
#include "response.h"

int main(int argc, char* argv[])
{
    int statusCode = init(argc, argv);
    if(statusCode < 0) return statusCode;


    // struct sockaddr_in server_addr;   
    int listener_fd;
    struct addrinfo hints, *res;
    struct sockaddr_storage client_addr;
    //int addrlen = sizeof(server_addr);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;              // IPv4 
    hints.ai_socktype = SOCK_STREAM;        // TCP socket
    hints.ai_flags = AI_PASSIVE;            // Use my IP address

    char portStr[6];
    sprintf(portStr, "%d", PORT);

    int error;
    if ((error = getaddrinfo(NULL, portStr, &hints, &res)) != 0)
    {
        perror("Watafuck: ");
        exit(1);
    }

    // Create socket and bind it to the address
    int yes = 1;
    struct addrinfo *it = res;

    for (; it != NULL; it = it->ai_next)
    {
        listener_fd = socket(it->ai_family, it->ai_socktype, it->ai_protocol);
        if (listener_fd < 0)
        {
            continue;
        }

        setsockopt(listener_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if (bind(listener_fd, it->ai_addr, it->ai_addrlen) < 0)
        {
            close(listener_fd);
            continue;
        }

        break; // successfully bound
    }

    if (it == NULL)
    {
        fprintf(stderr, "Failed to bind socket\n");
        freeaddrinfo(res);
        exit(2);
    }

    // listen for incoming connections
    if (listen(listener_fd, 10) == -1)
    {
        perror("Listen failed");
        close(listener_fd);
        freeaddrinfo(res);
        exit(1);
    }

    // accept a connection
    socklen_t addr_len = sizeof(client_addr);
    int client_fd = accept(listener_fd, (struct sockaddr*)&client_addr, &addr_len);

    const char *http_response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Connection: close\r\n"
            "\r\n"
            "<html><body><h1>Hello from C Web Server!</h1></body></html>\r\n";

    // Send the http response to the client
    write(client_fd, http_response, strlen(http_response));
    printf("Client connected. Data sent\n");
    close(client_fd);
    printf("Client disconnected.\n");
    
    close(listener_fd);
    freeaddrinfo(res);
    
    return 0;
}