#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/uio.h>
#include<unistd.h>
#include<strings.h>
#include<string.h>

#include "error.h"

#define CONNECTED 1
#define DISCONNECTED 0
#define LOGGED 1
#define UNLOGGED 0
#define NUMOFBYTES 17
#define SUCCESS 0
#define FAILURE -1
#define MAGICNUM 0xA3F0
#define REPLY 0xB4
#define REQUEST 0x52

typedef struct 
{
  uint16_t mesgType;
  unsigned char status;
  unsigned char second;
  unsigned char minute;
  unsigned char hour;
  unsigned char day;
  unsigned char month;
  uint32_t year;
  unsigned char timezone[5];
}binarydata; 


typedef struct sockaddr SA;


int Socket( int family, int type, int protocol);

ssize_t senddata( int fd, void *data, size_t size, int connected,
             const struct sockaddr *servaddr, socklen_t addrlen,
             int logged, char* logname );

int Read( int sockfd, void *data, size_t size, int logged, char* logname);






