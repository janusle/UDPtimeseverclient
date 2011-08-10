#include "udp.h"
#include "error.h"

extern int errno;


int 
Socket( int family, int type, int protocol )
{
  int sockfd;
  sockfd = socket( family, type, protocol );
  if( sockfd < 0 )
  {
     err_quit(false);
  }
  
  return sockfd;
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
clientinit( char* hostname , char* port ,SAI** sock_addr )
{
  struct addrinfo hints, *res;
  int sockfd;

  bzero(&hints, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;
  
  if( getaddrinfo( hostname, port, &hints, &res) != 0 )
  {
     err_quit(false);
  }

  *sock_addr = (SAI*)res->ai_addr;

  sockfd = Socket( AF_INET, SOCK_DGRAM, 0);
  
  return sockfd;

}


int 
senddata( int fd, void *data, size_t size ,
      const struct sockaddr *servaddr, socklen_t addrlen, int logged, char* logname  )
{
     FILE *lfd; 
     binarydata *ptr;

     ptr = (binarydata*)data;


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


int 
request( int sockfd, SAI* sock_addr, int connected, int logged, 
        char* logname)
{
   binarydata req;

   /* init request data */
   bzero( &req, sizeof(req) );
   req.mesgType = MAGICNUM;
   req.status = 0x52;
   memcpy( req.timezone, "AEST", TIMEZONELEN);
 

   return senddata( sockfd, &req, sizeof(req),  (SA*)sock_addr,
             sizeof(*sock_addr), logged, logname);



}


