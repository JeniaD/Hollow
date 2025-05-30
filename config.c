#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned short PORT = 8080;
char HOMEDIR[256] = "/var/www/html";
const char* SERVNAME = "Hollow";
const int VERSION = 1;

int init(int argc, char* argv[]){
    if(!argc) return -1; // No arguments found

    // Go through every argument except the first one
    for(int i = 1; i < argc; i++){
        // Single arguments
        if(strcmp(argv[i], "--help") == 0){
            printf("Web server v%d\n\n", VERSION);
            printf("Arguments:\n");
            printf(" --port PORT\n");
            printf("\tSpecify the port number. Some may require root access.\n");
            printf(" --help\n");
            printf("\tShow help message.\n");
            return 0;
        }

        // Arguments with value specification
        if(strcmp(argv[i], "--port") == 0 && i+1 < argc){
            PORT = atoi(argv[++i]);
        }
        if (strcmp(argv[i], "--homedir") == 0 && i+1 < argc) {
            strncpy(HOMEDIR, argv[++i], sizeof(HOMEDIR));
            HOMEDIR[sizeof(HOMEDIR) - 1] = '\0'; // Ensure null-terminated
        }
    }
    // Final checks
    // if(PORT < 65)

    return 1;
}
