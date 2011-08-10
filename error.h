#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<sys/errno.h>

/* print error msg to stderr, if u equals true then print usage as well*/
void err_quit(bool u);

/* print usage to stderr */
void usage();
