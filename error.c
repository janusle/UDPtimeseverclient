#include "error.h"

void 
err_quit(char *st, bool u)
{
  fprintf(stderr, "%s\n", st);
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
