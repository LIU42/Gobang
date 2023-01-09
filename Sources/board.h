#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include <string>

using namespace std;

enum class Chess
{
	BLACK = 'B',
	WHITE = 'W',
	EMPTY = '0',
	SELF = 'S',
	OPPOSITE = 'O',
	NOW = 'N'
};

struct Point
{
	int x;
	int y;
};

typedef vector <string> LineData;
typedef vector <Point> LinkData;

class Board
{
	public:
		static const int LARGE = 19;
		static const int LINK_COUNT = 5;
		static const int LINE_COUNT = 4;

	private:
		Chess table[LARGE][LARGE];
		Chess tempChess;
		Point tempPoint;
	
	public:
		void init();
		void play(Chess, int, int);

	public:
		int getTempX();
		int getTempY();

	public:
		bool isBlackWin(LineData&);
		bool isWhiteWin(LineData&);

	public:
		Chess getTableData(int, int);
		LineData getLineData(int, int, bool);
		LinkData getLinkData(LineData&);
};
#endif