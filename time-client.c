#include "udp.h"
#include "error.h"


int 
main(int argc, char** argv)
{
  int sockfd;
  int temp;
  SAI* sock_addr;
  char test[16];
  char logname[20] = "reqlog";
  binarydata re;
  /*
  if( argc < 2 )
  {
    err_quit("Too few arguments", true);
  }
  */

  sockfd = clientinit( "goanna.cs.rmit.edu.au", "20201", &sock_addr );
 
  inet_ntop(AF_INET, &(sock_addr->sin_addr), test, 16);
  /*printf("%s\n" ,test);*/
  temp = request( sockfd, &sock_addr, LOGGED, logname);
  printf("%d\n", temp);
  //temp = Receive( sockfd, &re, sizeof(re), 0, "reclog");
  return 0;
}
