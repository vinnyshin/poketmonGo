#include "map.h"

unitP monster[MONSTER_NUM] = {{3,3,'@',"피카추"},{10,7,'#',"잠만보"},{20,10,'%',"끝판왕"}};

unitP cursor;

void initMap(){
	clear();
	makeGrid();
	makeMsgBox();
	printGameMsg("GPS 정보 수신중");
	printMonster();
	printXY(MAP_MAX_X/2,MAP_MAX_Y/2);
	printGPSXY(99999,9999);
	setCursorPosition(MAP_MAX_X/2,MAP_MAX_Y/2);
	

}

void printMonster(){

	for(int i =0; i < MONSTER_NUM; i++){
		gotoxy(monster[i].x,monster[i].y);
		printf("%c",monster[i].mark);
	}

		fflush(stdin);
}

void cursorReset(){
	gotoxy(MAX_X,MAX_Y);
}

void printXY(int x, int y){
	gotoxy(P_MSG_X,P_MSG_Y);
	printf("               ");
	gotoxy(P_MSG_X,P_MSG_Y);
	printf("[%d][%d]",x,y);
	cursorReset();
}

void printGPSXY(int x, int y){
	gotoxy(P_GPS_MSG_X,P_GPS_MSG_Y);
	printf("               ");
	gotoxy(P_GPS_MSG_X,P_GPS_MSG_Y);
	printf("[%d][%d]",x,y);
	cursorReset();
}

void printGameMsg(char * str){
	gotoxy(MSG_X_START,MSG_Y_START);
	printf("               ");
	gotoxy(MSG_X_START,MSG_Y_START);
	printf("%s",str);
	cursorReset();
}

void gotoxy(int x, int y){

	printf("\033[%d;%df",y,x);
	fflush(stdout);
}

void clearGrid(){

	int x=2;
	int y=2;

	for(x = 2; x < MAP_MAX_X-1 ; x++){
		for(y =2; y < MAP_MAX_Y-1 ; y++){
			gotoxy(x,y);
			printf(" ");
		}
	}
}

void clear(){

	int x=0;
	int y=0;

	for(x = 0; x < MAX_X ; x++){
		for(y =0; y < MAX_Y ; y++){
			gotoxy(x,y);
			printf(" ");
		}
	}
}

void makeMsgBox(){

	int x=0;
	int y=0;

	for(y = M_BOX_Y_START ; y < M_BOX_Y_END ; y++){
		for(x = M_BOX_X_START; x < M_BOX_X_END ; x++){
			gotoxy(x,y);
			if(y==0){
			  printf("=");
			}
			else if(y==(M_BOX_Y_END-1)){
			  printf("=");
			}
			else if(x==M_BOX_X_START){
			  printf("|");
			}
			else if(x==(M_BOX_X_END-1)){
			  printf("|");
			}
		}
	}

	cursorReset();

}

void makeGrid(){

	int x=0;
	int y=0;

	for(y = 0; y < MAP_MAX_Y ; y++){
		for(x =0; x < MAP_MAX_X ; x++){
			gotoxy(x,y);
			if(y==0){
			  printf("=");
			}
			else if(y==(MAP_MAX_Y-1)){
			  printf("=");
			}
			else if(x==0){
			  printf("|");
			}
			else if(x==(MAP_MAX_X-1)){
			  printf("|");
			}
		}
	}
}

void printCursor(){
	gotoxy(cursor.x,cursor.y);
	printf("*");
	printXY(cursor.x,cursor.y);
	fflush(stdout);
}

void clearCursor(){
	gotoxy(cursor.x,cursor.y);
	printf(" ");
	fflush(stdout);
}

void setCursorPosition(int x, int y){
	cursor.x =x;
	cursor.y =y;
	printCursor();
}

void moveCursorXY(int x, int y){
	clearCursor();
	cursor.x = cursor.x + x;
	cursor.y = cursor.y + (-y);
	didEncounterMonster();
	printCursor();
	fflush(stdout);
}

int didEncounterMonster(){
	char msg[200]="";
	for(int i = 0; i < MONSTER_NUM ; i++){
		if((monster[i].x == cursor.x) && (monster[i].y == cursor.y)){
			sprintf(msg,"%s가 나타났다",monster[i].name);
			printGameMsg(msg);
			return 1;
		}
	}
}	

void move_R(){
	moveCursorXY(1,0);
}

void move_L(){
	moveCursorXY(-1,0);
}

void move_UP(){
	moveCursorXY(0,1);
}

void move_DOWN(){
	moveCursorXY(0,-1);
}

int getch()
{
	int c;
	struct termios oldattr, newattr;

	tcgetattr(STDcursorN_FcursorLENO, &oldattr);           // 현재 터미널 설정 읽음
	newattr = oldattr;
	newattr.c_lflag &= ~(cursorCANON | ECHO);         // CANONcursorCAL과 ECHO 끔
	newattr.c_cc[VMcursorN] = 1;                      // 최소 입력 문자 수를 1로 설정
	newattr.c_cc[VTcursorME] = 0;                     // 최소 읽기 대기 시간을 0으로 설정
	tcsetattr(STDcursorN_FcursorLENO, TCSANOW, &newattr);  // 터미널에 설정 입력
	c = getchar();                               // 키보드 입력 읽음
	tcsetattr(STDcursorN_FcursorLENO, TCSANOW, &oldattr);  // 원래의 설정으로 복구
	return c;
}

void moveCursor(int key){
	switch(key){
		case KEY_UP : 
			move_UP();
			break;
		case KEY_DOWN : 
			move_DOWN();
			break;
		case KEY_LEFT : 
			move_L();
			break;
		case KEY_RcursorGHT : 
			move_R();
			break;
		default :
			break;
	}
}
