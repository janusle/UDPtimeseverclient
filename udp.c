#include "udp.h"
#include "error.h"

int 
Socket( int family, int type, int protocol )
{
  int sockfd;
  sockfd = socket( family, type, protocol );
  if( sockfd < 0 )
  {
     err_quit("Socket error", false);
  }
  
  return sockfd;
}


void
Connect( int sockfd, const struct sockaddr *servaddr, socklen_t addrlen)
{
  if( connect( sockfd, (SA*)servaddr, addrlen ) == -1 )
  {
    err_quit("Connect error", false);   
  }
}


int 
Receive( int sockfd, void *data, size_t size, int logged, char* logname)
{
   FILE *lfd; 
   binarydata *ptr;
   int n;
   ptr = (binarydata*)data;

   n = read( sockfd, data, NUMOFBYTES );
   
   if( n != NUMOFBYTES )
      return FAILURE;

   if( ptr->mesgType != MAGICNUM  )    
      return FAILURE;  
  
   if( memcmp( (const char*)ptr->timezone, "AEST", TIMEZONELEN) != 0 )
      return FAILURE;

   return SUCCESS; 
}


int 
clientinit( char* hostname , char* port ,SA** sock_addr )
{
  struct addrinfo hints, *res;
  int sockfd;

  bzero(&hints, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;
  
  if( getaddrinfo( hostname, port, &hints, &res) != 0 )
  {
     err_quit("Address is invalid", false);
  }

  *sock_addr = res->ai_addr;

  sockfd = Socket( AF_INET, SOCK_DGRAM, 0);
  
  return sockfd;

}


int 
senddata( int fd, void *data, size_t size , int connected, 
      const struct sockaddr *servaddr, socklen_t addrlen, int logged, char* logname  )
{
     FILE *lfd; 
     binarydata *ptr;

     ptr = (binarydata*)data;

     if ( connected )
        Connect( fd, (SA*)servaddr, addrlen);

     if ( write( fd, data, NUMOFBYTES ) < (int)size )
     {
       return FAILURE; 
     }
 
     if( logged )
     {
       lfd = fopen(logname, "a");
       fprintf(lfd, "%x\n%c\n%c\n%c\n%c\n%c\n%c\n%d\n%s\n\n",
               ptr->mesgType, ptr->status, ptr->second,
               ptr->minute, ptr->hour, ptr->day, 
               ptr->month, ptr->year, ptr->timezone);
       fclose(lfd);

       /* for test */
       fprintf(stdout, "%x\n%c\n%c\n%c\n%c\n%c\n%c\n%d\n%s\n\n",
               ptr->mesgType, ptr->status, ptr->second,
               ptr->minute, ptr->hour, ptr->day, 
               ptr->month, ptr->year, ptr->timezone);
     }
  
     return 0;
}




