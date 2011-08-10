#include "error.h"

void 
err_quit(bool u)
{
  
  perror("");
  if( u )
  {
    usage();
  }

  exit(-1);
}

void 
usage()
{
  fprintf(stderr, "Usage: gethttp URL filename\n"); 
}
