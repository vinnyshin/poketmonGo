#include <stdio.h>


//$GPGGA,060256.00,3733.36221,N,12702.73218,E,1,04,13.18,27.0,M,18.6,M,,*57
#define FILE_NAME "./gpsInfo.txt"
#define STEP 700
int main(){

	char buff[500]="";
	int x = 36221;
	int y = 73218;

	FILE * fd;

	fd = fopen(FILE_NAME,"w");


	for(int i=0; i<10 ; i++){
		x = x + STEP;
	sprintf(buff,"$GPGGA,060256.00,3733.%d,N,12702.%d,E,1,04,13.18,27.0,M,18.6,M,,*57\n",y,x);

	fprintf(fd,"%s",buff);

	}



	for(int i=0; i<3 ; i++){
		y = y + STEP;
	sprintf(buff,"$GPGGA,060256.00,3733.%d,N,12702.%d,E,1,04,13.18,27.0,M,18.6,M,,*57\n",y,x);

	fprintf(fd,"%s",buff);

	}

	for(int i=0; i<20 ; i++){
		x = x - STEP;
	sprintf(buff,"$GPGGA,060256.00,3733.%d,N,12702.%d,E,1,04,13.18,27.0,M,18.6,M,,*57\n",y,x);

	fprintf(fd,"%s",buff);

	}

	for(int i=0; i<5 ; i++){
		y = y + STEP;
	sprintf(buff,"$GPGGA,060256.00,3733.%d,N,12702.%d,E,1,04,13.18,27.0,M,18.6,M,,*57\n",y,x);

	fprintf(fd,"%s",buff);

	}

fclose(fd);

}
