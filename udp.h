#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<strings.h>

#include "error.h"

#define CONNECTED 1
#define DISCONNECTED 0
#define LOGGED 1;
#define UNLOGGED 0;

type struct data 
{
  uint16_t mesgType;
  unsigned char status;
  unsigned char second;
  unsigned char minute;
  unsigned char hour;
  unsigned char day;
  unsigned char month;
  uint32_t year;
  unsigned char[4] timezone;
}binarydata; 


typedef struct sockaddr_in SA;


int Socket( int family, int type, int protocol);

ssize_t send( int fd, void *data, size_t size, int connected,
             const struct sockaddr *servaddr, socklen_t addrlen,
             int logged, char* logname );

int Read( int sockfd, void *data, size_t size, int logged, char* logname);






