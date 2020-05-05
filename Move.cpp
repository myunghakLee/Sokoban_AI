#include "AutoMove.h"

#define AISPEED 60000


bool Move::move(int y, int x) {
	int MyAround = Map[MyPositionY + y][MyPositionX + x];					//�� �����¿� �� �ϳ�
	int MyAroundAround = Map[MyPositionY + (2 * y)][MyPositionX + (2 * x)]; //�� �����¿� �� 2ĭ �� �� �� �ϳ�
	if (IsWall(MyAround)) {
		return false;
	}
	else if (IsBox(MyAround) || IsBoxInDestination(MyAround)) {
		if (IsDestination(MyAroundAround) || IsEmpty(MyAroundAround)) {
			Map[MyPositionY + (2 * y)][MyPositionX + (2 * x)] += _BOX;
			Map[MyPositionY + y][MyPositionX + x] += (_ME - _BOX);
			Map[MyPositionY][MyPositionX] -= _ME;
			return true;
		}
		else {
			return false;
		}
	}
	else if (IsEmpty(MyAround)) {
		Map[MyPositionY + y][MyPositionX + x] += _ME;
		Map[MyPositionY][MyPositionX] -= _ME;
		return true;
	}
	else if (IsDestination(MyAround)) {
		Map[MyPositionY + y][MyPositionX + x] += _ME;
		Map[MyPositionY][MyPositionX] -= _ME;
		return true;
	}

	return false;
}
void Move::moveLeft() {
	if (move(0, -1)) {
		MyPositionX--;
		move_count++;
	}
}
void Move::moveRight() {
	if (move(0, 1)) {
		MyPositionX++;
		move_count++;
	}
}
void Move::moveUp() {
	if (move(-1, 0)) {
		MyPositionY--;
		move_count++;
	}
}
void Move::moveDown() {
	if (move(1, 0)) {
		MyPositionY++;
		move_count++;
	}
}
bool Move::IsWall(int num) {
	if (num == _WALL) { return true; }
	return false;
}
bool Move::IsBox(int num) {
	if (num == _BOX) { return true; }
	return false;
}
bool Move::IsEmpty(int num) {
	if (num == _EMPTY) { return true; }
	return false;
}
bool Move::IsDestination(int num) {
	if (num == _DESTINATION) { return true; }
	return false;
}
bool Move::IsBoxInDestination(int num) {
	if (num == _BOXinDESTINATION) { return true; }
	return false;
}
void Move::DeleteMap() {
	for (int i = 0; i < height; i++) {
		delete[]Map[i];
	}
	delete[]Map;
}
void Move::PrintMap() {
	int t1 = 5;
	int t = 15;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if(Map[i][j] == _EMPTY){mvprintw(i+t1,j*2+t,"□ ");}
			//else if(Map[i][j] == _OUTSIDE){printw("□ "); }
			else if(Map[i][j] == _WALL){mvprintw(i+t1,j*2+t,"■ ");}
			else if(Map[i][j] == _BOX){mvprintw(i+t1,j*2+t,"● ");}
			else if(Map[i][j] == _DESTINATION){attron(COLOR_PAIR(2)); mvprintw(i+t1,j*2+t,"☆ "); attroff(COLOR_PAIR(2));}
			else if(Map[i][j] == _BOXinDESTINATION){attron(COLOR_PAIR(2));mvprintw(i+t1,j*2+t,"★ "); attroff(COLOR_PAIR(2));}
			else if(Map[i][j] == _ME){attron(COLOR_PAIR(3)); mvprintw(i+t1,j*2+t,"◈ "); attroff(COLOR_PAIR(2));}
			else if(Map[i][j] == _MEinDESTINATION){attron(COLOR_PAIR(3)); mvprintw(i+t1,j*2+t,"◈ "); attroff(COLOR_PAIR(2));}
		}
		printw("\n");
	}

	// printw(" X : %d\n", MyPositionX);
	// printw(" Y : %d\n", MyPositionY);
	// printw("move : %d\n", move_count);
}
bool Move::IsSuccess() {
	int Snum = 0;
	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			if (Map[i][j] == _BOXinDESTINATION) {
				Snum++;
			}
		}
	}
	if (Snum == NumDestinations) { return true; }
	else { return false; }
}

int Move::GetMyPositionX(){return MyPositionX;}
int Move::GetMyPositionY(){return MyPositionY;}
int Move::GetMoveCount(){return move_count;}

string Move::AutoGamming(WINDOW* win) {

	//int* MapCopy = new int(height * width);
	
	AutoMove AI(this);
	double SolveTime = 0;
	time_t startT, endT;
	startT = clock();
	string str = AI.solve();
	endT = clock();
	SolveTime = double(endT - startT);
	wattron(win, COLOR_PAIR(3));
	mvwprintw(win, 8, 2,"Time : %.6f",SolveTime/1000000);
	wattroff(win, COLOR_PAIR(3));
	wrefresh(win);
	mvprintw(20,7,"Answer : "); 
	int end_line = -1;
	for(int i =0; i<str.length(); i++){
		
		if(i%40== 0){
			end_line++;
		}
		mvprintw(20 + end_line, 16 + i - 40*end_line, "%c", str[i]);
	}
	mvwprintw(win, 8, 2,"                   ");
	
	//printw("\n");
	mvprintw(19,14,"move : %d", str.length());
	attron(COLOR_PAIR(3));
	mvprintw(17, 14, "Press 'd' to Auto start !		");
	attroff(COLOR_PAIR(3));
	refresh();

	char key;
	do{
		key = getch();
	}while(key !='d' && key !='D');

	for(int i = 0; i< str.length(); i++){
		usleep(AISPEED);
		if(str[i] == 'L' || str[i] == 'l'){
			moveLeft();
		}	
		else if(str[i] == 'r' || str[i] == 'R'){
			moveRight();
		}	
		else if(str[i] == 'u' || str[i] == 'U'){
			moveUp();
		}	
		else if(str[i] == 'd' || str[i] == 'D'){
			moveDown();
		}	
		clear();
		attron(COLOR_PAIR(7));
		mvprintw(3,20,"STAGE AUTO\n");
		attroff(COLOR_PAIR(7));
		PrintMap();
		mvprintw(10,40,"move : %d", str.length());
		//printw("press key to move player\n");
		//printw("w - UP  s - DOWN  a - LEFT  d - RIGHT\n");
		refresh();

	}

	return str;
}