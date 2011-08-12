#include "udp.h"
#include "error.h"
#include "confprocess.h"


int 
main(int argc, char** argv)
{
  char* config[CONFLEN]; 
  int logged;

  if( argc < 2 )
  {
    fprintf(stderr, "Too few arguments\n");
    err_quit(true);
  }


  init( argv[1], config );
  if( config[SERVER_ADDRESS] != NULL &&
      config[SERVER_PORT] != NULL )
  {
     
     if( strcmp( config[PRINT_MSG], "ON" ) == 0)
        logged = LOGGED;
     else
        logged = UNLOGGED;

     do_udp( config[SERVER_ADDRESS], 
             config[SERVER_PORT],
             logged,
             atoi(config[REQ_COUNT]),
             atoi(config[REQ_TIMEOUT])
            );

  }
  else if( config[SERVER_NAME] != NULL &&
           config[SERVER_PORT] != NULL )
  {

     if( strcmp( config[PRINT_MSG], "ON" ) == 0)
        logged = LOGGED;
     else
        logged = UNLOGGED;

     do_udp( config[SERVER_NAME], 
             config[SERVER_PORT],
             logged,
             atoi(config[REQ_COUNT]),
             atoi(config[REQ_TIMEOUT])
            );

  }
  else
  {
    fprintf(stderr, "Bad format in config file\n");
    exit(-1);
  }
    
  


  /* for test */
  /* 
  tmp = explode( argv[1] );
  printf("%s\n%s\n", tmp[0], tmp[1]);
  */ 
  /*inet_ntop(AF_INET, &(sock_addr->sin_addr), test, 16);*/
   
   
  /*do_udp( "goanna.cs.rmit.edu.au", "20201", LOGGED, 3 );*/
  
  return 0;
}
