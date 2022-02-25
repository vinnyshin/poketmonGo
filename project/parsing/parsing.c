#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME "./sample.txt"

int getGPSInfo(char * src,int * x, int * y);

int main(){

	FILE * fd;

	fd = fopen(FILE_NAME,"r");
	char * result;

	int x;
	int y;

	char buffer[500];
	while(1){
	 result = fgets(buffer,500,fd);
	
	 if(result == NULL){
		break;
	 }
		if(getGPSInfo(buffer,&x,&y)){

	 		printf("x : %d, y : %d\n",x,y);

		}
	}
	fclose(fd);
	return 1;
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
