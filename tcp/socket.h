#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <time.h>

#define ERROR			-1
#define MAX_CLIENTS		2
#define MAX_DATA		1024
#define BUFFER			1024
#define EXIT 			"exit"


typedef struct sockaddr_in 	sa_in;
typedef struct sockaddr 	sa;