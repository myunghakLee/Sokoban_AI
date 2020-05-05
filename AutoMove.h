# include "Move.h"


#define _EMPTY_C ' '
#define _WALL_C '#'
#define _BOX_C '$'
#define _DESTINATION_C '.'
#define _OUTSIDE_C ' '
#define _BOXinDESTINATION_C ' '
#define _ME_C '@'
#define _MEinDESTINATION_C '@'

class AutoMove {
private:
	Move* AI;
	char *mapinfo, *mapData, *objectData;
	char *current_objectData;
	short int player_start_x, player_start_y;
	unsigned short int board_linenum;	//�޾ƿ� ������ ���� ����
	unsigned short int MapLength;
	//char mapConverter = [' ':' ', '.' : '.', '@' : ' ', '#' : '#', '$' : ' ']

	//AutoMove(int* board, int y, int x) {
	//	


	//};
public:
	AutoMove(Move *m) {
		AI = m;
		//map�� ũ��
		MapLength = AI->height * AI->width;
		mapinfo = new char[MapLength];
		mapData = new char[MapLength];
		objectData = new char[MapLength];
		//mapinfo�� mapData�� ������ ũ�⸸ŭ int������ ���� �Ҵ�

		board_linenum = AI->width;
		//���� �˸��� ���� ��ġ�Ͽ� �������
		for (int i = 0; i < AI->height; i++) {
			for (int j = 0; j < AI->width; j++) {
				if (AI->Map[i][j] == _ME || AI ->Map[i][j] == _BOX || AI->Map[i][j] == _EMPTY) {
					mapData[i * AI->width + j] = _EMPTY_C;
				}
				else if(AI->Map[i][j] == _WALL) {
					mapData[i * AI->width + j] = _WALL_C;
				}
				else if (AI->Map[i][j] == _DESTINATION || AI->Map[i][j] == _MEinDESTINATION || AI->Map[i][j] == _BOXinDESTINATION) {
					mapData[i * AI->width + j] = _DESTINATION_C;
				}
				

				if (AI->Map[i][j] == _DESTINATION || AI->Map[i][j] == _WALL || AI->Map[i][j] == _EMPTY) {
					objectData[i * AI->width + j] = _EMPTY_C;
				}
				else if (AI->Map[i][j] == _BOX || AI->Map[i][j] ==_BOXinDESTINATION) {
					objectData[i * AI->width + j] = _BOX_C;
				}
				else if (AI->Map[i][j] == _ME || AI->Map[i][j] == _MEinDESTINATION) {
					objectData[i * AI->width + j] = _ME_C;
				}
			}
		}
		player_start_x = AI->MyPositionX;
		player_start_y = AI->MyPositionY;
	}


	void push(short int x, short int y, short int dx, short int dy);
	string solve();
	bool IsSolved();
	bool IsItInside();

	double GetTotalTime();
};