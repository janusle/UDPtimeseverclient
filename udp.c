#include "udp.h"
#include "error.h"

extern int errno;



static char*
getip( SAI* servaddr )
{
  static char st[TMPLEN];

  inet_ntop( AF_INET, &(servaddr->sin_addr), st, INET_ADDRSTRLEN );

  return st;

}


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
receive( int sockfd, void *data, SAI* sock_addr, int logged )
{
   FILE *lfd; 
   binarydata *ptr;
   int n, addrlen;

   ptr = (binarydata*)data;

   n = recvfrom( sockfd, data, NUMOFBYTES ,0 ,(SA*)sock_addr, &addrlen  );
 
   /* for test */
   /*
   printf("Recv: %d\n", n);
   */


   if( n != NUMOFBYTES )
      return FAILURE;

   if( ptr->mesgType != MAGICNUM  )    
      return FAILURE;  
  
   if( memcmp( (const char*)ptr->timezone, "AEST", TIMEZONELEN) != 0 )
      return FAILURE;

   if( logged )
   {
     lfd = fopen(RECVLOG, "a"); 


     fprintf(lfd, "%x\n%x\n%d\n%d\n%d\n%d\n%d\n%d\n%c%c%c%c\n",
             ptr->mesgType, ptr->status, ptr->second,
             ptr->minute, ptr->hour, ptr->day, 
             ptr->month, ptr->year, ptr->timezone[0],
             ptr->timezone[1], ptr->timezone[2],ptr->timezone[3]);

     /*for test*/
     /*
     printf("%x\n%x\n%d\n%d\n%d\n%d\n%d\n%d\n%c%c%c%c\n",
             ptr->mesgType, ptr->status, ptr->second,
             ptr->minute, ptr->hour, ptr->day, 
             ptr->month, ptr->year, ptr->timezone[0],
             ptr->timezone[1], ptr->timezone[2],ptr->timezone[3]);
     */
     fclose(lfd);
   }
   return SUCCESS; 
}


int getreply( int sockfd, int logged , int times)
{
   binarydata data; 
   int i;
   FILE *lfd;
   SAI *sock_addr;  
   
   sock_addr = (SAI*)malloc(sizeof(SAI));

   bzero( sock_addr, sizeof(SAI) );
   for(i=0; i<times; i++)
   {
     if( receive( sockfd, &data, sock_addr, logged ) == SUCCESS )
        break; 
   }

   if( i >= times )
    return FAILURE;

  
   
   /* log */
   lfd = fopen(RECVLOG, "a");
   fprintf(lfd,"timeclient: reply from %s:%d\n\n\n", getip(sock_addr),
             sock_addr->sin_port);
   fclose(lfd);
      
   fprintf(stdout,"timeclient: reply from %s:%d\n", getip(sock_addr),
             sock_addr->sin_port);


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
     /*for test*/

     ptr = (binarydata*)data;


     if ( (sendto( fd, data, NUMOFBYTES, 0, servaddr, addrlen ))  < size )
     {
       return FAILURE; 
     }

     /* for test 
     printf("Send: %d\n", n);
     */

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
       /*
       printf("Send data: \n");
       fprintf(stdout, "%x\n%x\n%d\n%d\n%d\n%d\n%d\n%d\n%c%c%c%c\n\n",
               ptr->mesgType, ptr->status, ptr->second,
               ptr->minute, ptr->hour, ptr->day, 
               ptr->month, ptr->year, ptr->timezone[0], ptr->timezone[1],
               ptr->timezone[2],ptr->timezone[3]);
       */
     }
  
     return SUCCESS;
}


int 
request( int sockfd, SAI* sock_addr, int logged )
{
   binarydata req;
   FILE *lfd;

   /* init request data */
   bzero( &req, sizeof(req) );
   req.mesgType = MAGICNUM;
   req.status = 0x52;
   memcpy( req.timezone, "AEST", TIMEZONELEN);
 

   fprintf(stdout,"timeclient: request to %s:%d\n", getip((SAI*)sock_addr),
             ((SAI*)sock_addr)->sin_port);


   lfd = fopen(SENDLOG, "a");
   fprintf(lfd, "timeclient: request to %s:%d\n", getip((SAI*)sock_addr),
               ((SAI*)sock_addr)->sin_port);

   fclose(lfd);
   return senddata( sockfd, &req, sizeof(req),  (SA*)sock_addr,
             sizeof(*sock_addr), logged);

}


