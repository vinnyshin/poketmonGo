#ifndef __MAP_H__
#define __MAP_H__

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

#define P_GPS_MSG_X MSG_X_START
#define P_GPS_MSG_Y (MSG_Y_START + 6)



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




void gotoxy(int,int);

void printMonster();

void cursorReset();

void printXY(int x, int y);

void printGPSXY(int x, int y);
void printGameMsg(char * str);
void gotoxy(int x, int y);
void clearGameMap();

void clear();
void makeMsgBox();

void makeBoundary();


void printI();
void clearI();
void setPositionI(int x, int y);
void movePositionI(int x, int y);
int checkMonster();

void move_R();
void move_L();
void move_UP();
void move_DOWN();
int getch();
void moveI(int key);

void initMap();
#endif
