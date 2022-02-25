#include "parsing.h"

FILE * g_fd;
FILE * initFile(){
	
	g_fd = fopen(FILE_NAME,"r");
	return g_fd;
}

void deinitFile(){
	fclose(g_fd);
}

int getGPSInfo(char * src,int * x, int * y){

	char * location_s;
	char temp[20][200];
	int count = 0;
	char s_x[100];
	char s_y[100];
	
	if(!strncmp(src,"$GPGGA",(unsigned int)6)){

		location_s = strtok(src,",");

		strcpy(temp[count++],location_s);

		while(1){


			location_s = strtok(NULL,",");
			if(location_s==NULL){
				break;
			}
			strcpy(temp[count++],location_s);
		}
		if(count > 7){
			strcpy(s_x,temp[2]);
			strcpy(s_y,temp[4]);
			*x = atoi(&s_x[5]);
			*y = atoi(&s_y[6]);
			return 1;
		}

	}


	return 0;
}
