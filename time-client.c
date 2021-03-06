#include "udp.h"
#include "error.h"
#include "confprocess.h"


int 
main(int argc, char** argv)
{
  char* config[CONFLEN]; 
  int logged, count, timeout, port;

  if( argc < 2 )
  {
    fprintf(stderr, "Too few arguments\n");
    err_quit(true);
  }


  init( argv[1], config );
  
  count = atoi(config[REQ_COUNT]);
  timeout = atoi(config[REQ_TIMEOUT]);
  port = atoi( config[SERVER_PORT] );

  if( port == 0 )
  {
     fprintf(stderr, "invalid port\n");
     exit(-1);
  }

  /* set default count if need */
  if( count == 0 )
    count = atoi(TIMES);



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
             count,
             timeout
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
             count,
             timeout
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
