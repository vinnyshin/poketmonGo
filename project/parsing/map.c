#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#define MAX_X 100
#define MAX_Y 15

#define MAP_MAX_X 30
#define MAP_MAX_Y 15


#define M_BOX_X_START 35
#define M_BOX_X_END 60


#define M_BOX_Y_START 0
#define M_BOX_Y_END 6

#define MSG_X_START (M_BOX_X_START + 2) 
#define MSG_Y_START (M_BOX_Y_START + 3)

#define P_MSG_X MSG_X_START
#define P_MSG_Y (MSG_Y_START + 5)


#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_LEFT 68
#define KEY_RIGHT 67

#define MONSTER_NUM 3
typedef struct unitP{
	int x;
	int y;
	char mark;
	char name[100];
}unitP;


unitP monster[MONSTER_NUM] = {{3,3,'@',"피카추"},{10,7,'#',"잠만보"},{20,10,'%',"끝판왕"}};


void gotoxy(int,int);

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

void clearGameMap(){

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

void makeBoundary(){

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


unitP I;
void printI(){
	gotoxy(I.x,I.y);
	printf("*");
	printXY(I.x,I.y);
	fflush(stdout);
}
void clearI(){
	gotoxy(I.x,I.y);
	printf(" ");
	fflush(stdout);
}


void setPositionI(int x, int y){
	I.x =x;
	I.y =y;
	printI();
}

void movePositionI(int x, int y){
	clearI();
	I.x = I.x + x;
	I.y = I.y + (-y);
	printI();
	fflush(stdout);
}

int checkMonster(){
	
	char msg[200]="";
	for(int i = 0; i < MONSTER_NUM ; i++){
		if((monster[i].x == I.x) && (monster[i].y == I.y)){
			sprintf(msg,"%s가 나타났다",monster[i].name);
			printGameMsg(msg);
			return 1;
		}

	}

}	


void move_R(){
	movePositionI(1,0);
	checkMonster();
}
void move_L(){
	movePositionI(-1,0);
	checkMonster();
}

void move_UP(){
	movePositionI(0,1);
	checkMonster();
}

void move_DOWN(){
	movePositionI(0,-1);
	checkMonster();
}


int getch()
{
	int c;
	struct termios oldattr, newattr;

	tcgetattr(STDIN_FILENO, &oldattr);           // 현재 터미널 설정 읽음
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);         // CANONICAL과 ECHO 끔
	newattr.c_cc[VMIN] = 1;                      // 최소 입력 문자 수를 1로 설정
	newattr.c_cc[VTIME] = 0;                     // 최소 읽기 대기 시간을 0으로 설정
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);  // 터미널에 설정 입력
	c = getchar();                               // 키보드 입력 읽음
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);  // 원래의 설정으로 복구
	return c;
}

void moveI(int key){
	
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
		case KEY_RIGHT : 
			move_R();
			break;

		default :
			break;
	}

}
int main(){

	clear();
	makeBoundary();
	makeMsgBox();
	printGameMsg("피카추가 등장");
	printXY(34234,23432);
	setPositionI(MAP_MAX_X/2 ,MAP_MAX_Y/2 );	
	printMonster();
	while(1){

		moveI(getch());

	}

	cursorReset();

	return 1;
}
