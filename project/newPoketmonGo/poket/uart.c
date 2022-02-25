#include "uart.h"

#define USB "/dev/ttyUSB0"

int read_with_timeout(int fd, char* buf, int buf_size, int timeout_ms) {
	int rx_len=0;
	struct timeval timeout;
	fd_set readFds;
	timeout.tv_sec = 0;
	timeout.tv_usec = timeout_ms*1000;

	FD_ZERO(&readFds);
	FD_SET(fd, &readFds);
	select(fd+1, &readFds, NULL, NULL, &timeout); // verifying file descriptor
	// did we received data or not
	// select will be returned after timeout ms;
	// we used select instead of non-blocking mode

	if(FD_ISSET(fd, &readFds)) {
		rx_len = read(fd,buf,buf_size);
	}
	return rx_len;
}

int uart_gets(int fd, char* buf) {
	char temp[10];
	int readNum=0;
	char returnStr[256] = "";
	int totalReadNum=0;
	while(1) {
		readNum = read_with_timeout(fd, temp, 1, 1000);
		if(readNum == 0) {
			printf("ERROR: readNum is 0");
			return -1;
		}
		if(readNum > 0) {
			returnStr[totalReadNum++] = temp[0];
			if(temp[0] == '\n') {
				break;
			}
		}
	}

	if(totalReadNum > 0) {
		strcpy(buf, returnStr);
	}
	return totalReadNum;
}

int initUart() {
	struct termio tdescript;
	struct termio tmLinOld;

	int fd = open(USB, O_RDWR);
	
	if(fd < 0) {
		printf("FILE OPEN ERROR");
		return -1;
	}

	if(!isatty(fd)) {
		printf("device is not in use");
	}

	ioctl(fd, TCGETA, &tdescript);
	ioctl(fd, TCGETA, &tmLinOld);
	
	tdescript.c_iflag = 0;
	tdescript.c_oflag = 0;
	tdescript.c_lflag = 0;
	
	tdescript.c_cflag &= ~CBAUD;
	tdescript.c_cflag |= B9600;
	tdescript.c_cc[VMIN] = 0;
	tdescript.c_cc[VTIME] = 1;
	
	return fd;
}


int no_main() {
	char buf[256];
	int fd = initUart();

	while(1) {
		if(uart_gets(fd, buf) > 0) {
			printf("%s", buf);
		} else {
			printf("error\n");
			close(fd);
			fd = initUart();
		}
	}

	return 0;
}

