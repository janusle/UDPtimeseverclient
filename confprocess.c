#include "confprocess.h"

char [ARRAYLEN][]
explode( char* line )
{
  static char array[ARRAYLEN][LEN];
   
  strcpy(array[0], strtok( line, " " ));
  strcpy(array[1], strtok( NULL, " " ));

  return array;
}

