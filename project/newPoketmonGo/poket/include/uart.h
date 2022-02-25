#ifndef __UART_H__
#define __UART_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <termio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <time.h>
#include <syslog.h>
#include <sys/resource.h>
#include <net/if.h>

#define USB "/dev/ttyUSB0"

int read_with_timeout(int fd, char* buf, int buf_size, int timeout_ms);
int uart_gets(int fd, char* buf);
int initUart();

#endif
