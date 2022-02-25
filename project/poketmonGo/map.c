#include "map.h"

Position p;
Position monster[MONSTER_NUM] = {{3, 3, "PIKACHU", '$'}, {7, 7, "RAICHU", '#'}, {10, 10, "TTOGAS", '&' }};

void initMap() {
	clear();
	make_grid();
	print_message("Receiving GPS signal");
	setPosition(MAX_X / 2, MAX_Y / 2);
	print_monsters();

	while (1) {
		moveCursor(getch());
	}

	gotoxy(COMMAND_X, COMMAND_Y);
}

void gotoxy(int x, int y) {
	printf("\033[%d;%df",y,x);
	fflush(stdout);
}

void printPosition() {
	gotoxy(p.x, p.y);
	printf("*");
	fflush(stdout);
}

void clearPosition() {
	gotoxy(p.x, p.y);
	printf(" ");
	fflush(stdout);
}

int is_monster() {
	char msg[100];

	for(int i = 0; i < MONSTER_NUM; ++i) {
		if((monster[i].x == p.x) && (monster[i].y == p.y)) {
			sprintf(msg, "%s encountered", monster[i].name);
			print_message(msg);
			return 0;
		}
	}
}

void movePosition(int x, int y) {
	clearPosition();
	p.x = p.x + x;
	p.y = p.y + (-y);
	is_monster();
	printPosition();
	fflush(stdout);
}

void move_UP() {
	movePosition(0, 1);
}

void move_DOWN() {
	movePosition(0, -1);
}

void move_RIGHT() {
	movePosition(1, 0);
}

void move_LEFT() {
	movePosition(-1, 0);
}

void setPosition(int x, int y) {
	p.x = x;
	p.y = y;
	printPosition();
}

void make_grid() {
	int i;

	// Drawing left box
	for (i = 1; i <= MAX_Y; ++i) {
		gotoxy(1, i);
		printf("|");
	}

	for (i = 2; i < MAX_X; ++i) {
		gotoxy(i, 1);
		printf("=");
	}

	for(i = 1; i <= MAX_Y; ++i) {
		gotoxy(MAX_X, i);
		printf("|");
	}
	
	for(i = 2; i < MAX_X; ++i) {
		gotoxy(i, MAX_Y);
		printf("=");
	}
	
	// Drawing right box
	for (i = 1; i <= MAX_Y; ++i) {
		gotoxy(MAX_X + 1, i);
		printf("|");
	}
	
	for (i = MAX_X + 2; i < 2 * MAX_X; ++i) {
		gotoxy(i, 1);
		printf("=");
	}

	for(i = 1; i <= MAX_Y; ++i) {
		gotoxy(2 * MAX_X, i);
		printf("|");
	}

	for(i = MAX_X + 2; i < 2 * MAX_X; ++i) {
		gotoxy(i, MAX_Y);
		printf("=");
	}
}

void clear() {
	for(int i = 1; i <= 2 * MAX_X; ++i) {
		for(int j = 1; j <= MAX_Y; ++j) {
			gotoxy(j,i);
			printf(" "); 
		}
	}
}

void print_message(char* s) {
	printf("\033[%d;%df",2, MAX_X + 2);
	fflush(stdout);
	printf("%s\n", s);
}

void print_monsters() {
	Position temp;
	for(int i = 0; i < MONSTER_NUM; ++i) {
		temp = monster[i];
		gotoxy(temp.x, temp.y);
		printf("%c", temp.mark);
	}
}

void print_x_y(int x, int y) {
	gotoxy(POS_X, POS_Y);
	printf("                     ");
	gotoxy(POS_X, POS_Y);
	printf("[%d][%d]", x, y);
}

void print_GPS(int x, int y) {
	gotoxy(POS_X, POS_Y + 1);
	printf("                     ");
	gotoxy(POS_X, POS_Y + 1);
	printf("[%d][%d]", x, y);
}

int getch() {
	int c;
	struct termios oldattr, newattr;

	tcgetattr(STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);
	newattr.c_cc[VMIN] = 1;
	newattr.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
	c = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	return c;
}

void moveCursor(int key) {
	switch(key) {
		case KEY_UP:
			move_UP();
			break;
		case KEY_DOWN:
			move_DOWN();
			break;
		case KEY_RIGHT:
			move_RIGHT();
			break;
		case KEY_LEFT:
			move_LEFT();
			break;
		default:
			break;
	}
	print_x_y(p.x, p.y);
	print_GPS(3555,3555);
}

