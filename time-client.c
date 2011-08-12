#include "udp.h"
#include "error.h"
#include "confprocess.h"


int 
main(int argc, char** argv)
{
  char* config[CONFLEN]; 
  int i;

  if( argc < 2 )
  {
    fprintf(stderr, "Too few arguments\n");
    err_quit(true);
  }


  init( "client.config", config );
 


  /*
  for(i=0; i<CONFLEN; i++)
  {
    if( config[i] != NULL )
      printf("%s\n", config[i]);    
  }
  */
  /* for test */
  /* 
  tmp = explode( argv[1] );
  printf("%s\n%s\n", tmp[0], tmp[1]);
  */ 
  /*inet_ntop(AF_INET, &(sock_addr->sin_addr), test, 16);*/
   
   
  /*do_udp( "goanna.cs.rmit.edu.au", "20201", LOGGED, 3 );*/
  
  return 0;
}
