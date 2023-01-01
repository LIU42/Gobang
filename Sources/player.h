#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "board.h"

enum class Side { BLACK, WHITE, NOBODY };

struct Format
{
	int rushFive;
	int aliveFour;
	int rushFour;
	int endFour;
	int preFour;
	int aliveThree;
	int endThree;
	int preThree;
	int aliveTwo;
	int linkTwo;
};

class Player
{
	protected:
		Side side;
		Chess chess;
		Board* boardPtr;

	public:
		void init(Side, Chess, Board*);
		void play(int, int);

	public:
		Side getSide();
};

class PlayerAI : public Player
{
	private:
		Format format;
		Point bestPoint;
		int maxScore;

	private:
		void identify(LineData&);
		void clearFormatData();
		void getFormatData(LineData&);
		void analysisData(int, int);

	public:
		void init(Side, Chess, Board*);
		void analysis();
		void play();
};
#endif