#include "error.h"

void 
err_quit(bool u)
{
  
  perror("time-client");
  if( u )
  {
    usage();
  }

  exit(-1);
}

void 
usage()
{
  fprintf(stderr, "Usage: time-client configfile\n"); 
}
