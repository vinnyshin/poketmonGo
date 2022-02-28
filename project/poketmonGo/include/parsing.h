#ifndef __PARSING_H__
#define __PARSING_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME "./gpsInfo.txt"

int getGPSInfo(char * src,int * x, int * y);
FILE * initFile();
void deinitFile();

#endif
