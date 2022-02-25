#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	int fd;
	fd = open("/dev/ttyUSB0", O_RDONLY);
	char buf[100];

	while(1) {
		read(fd, buf, 100);
		printf("%s", buf);
		printf("==============================\n");
	}
	
	close(fd);
	return 0;
}

