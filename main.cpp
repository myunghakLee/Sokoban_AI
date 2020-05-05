#include "Move.h"
#include <fstream>
#include <dirent.h>
#include <sys/types.h>
#include <vector>
#include <algorithm>
#include<assert.h>
using namespace std;
int *max_width;
int *line_num;
int map[3][110] = {{
				  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  				  0,  1,  1,  1,  1,  1,  1,  0,  0,  0, 
				  0,  1,  0,  0,  0,  0,  1,  0,  0,  0,
				  0,  1,100,  2,  2,  0,  1,  0,  0,  0,
				  0,  1,  0,  3,  3,  0,  1,  0,  0,  0,
				  0,  1,  0,  0,  0,  0,  1,  0,  0,  0,
				  0,  1,  1,  1,  1,  1,  1,  0,  0,  0,
				  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
				  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				  0,  0,  0,  0,  0,  0,  0,  0,  0,  0

				  },
				  {
				  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  				  0,  1,  1,  1,  1,  0,  0,  0,  0,  0, 
				  0,  1,  3,  0,  1,  1,  0,  0,  0,  0,
				  0,  1,  3,100,  0,  1,  0,  0,  0,  0,
				  0,  1,  3,  0,  2,  1,  0,  0,  0,  0,
				  0,  1,  1,  2,  0,  1,  1,  1,  0,  0,
				  0,  0,  1,  0,  2,  0,  0,  1,  0,  0,
				  0,  0,  1,  0,  0,  0,  0,  1,  0,  0, 
				  0,  0,  1,  0,  0,  1,  1,  1,  0,  0,
				  0,  0,  1,  1,  1,  1,  1,  1,  0,  0,
				  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
				  },
				  {
				  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  				  0,  1,  1,  1,  1,  1,  1,  1,  1,  0, 
				  0,  1,  0,  0,  0,  0,  0,  1,  1,  0,
				  0,  1,  0,  0,  0,  0,  0,  1,  1,  0,
				  0,  1,  3,  0,  1,  0,  0,  1,  1,  0,
				  0,  1,  3,  0,  2,  2,  0,  1,  1,  0,
				  0,  1,  3,  2,  2,  0,  0,  1,  1,  0,
				  0,  1,  3,  1,  0,  0,100,  1,  0,  0, 
				  0,  1,  1,  1,  1,  1,  1,  1,  0,  0,
				  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
				  }
				  };

void LoadingScene();
void GameScene();
void init_scr();
int frontUI();
int *get_map(string filename, int stage, bool is_number);

int main(int argc, char **argv) {
	




	string filename;
	int **MyMap;
	int level = 1;
	if(argc == 1){
		max_width = new int[3];
		line_num = new int[3]; 
		max_width[0] = 10;
		max_width[1] = 10;
		max_width[2] = 10;

		line_num[0] = 11;
		line_num[1] = 11;
		line_num[2] = 11;

		level = 3;
		MyMap = new int*[3];
		for(int i =0;i<3;i++){
			MyMap[i] = new int[110];
			MyMap[i] = map[i];
		}
	}
	else if (argc ==2){
		//int형으로 된 map불러오기
		filename = argv[1];
		MyMap = new int*[1];
		max_width = new int[1];
		line_num = new int[1];
		MyMap[0] = get_map(filename, 0, true);
		level = 1;
		////////////////////////////
	}
	else if(argc == 3 || argc == 4){
		string input_string = argv[1];
		if(input_string == "c"){
			filename = argv[2];
			MyMap = new int*[1];
			max_width = new int[1];
			line_num = new int[1];
			MyMap[0] = get_map(filename, 0, false);
			level = 1;
		}
		else if (input_string == "dir"){



			DIR *dir;
			struct dirent *ent;
			dir = opendir (argv[2]);
			if (dir != NULL) {
				bool is_number_file = false;	
				
				if(argc == 4){
					is_number_file = true;
					string temp;
					temp = argv[3];
					if(temp != "n"){
						cout<<"잘못된 입력입니다.\n";
						exit(1);					
					}	
				}

				vector<string> filenames;
				int num_file = 0;
				/* print all the files and directories within directory */
				
				while ((ent = readdir(dir)) != NULL) {
					num_file++;
					filenames.push_back(ent->d_name);
				}
				sort(filenames.begin(), filenames.end());
				// for(int j =0;j<6;j++){
				// 	cout<<filenames.at(j);
				// }
				MyMap = new int*[num_file];
				max_width = new int[num_file];
				line_num = new int[num_file]; 
				
				level = num_file;
				int map_num = 0;
				for(int j = 0; j < num_file; j++){
					cout<<"filename : " << filenames.at(j)<<"입니다.\n";
					if(filenames.at(j) == "." || filenames.at(j) == ".."){
						continue;
					}
					filename = argv[2];
					filename +='/';
					filename += filenames.at(j);
					MyMap[map_num] = get_map(filename, map_num, is_number_file);
					if(MyMap[map_num] != NULL){
						cout<<*MyMap[map_num]<<endl;
						map_num++;
					}
				}
				level = map_num;


				closedir (dir);
			} else {
				/* could not open directory */
				cout<<"해당 경로는 존재하지 않습니다.";
				return -1;
			}
		}
		else{
			cout<<"잘못된 입력입니다.\n";
			exit(1);
		}
	}

	

	

	while(1){
		// 기본 윈도우 25 x 80
		clear();
		init_scr();
		bkgd(COLOR_PAIR(1)); // attribute로 윈도우 전체 적용
		attron(COLOR_PAIR(3)); // 1번 팔레트 사용
		mvprintw(10,31,"S O K O B A N !\n");
		attroff(COLOR_PAIR(3));
		mvprintw(15,28,"Press 's' to play game!\n");
		mvprintw(16,28,"Press 'q' to quit!\n");

		attron(COLOR_PAIR(4));
		border('*','*','*','*','*','*','*','*');
		attroff(COLOR_PAIR(4));

		refresh();
		char start = getch();
		

		

		if(start == 'q' || start == 'Q'){
			printw("BYE!\n");
			refresh();
			touchwin(stdscr);
			refresh();
			endwin();

			exit(1);
		}
		touchwin(stdscr);
		refresh();
		endwin();
		if(start == 's'){break;}
	}
	LoadingScene();
	keypad(stdscr, TRUE);
	MEVENT event;

	char key;
	bool success = false;
							// new window
	WINDOW *win1, *win2;
	win1 = newwin(11, 20, 1, 60);
	wbkgd(win1, COLOR_PAIR(1));
	win2 = newwin(11, 20, 12, 60);
	wbkgd(win2, COLOR_PAIR(1));
  	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    WINDOW *autowin;
    autowin = newwin(3, 13, 1, 1);
    wbkgd(autowin, COLOR_PAIR(1));

    curs_set(0);

	for(int i = 0; i < level; i++){
		clear();
		char mode;
		printw("STAGE %d\n", i+1);
		
			Move M(MyMap[i], line_num[i], max_width[i]);
			while(1){
				clear(); // 화면 전부 지우기
				bkgd(COLOR_PAIR(1));
				attron(COLOR_PAIR(3));
				mvprintw(3,22,"STAGE %d", i+1);
				attroff(COLOR_PAIR(3));
					
				M.PrintMap();
				GameScene();
				attron(COLOR_PAIR(2));
				mvprintw(17,14,"Press key to move player");
				attroff(COLOR_PAIR(2));
				//mvprintw(18,5,"w - UP  s - DOWN  a - LEFT  d - RIGHT");
				refresh();
						

				wattron(win1, COLOR_PAIR(8));
				mvwprintw(win1, 2, 5," X : %d\n", M.GetMyPositionX());
				mvwprintw(win1, 4, 5," Y : %d\n", M.GetMyPositionY());
				wattroff(win1, COLOR_PAIR(8));
				wattron(win1, COLOR_PAIR(7));
				mvwprintw(win1, 6, 5,"Move : %d\n", M.GetMoveCount());
				wattroff(win1, COLOR_PAIR(7));
				wattron(win1, COLOR_PAIR(6));
				wborder(win1, '*', '*', '*', '*', '*', '*', '*', '*');
				wattroff(win1, COLOR_PAIR(6));
				wrefresh(win1);


				mvwprintw(win2, 2, 5,"w - UP↑");
				mvwprintw(win2, 4, 5,"s - DOWN↓");
				mvwprintw(win2, 6, 5,"a - LEFT←");
				mvwprintw(win2, 8, 5,"d - RIGHT→");
				wattron(win2, COLOR_PAIR(6));
				wborder(win2, '*', '*', '*', '*', '*', '*', '*', '*');
				wattroff(win2, COLOR_PAIR(6));
				wrefresh(win2);
						
 				wattron(autowin, COLOR_PAIR(9));
 	   			mvwprintw(autowin, 1, 1, "AUTO BUTTON");
   				wborder(autowin, '|','|','-','-','*','*','*','*');
   				wattroff(autowin, COLOR_PAIR(9));
   				wrefresh(autowin);


				int key = getch();

				MEVENT event;



				if (key == KEY_MOUSE){
			      	assert(getmouse(&event) == OK);
			      	if(event.x<13 && event.y <3 && event.x > 0 && event.y>0){
						M.AutoGamming(win1);					
					}
    			}


				
				if (key == 'w' || key == KEY_UP) {
					M.moveUp();
				}
				else if (key == 's' || key == KEY_DOWN) {
					M.moveDown();
				}
				else if (key == 'a' || key == KEY_LEFT) {
					M.moveLeft();
				}
				else if (key == 'd'  || key == KEY_RIGHT) {
					M.moveRight();
				}
				else if (key == 'z'){
					M.AutoGamming(win1);					
				}
				else if (key == 'p'){
					break;
				}
				//check game fin 

				if (M.IsSuccess()) {
					clear();
					mvprintw(20,20,"STAGE %d\n", i+1);
					M.PrintMap();
					
					attron(COLOR_PAIR(3));
					mvprintw(18,18,"STAGE %d SUCCESS!\n", i+1);
					attroff(COLOR_PAIR(3));
					if(i >= level -1){
						attron(COLOR_PAIR(3));
						mvprintw(20,17,"The levels are all over\n");
						attroff(COLOR_PAIR(3));
					}
					else{
						attron(COLOR_PAIR(2));
						mvprintw(20,17,"press any key to continue!\n");
						attroff(COLOR_PAIR(2));
						refresh();
						getch();
					}
					break;
				}
			
		}
	}
		
	mvprintw(22,50,"BYE!\n");
	touchwin(stdscr);
	refresh();
	getch();
	endwin();

}
// 초기화
void init_scr()
{
	setlocale(LC_ALL, "");
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_RED,COLOR_GREEN); // Title scene
	init_pair(5, COLOR_WHITE, COLOR_MAGENTA); // Roading scene
	init_pair(6, COLOR_RED,COLOR_CYAN); // Game scene
	init_pair(7, COLOR_MAGENTA,COLOR_BLACK);
	init_pair(8, COLOR_BLUE,COLOR_BLACK);
	init_pair(9, COLOR_YELLOW, COLOR_WHITE);
    curs_set(1); // 화면 커서(큰 커서)
    noecho(); // 문자 입력시 입력한 값을 화면에 보이지 않게함
    keypad(stdscr, TRUE); // 키보드 입력
}

int *get_map(string filename, int stage, bool is_number){

	ifstream in(filename);
	if(filename == "." || filename == ".."){
		cout<<"파일 이름이 잘못되었습니다.\n";
		exit(1);
		return NULL;
	}
	
	if(!in.is_open()){
		cout<<"파일 이름이 잘못되었습니다.\n";
		cout<<filename;
		exit(1);

		return NULL;
	}
	
	string input_string[200];
	max_width[stage] = 0;
	line_num[stage] = 0;

	while(getline(in, input_string[line_num[stage]])){
		if(is_number){
			while(input_string[line_num[stage]].find(" ") != string::npos)
				input_string[line_num[stage]].replace(input_string[line_num[stage]].find(" "), 1, "");
		}
		if(input_string[line_num[stage]].length()> max_width[stage]){
			max_width[stage] = input_string[line_num[stage]].length();
		}
		line_num[stage]++;
	}
	int *return_map = new int[max_width[stage] * line_num[stage] + 1]; 

	// line_num[stage]--;
	// max_width[stage]--;
	int size_sub = 0;
	if(is_number){
		size_sub = 1;
	}
	for(int i =0;i<line_num[stage];i++){
		for(int j =0;j<max_width[stage];j++){
			
			if(j < input_string[i].size() - 1 	){
				if(input_string[i][j] == _EMPTY_C){
					return_map[i * max_width[stage] + j] = _EMPTY;
				}
				else if(input_string[i][j] == _WALL_C){
					return_map[i * max_width[stage] + j] = _WALL;
				}
				else if(input_string[i][j] == _BOX_C){
					return_map[i * max_width[stage] + j] = _BOX;
				}
				else if(input_string[i][j] == _DESTINATION_C){
					return_map[i * max_width[stage] + j] = _DESTINATION;
				}
				else if(input_string[i][j] == _ME_C){
					return_map[i * max_width[stage] + j] = _ME;
				}
				else if(input_string[i][j] == '*'){
					return_map[i * max_width[stage] + j] = _BOXinDESTINATION;
				}			
				else if(input_string[i][j] == '5'){
					return_map[i * max_width[stage] + j] = _ME;
				}
				else if(input_string[i][j] == '4'){
					return_map[i * max_width[stage] + j] = _EMPTY;
				}
				else{
					return_map[i * max_width[stage] + j] = (int)input_string[i][j] - '0';
				}
			}
			else{
				return_map[i*max_width[stage]+j] = _EMPTY;
			}
//			std::cout<<return_map[i*max_width[stage]+j];
		}
//		std::cout<<endl;
	}
//	int a = 3;
//	std::cin>>a;
	return return_map;

}

void LoadingScene()
{
	clear(); // 전부 지우기
	
	bkgd(COLOR_PAIR(5)); // attribute로 윈도우 전체 적용
	attron(COLOR_PAIR(5)); // 1번 팔레트 사용
	mvprintw(10, 31, "L O A D I N G !\n");
	attroff(COLOR_PAIR(5));
	for (int i = 25; i < 52; ++i)
	{
		mvprintw(15, i, "\u2B1B");
		usleep(25000); // 1초 대기
		refresh();
	}
}
void GameScene()
{
	attron(COLOR_PAIR(6));
	border('*', '*', '*', '*', '*', '*', '*', '*');
	attroff(COLOR_PAIR(6));
}
