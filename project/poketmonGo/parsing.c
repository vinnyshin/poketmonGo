#include "parsing.h"

FILE *initFile()
{
	FILE* fp = fopen(FILE_NAME, "r");
	return fp;
}

void deinitFile(FILE* fp)
{
	fclose(fp);
}

int getGPSInfo(char *src, int *x, int *y)
{

	char *location;
	char temp[32][256];
	int count = 0;
	char buf_x[64];
	char buf_y[64];
	int is_gagga = strncmp(src, "$GPGGA", (unsigned int)6);

	if (is_gagga == 0)
	{

		location = strtok(src, ",");

		strcpy(temp[count++], location);

		while (1)
		{

			location = strtok(NULL, ",");
			if (location == NULL)
			{
				break;
			}
			strcpy(temp[count++], location);
		}
		if (count > 7)
		{
			strcpy(buf_x, temp[2]);
			strcpy(buf_y, temp[4]);
			*x = atoi(&buf_x[5]);
			*y = atoi(&buf_y[6]);
			return 1;
		}
	}

	return 0;
}
