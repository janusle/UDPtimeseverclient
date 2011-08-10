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
Receive( int sockfd, void *data, size_t size, 
         const struct sockaddr *servaddr, socklen_t addrlen,
         int logged )
{
   FILE *lfd; 
   binarydata *ptr;
   int n;
   ptr = (binarydata*)data;

   n = recvfrom( sockfd, data, NUMOFBYTES ,0 ,servaddr, &addrlen  );
   
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
senddata( int fd, void *data,int size ,
      const struct sockaddr *servaddr, socklen_t addrlen, int logged )
{
     FILE *lfd; 
     binarydata *ptr;

     ptr = (binarydata*)data;


     if ( sendto( fd, data, NUMOFBYTES, 0, servaddr, addrlen ) < (int)size )
     {
       return FAILURE; 
     }

     printf("%d\n", size);
     if( logged )
     {
       lfd = fopen(SENDLOG, "a");
       fprintf(lfd, "%x\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%c%c%c%c\n\n",
               ptr->mesgType, ptr->status, ptr->second,
               ptr->minute, ptr->hour, ptr->day, 
               ptr->month, ptr->year, ptr->timezone[0], ptr->timezone[1],
               ptr->timezone[2], ptr->timezone[3]);
       fclose(lfd);

       /* for test */
       fprintf(stdout, "%x\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%c%c%c%c\n\n",
               ptr->mesgType, ptr->status, ptr->second,
               ptr->minute, ptr->hour, ptr->day, 
               ptr->month, ptr->year, ptr->timezone[0], ptr->timezone[1],
               ptr->timezone[2],ptr->timezone[3]);
     }
  
     return SUCCESS;
}


int 
request( int sockfd, SAI* sock_addr, int connected, int logged )
{
   binarydata req;

   /* init request data */
   bzero( &req, sizeof(req) );
   req.mesgType = MAGICNUM;
   req.status = 0x52;
   memcpy( req.timezone, "AEST", TIMEZONELEN);
 

   return senddata( sockfd, &req, sizeof(req),  (SA*)sock_addr,
             sizeof(*sock_addr), logged);



}


