#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int VERSION = 0;

unsigned short PORT = 8080;
char* homeDir = "/var/www/html";

int init(int argc, char* argv[])
{
    if(!argc) return -1; // No arguments found

    // Go through every argument
    for(int i = 0; i < argc; i++)
    {
        // Single arguments
        if(strcmp(argv[i], "--help") == 0)
        {
            printf("Web server v%d\n\n", VERSION);
            printf("Arguments:\n");
            printf(" --port PORT\n");
            printf("\tSpecify the port number. Some may require root access.\n");
            printf(" --help\n");
            printf("\tShow help message.\n");
            return 0;
        }

        // Arguments with value specification
        if(strcmp(argv[i], "--port") == 0 && i+1 < argc)
        {
            PORT = atoi(argv[++i]);
        }
    }
    // Final checks
    // if(PORT < 65)

    return 1;
}

/*
- global variables/Server struct
- parameters from CLI or file processing
- request building functions
- request parsing functions
*/

int main(int argc, char* argv[])
{
    int statusCode = init(argc, argv);
    if(statusCode < 0) return statusCode;


    // struct sockaddr_in server_addr;   
    int listener_fd;
    struct addrinfo hints, *res;
    //int addrlen = sizeof(server_addr);

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;              // IPv4 
    hints.ai_socktype = SOCK_STREAM;        // TCP socket
    hints.ai_flags = AI_PASSIVE;            // Use my IP address

    char portStr[6];
    sprintf(portStr, "%d", PORT);

    int error;
    if ((error = getaddrinfo("localhost", portStr, &hints, &res)) != 0)
    {
        perror("Watafuck: ");
        exit(1);
    }

    for (struct addrinfo *p = res; p != NULL; p = p->ai_next)
    {
        listener_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (listener_fd < 0)
        {
            perror("Socket creation failed");
            continue;
        }

        if (bind(listener_fd, p->ai_addr, p->ai_addrlen) < 0)
        {
            close(listener_fd);
            continue;
        }
    }
    
    return 0;
}