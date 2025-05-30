#ifndef CONFIG_H
#define CONFIG_H

#define RESPMAXSIZE 10000
extern unsigned short PORT;
extern char HOMEDIR[256];
extern const char* SERVNAME;
extern const int VERSION;

int init(int argc, char* argv[]);

#endif