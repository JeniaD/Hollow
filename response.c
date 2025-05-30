#include "config.h"

void formulateResponse(char** response, char* body){
    *response = malloc(RESPMAXSIZE);
    int contentSize = sizeof(body);
    
}