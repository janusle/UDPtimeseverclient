#include "udp.h"
#include "error.h"


int 
main(int argc, char** argv)
{
  int sockfd;
  int temp;
  SAI* sock_addr;
  
  if( argc < 2 )
  {
    fprintf(stderr, "Too few arguments\n");
    err_quit(true);
  }


  sockfd = clientinit( "goanna.cs.rmit.edu.au", "20201", &sock_addr );
 
  /*inet_ntop(AF_INET, &(sock_addr->sin_addr), test, 16);*/

  request( sockfd, sock_addr, LOGGED);
  temp = getreply( sockfd, LOGGED, 3);

  
  return 0;
}
