#ifndef __MAP_H__
#define __MAP_H__

#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#define KEY_UP 65
#define KEY_DOWN 66
#define KEY_RIGHT 67
#define KEY_LEFT 68

#define MAX_X 48
#define MAX_Y 15

#define COMMAND_X 50
#define COMMAND_Y 25

#define POS_X MAX_X + 2
#define POS_Y 7
#define MONSTER_NUM 3

typedef struct Position {
	int x;
	int y;
	char name[100];
	char mark;
} Position;

void initMap();
void gotoxy(int x, int y);
void printPosition();
void clearPosition();
int is_monster();
void movePosition(int x, int y);
void move_UP();
void move_DOWN();
void move_RIGHT();
void move_LEFT();
void setPosition(int x, int y);
void make_grid();	
void clear();
void print_message(char* s);
void print_monsters();
void print_x_y(int x, int y);
void print_GPS(int x, int y);
int getch();	
void moveCursor(int key); 

#endif
