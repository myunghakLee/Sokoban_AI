#include "AutoMove.h"
#include <queue>
#include <list>
#include <set>
#include <string.h>
double IsItInsideTime = 0;
double pushTime = 0;
double push_popTime = 0;
double copy_time = 0;
double allocate_time = 0;
double is_solve_time = 0;
double total_solve_time = 0;
double delete_time = 0;
double box_move_time = 0;
double empty_move_time = 0;
time_t start, endt;
time_t total_start, total_end;
time_t move_start, move_end;
set<string> visited;


void AutoMove::push(short int x, short int y, short int dx, short int dy) {
//	start = clock();
	if (mapData[(y + 2 * dy) * board_linenum + x + 2 * dx] == _WALL_C
 		|| current_objectData[(y + 2 * dy) * board_linenum + x + 2 * dx] != _EMPTY_C) {
		delete current_objectData;
		current_objectData = NULL;
//		endt = clock();
		pushTime += double(endt - start);
		return;
	}

	current_objectData[y * board_linenum + x] = _EMPTY_C;
	current_objectData[(y + dy) * board_linenum + x + dx] = _ME_C;
	current_objectData[(y + 2 * dy) * board_linenum + x + 2 * dx] = _BOX_C;
//	endt = clock();
	pushTime += double(endt - start);
}

bool AutoMove::IsSolved() {
//	start = clock();
	for (int i = 0; i < MapLength; i++) {
		if ((mapData[i] == _DESTINATION_C) != (current_objectData[i] == _BOX_C))
			return false;
	}
//	endt = clock();
	is_solve_time += double(endt - start);
	return true;
}

bool AutoMove ::IsItInside() {	
//	start = clock();


	set<string>::iterator iter = visited.find(current_objectData);
	if (iter != visited.end()) {
		return false;
	}
//	endt = clock();
	IsItInsideTime += double(endt - start);
	return true;
}

string AutoMove:: solve() {
//	total_start = clock();
//	SolverData* solver_queue = new SolverData(objectData, "", player_start_x, player_start_y);
	//queue<SolverData*> solver_queue;
	queue<char*> CobjectData;
	queue<string*>playerMove;
	queue<short int> DataX;
	queue<short int> DataY;
	string movestart = "";

//	solver_queue.push(new SolverData(objectData, &movestart, player_start_x, player_start_y));
	CobjectData.push(objectData);
	playerMove.push(&movestart);
	DataX.push(player_start_x);
	DataY.push(player_start_y);

	visited.insert(objectData);
	short int direction[4][2] = { {0, -1}, {1, 0}, {0, 1},{-1, 0} };
	char direction_c[4][2] = { {'u', 'U'}, {'r', 'R'},{'d', 'D'},{'l', 'L'} };

  	while (!DataX.empty()) {
		//SolverData* newSolverData = solver_queue.front();
//		start = clock();
		char* Cobject = CobjectData.front();
		CobjectData.pop();
		string* Pmove = playerMove.front();
		playerMove.pop();
		short int X = DataX.front();
		DataX.pop();
		short int Y = DataY.front();
		DataY.pop();
//		endt = clock();
		push_popTime += double(endt - start);
		unsigned short int next_position;
		//solver_queue.pop();
		for (int i = 0; i < 4; i++) {
//			start = clock();
			current_objectData = new char[MapLength + 1];
//			endt = clock();
			allocate_time += double(endt - start);
			
//			start = clock();
			strcpy(current_objectData, Cobject);
//			endt = clock();
			copy_time += double(endt - start);

			next_position = (Y + direction[i][1]) * board_linenum + X + direction[i][0];
//			std::cout << newSolverData->CobjectData << std::endl;
			//�����̷��� ���⿡ �ڽ��� �ִ� ���
			if (current_objectData[next_position] == _BOX_C) {
//				move_start = clock();
				push(X, Y, direction[i][0], direction[i][1]);
				
				if (current_objectData != NULL && IsItInside()) {
//					start = clock();
					string* str = new string;
					//endt = clock();
					allocate_time += double(endt - start);

					//start = clock();
					*str = *Pmove;	//���� �����ΰ�
					*str += direction_c[i][1];
					//endt = clock();
					copy_time += double(endt - start);
					//std::cout << *str<<std::endl;
					if (IsSolved()) {
						//total_end = clock();
						total_solve_time += double(total_end - total_start);
						// printw("push pop time \t\t:\t%f\n",push_popTime);
						// printw("IsItInsideTime time \t:\t%f\n",IsItInsideTime);
						// printw("pushTime time \t\t:\t%f\n",pushTime);
						// printw("allocate_time time \t:\t%f\n",allocate_time);
						// printw("copy_time time \t\t:\t%f\n",copy_time);
						// printw("is_solve_time time \t:\t%f\n",is_solve_time);
						// printw("delete_time time \t:\t%f\n",delete_time);
						// printw("box_move_time time \t:\t%f\n",box_move_time);
						// printw("empty_move_time time \t:\t%f\n",empty_move_time);
						// printw("total_solve_time time \t:\t%f\n",total_solve_time);						
					

						return *str;
					}
					//solver_queue.push(new SolverData(current_objectData, str, x + dx, y + dy));
					//start = clock();
					CobjectData.push(current_objectData);
					playerMove.push(str);
					DataX.push(X + direction[i][0]);
					DataY.push(Y + direction[i][1]);
					visited.insert(current_objectData);
					//endt = clock();
					push_popTime += double(endt - start);
				}
				else {
					//start = clock();
					delete current_objectData;
					//endt = clock();
					delete_time += double(endt - start);
				}
				//move_end = clock();
				box_move_time += double(move_end - move_start);
			}
			else {
				if (mapData[next_position] == _WALL_C ||
					current_objectData[next_position] != _EMPTY_C) {
					//start = clock();
					delete current_objectData;
					//endt = clock();
					delete_time += double(endt - start);
					continue;
				}
				//move_start = clock();
				
				current_objectData[Y * board_linenum + X] = _EMPTY_C;
				current_objectData[next_position] = _ME_C;
				if (IsItInside()) { 

					//start = clock();
					string *str = new string[2];
					//endt = clock();
					allocate_time += double(endt - start);

					//start = clock();
					*str = *Pmove;	
					*str += direction_c[i][0];
					//std::cout << *str << std::endl;
					//endt = clock();
					copy_time += double(endt - start);
					if (IsSolved()) { 
						//total_end = clock();
						total_solve_time += double(total_end - total_start);					cout << "push pop time : " << push_popTime << endl;
						// printw("push pop time \t\t:\t%f\n",push_popTime);
						// printw("IsItInsideTime time \t:\t%f\n",IsItInsideTime);
						// printw("pushTime time \t\t:\t%f\n",pushTime);
						// printw("allocate_time time \t:\t%f\n",allocate_time);
						// printw("copy_time time \t\t:\t%f\n",copy_time);
						// printw("is_solve_time time \t:\t%f\n",is_solve_time);
						// printw("delete_time time \t:\t%f\n",delete_time);
						// printw("box_move_time time \t:\t%f\n",box_move_time);
						// printw("empty_move_time time \t:\t%f\n",empty_move_time);
						// printw("total_solve_time time \t:\t%f\n",total_solve_time);						
						// cout << "push pop time : " << push_popTime << "\n";
						// cout << "IsItInsideTime : " << IsItInsideTime << "\n";
						// cout << "push time : " << pushTime << "\n";
						// cout << "allocate_time : " << allocate_time << "\n";
						// cout << "copy time : " << copy_time << "\n";
						// cout << "is_solve time : " << is_solve_time << "\n";
						// cout << "delete time : " << delete_time << "\n";
						// cout << "box_move_time : " << box_move_time << "\n";
						// cout << "empty_move_time : " << empty_move_time << "\n";
						// cout << "total solve time : " << total_solve_time << "\n";



						return *str;
					}
					//solver_queue.push(new SolverData(current_objectData, str, x + dx, y + dy));
					//start = clock();
					CobjectData.push(current_objectData);
					playerMove.push(str);
					DataX.push(X + direction[i][0]);
					DataY.push(Y + direction[i][1]);
					visited.insert(current_objectData);
					//endt = clock();
					push_popTime = double(endt - start);

				}
				else {
					//start = clock();
					delete current_objectData;
					//endt = clock();
					delete_time += double(endt - start);
				}
				//move_end = clock();
				empty_move_time += double(move_end - move_start);
			}
			

		}
		//delete Cobject;
		//delete Pmove;
	}
	return "NO SOLUTION";
}

double AutoMove::GetTotalTime()
{
	return total_solve_time;
}