#include "file_stream.h"

int getGPSInfo() {
	FILE* fp =  fopen(FILE_NAME, "r");
	char buf[100];
	int is_gpgga;
	char temp[20][200];
	int count = 0;
	char x[100];
	char y[100];
	char* location;
	char* result;

	while(1) {
		result = fgets(buf, 100, fp);
		if (result == NULL) {
			break;
		}

		is_gpgga = strncmp(buf, "$GPGGA", 6);
		
		if (is_gpgga == 0) {
			count = 0;
			location = strtok(buf, ",");
			
			strcpy(temp[count++], location);
			while(1) {
				location = strtok(NULL, ",");
				if (location == NULL) {
					break;
				}
				strcpy(temp[count++], location);
			}
			if (count > 7) {
				strcpy(x, temp[2]);
				strcpy(y, temp[4]);
			}
			printf("x: %s y: %s\n", x, y);
			*xp = atoi(x);
			*yp = atoi(y);
		}
	}
	fclose(fp);
	return 0;
}
