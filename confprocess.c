#include "confprocess.h"


char**
explode( char* line )
{
  static char* array[ARRAYLEN];
  
  array[0] = (char*)Malloc( sizeof(char) * LEN );
  array[1] = (char*)Malloc( sizeof(char) * LEN );

  strcpy(array[0], strtok( line, " " ));
  strcpy(array[1], strtok( NULL, " " ));

  return array;
}


void*
Malloc( size_t size )
{
  void *tmp;

  if( (tmp=malloc( size)) == NULL )
  {
     err_quit(false); 
  }
  
  return tmp;

}
