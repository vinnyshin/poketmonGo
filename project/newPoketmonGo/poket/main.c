#include <stdio.h>
#include "map.h"
#include "parsing.h"
#include "uart.h"

#define GAP 600

int main(){

	char buffer[500];
	char * result;

	initMap();
	cursorReset();

#ifdef FILE_MODE
	FILE * fd = initFile();
#else
	int fd = initUart();
#endif

	int x=0;
	int y=0;
	int old_x=0;
	int old_y=0;
	int first=1;

	while(1){
#ifdef FILE_MODE
		result = fgets(buffer,500,fd);
		if(result == NULL) {
			break;
		}
#else
		int uart_result = uart_gets(fd, buffer);
		if(uart_result <= 0) {
			printGameMsg("receiving GPS...");
			close(fd);
			fd = initUart();
			continue;
		}
#endif	
		
		if(getGPSInfo(buffer,&y,&x)){
			printGPSXY(x,y);
			if(first) {
				old_x = x;
				old_y = y;
				first = 0;
				printGameMsg("GPS ON");
			} else {
				int diff_x = x - old_x;
				int diff_y = y - old_y;
				
				if(diff_x >= GAP) {
					move_R();
					old_x = x;
				}
				else if(diff_x <= -GAP) {
					move_L();
					old_x = x;
				}
				else if(diff_y >= GAP) {
					move_DOWN();
					old_y = y;
				}
				else if(diff_y <= -GAP) {
					move_UP();
					old_y = y;
				}
			}
		}
	}
#ifdef FILE_MODE
	deinitFile();
#else
	close(fd);
#endif

	return 1;
}
