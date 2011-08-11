#include "udp.h"
#include "error.h"


int 
main(int argc, char** argv)
{
  
  if( argc < 2 )
  {
    fprintf(stderr, "Too few arguments\n");
    err_quit(true);
  }


 
  /*inet_ntop(AF_INET, &(sock_addr->sin_addr), test, 16);*/

  do_udp( "goanna.cs.rmit.edu.au", "20201", LOGGED, 3 );
  
  return 0;
}
