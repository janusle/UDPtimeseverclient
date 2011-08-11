#include "udp.h"
#include "error.h"


int 
main(int argc, char** argv)
{
  int sockfd;
  int temp;
  SAI* sock_addr;
  char test[16];
  binarydata re;
  
  if( argc < 2 )
  {
    fprintf(stderr, "Too few arguments\n");
    err_quit(true);
  }


  sockfd = clientinit( "goanna.cs.rmit.edu.au", "20201", &sock_addr );
 
  /*inet_ntop(AF_INET, &(sock_addr->sin_addr), test, 16);*/

  request( sockfd, sock_addr, LOGGED);
  temp = receive( sockfd, &re , LOGGED );

  
  return 0;
}
