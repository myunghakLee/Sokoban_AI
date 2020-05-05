#pragma once
#include<iostream>
#include <ncursesw/ncurses.h>
#include <unistd.h>
#include <fstream>
#include<string>
using namespace std;

#define _EMPTY 0
#define _WALL 1
#define _BOX 2
#define _DESTINATION 3
#define _OUTSIDE 4
#define _BOXinDESTINATION 5
#define _ME 100
#define _MEinDESTINATION 103

#define _EMPTY_C ' '
#define _WALL_C '#'
#define _BOX_C '$'
#define _DESTINATION_C '.'
#define _OUTSIDE_C ' '
#define _BOXinDESTINATION_C ' '
#define _ME_C '@'
#define _MEinDESTINATION_C '@'

class Move {
private:
	int** Map;
	int MyPositionX;
	int MyPositionY;
	int height;
	int width;
	int NumDestinations; 																																																																	
	int move_count;
public:
	Move(int* arr, int h, int w) {
		height = h;
		width = w;
		NumDestinations = 0;
		move_count = 0;
		Map = new int* [height];
		for (int i = 0; i < height; i++) {
			Map[i] = new int[width];
		}
		int temp = 0;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (arr[temp] == _ME) {
					MyPositionX = j;
					MyPositionY = i;
				}
				else if (arr[temp] == _DESTINATION) {
					NumDestinations++;
				}
				Map[i][j] = arr[temp++];
			}
		}
	}
	bool move(int y, int x);
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	bool IsWall(int num);
	bool IsBox(int num);
	bool IsEmpty(int num);
	bool IsDestination(int num);
	bool IsBoxInDestination(int num);
	void DeleteMap();
	void PrintMap();
	bool IsSuccess();
	string AutoGamming(WINDOW* win);

	int GetMyPositionX();
	int GetMyPositionY();
	int GetMoveCount();

	friend class AutoMove;
};
