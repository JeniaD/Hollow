#include <stdlib.h>
#include "config.h"

void formulateResponse(char** response, int status, char* body){
    *response = malloc(RESPMAXSIZE);
    int contentSize = sizeof(body);
    snprintf(*response, sizeof(*response), "HTTP/1.1 %d", status);
}