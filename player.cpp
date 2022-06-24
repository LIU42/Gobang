#include "gobang.h"

using namespace std;

void Player::init(int inputSide, char inputColor)
{
	side = inputSide;
	chessColor = inputColor;
}

void Player::play(int x, int y)
{
	game.temp = { x, y };
	game.chessBoard[x][y] = chessColor;
	game.turn = -game.turn;
	game.turnCount += 1;
}

void Computer::init(int inputSide, char inputColor)
{
	side = inputSide;
	chessColor = inputColor;
	bestPoint = { 0, 0 };
	maxScore = 0;
}

void Computer::identify()
{
	for (int line = 0; line < 4; line++)
	{
		for (int i = 0; i < game.chessBoardLineData[line].size(); i++)
		{
			if (game.chessBoardLineData[line][i] != EMPTY_CHESS && game.chessBoardLineData[line][i] != NOW_CHESS)
			{
				if (game.chessBoardLineData[line][i] == chessColor) { game.chessBoardLineData[line][i] = SELF_CHESS; }
				else { game.chessBoardLineData[line][i] = OPPOSITE_CHESS; }
			}
		}
	}
}

void Computer::analysis(int x, int y)
{
	int score = 0;
	int attackFive = 0;
	int doubleFour = 0;
	int attackFour = 0;
	int defendFour = 0;
	int formatFour = 0;
	int attackThree = 0;
	int defendThree = 0;
	int formatThree = 0;
	int attackTwo = 0;
	int linkTwo = 0;

	for (int line = 0; line < 4; line++)
	{
		if (game.chessBoardLineData[line].find("SSSSN") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("SSSNS") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("SSNSS") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("SNSSS") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("NSSSS") != game.chessBoardLineData[line].npos)
		{ attackFive += 1; }

		if (game.chessBoardLineData[line].find("0SSSN0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0SSNS0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0SNSS0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0NSSS0") != game.chessBoardLineData[line].npos)
		{ doubleFour += 1; }

		if (game.chessBoardLineData[line].find("SSSN0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("SSNS0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("SNSS0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("NSSS0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("SSS0N") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("SSN0S") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("SNS0S") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("NSS0S") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("SS0SN") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("SS0NS") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("SN0SS") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("NS0SS") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("S0SSN") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("S0SNS") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("S0NSS") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("N0SSS") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0SSSN") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0SSNS") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0SNSS") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0NSSS") != game.chessBoardLineData[line].npos)
		{ attackFour += 1; }

		else if (
			game.chessBoardLineData[line].find("0SSN00") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0SNS00") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0NSS00") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("00SSN0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("00SNS0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("00NSS0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0SS0N0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0SN0S0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0NS0S0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0S0SN0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0S0NS0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0N0SS0") != game.chessBoardLineData[line].npos)
		{ attackThree += 1; }

		if (game.chessBoardLineData[line].find("OOOON") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("OOONO") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("OONOO") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("ONOOO") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("NOOOO") != game.chessBoardLineData[line].npos)
		{ defendFour += 1; }

		else if (
			game.chessBoardLineData[line].find("0OOON0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0NOOO0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0OONO0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0OO0ON") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("NOO0O0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0ONOO0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("NO0OO0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0O0OON") != game.chessBoardLineData[line].npos)
		{ defendThree += 1; }

		if (game.chessBoardLineData[line].find("0SN0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0NS0") != game.chessBoardLineData[line].npos)
		{ attackTwo += 1; }

		if (game.chessBoardLineData[line].find("SN") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("NS") != game.chessBoardLineData[line].npos)
		{ linkTwo += 1; }

		if (game.chessBoardLineData[line].find("OOON0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("OONO0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("ONOO0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("NOOO0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("OOO0N") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("OON0O") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("ONO0O") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("NOO0O") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("OO0ON") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("OO0NO") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("ON0OO") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("NO0OO") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("O0OON") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("O0ONO") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("O0NOO") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("N0OOO") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0OOON") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0OONO") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0ONOO") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0NOOO") != game.chessBoardLineData[line].npos)
		{ formatFour += 1; }

		else if (
			game.chessBoardLineData[line].find("0OON00") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0ONO00") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0NOO00") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("00OON0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("00ONO0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("00NOO0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0OO0N0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0ON0O0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0NO0O0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0O0ON0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0O0NO0") != game.chessBoardLineData[line].npos ||
			game.chessBoardLineData[line].find("0N0OO0") != game.chessBoardLineData[line].npos)
		{ formatThree += 1; }
	}

	if (attackFive > 0)												{ score = 30; }
	else if (defendFour > 1)										{ score = 29; }
	else if (defendFour > 0 && attackFour > 0)						{ score = 28; }
	else if (defendFour > 0 && defendThree > 0)						{ score = 27; }
	else if (defendFour > 0 && attackThree > 0)						{ score = 26; }
	else if (defendFour > 0)										{ score = 25; }
	else if (doubleFour > 0)										{ score = 24; }
	else if (attackFour > 1)										{ score = 23; }
	else if (attackFour > 0 && attackThree > 0)						{ score = 22; }
	else if (attackFour > 0 && defendThree > 0)						{ score = 21; }
	else if (defendThree > 1)										{ score = 20; }
	else if (defendThree > 0 && formatFour > 1)						{ score = 19; }
	else if (defendThree > 0 && formatFour > 0 && formatThree > 0)	{ score = 18; }
	else if (defendThree > 0 && attackThree > 0)					{ score = 17; }
	else if (defendThree > 0)										{ score = 16; }
	else if (formatFour > 1)										{ score = 15; }
	else if (formatFour > 0 && formatThree > 0)						{ score = 14; }
	else if (attackThree > 1)										{ score = 13; }
	else if (attackThree > 0 && linkTwo > 2)						{ score = 12; }
	else if (attackThree > 0 && linkTwo > 1)						{ score = 11; }
	else if (attackThree > 0 && linkTwo > 0)						{ score = 10; }
	else if (attackThree > 0)										{ score = 9; }
	else if (formatThree > 1)										{ score = 8; }
	else if (attackFour > 0 && linkTwo > 2)							{ score = 7; }
	else if (attackFour > 0 && linkTwo > 1)							{ score = 6; }
	else if (attackFour > 0 && linkTwo > 0)							{ score = 5; }
	else if (attackFour > 0)										{ score = 4; }
	else if (attackTwo > 2)											{ score = 3; }
	else if (attackTwo > 1)											{ score = 2; }
	else if (attackTwo > 0)											{ score = 1; }

	if (score > maxScore)
	{
		maxScore = score;
		bestPoint = { x, y };
	}
}

void Computer::play()
{
	Point position = { 0, 0 };

	if (maxScore == 0)
	{
		switch (side)
		{
			case BLACK_SIDE: position = { TABLE_LARGE / 2,TABLE_LARGE / 2 }; break;
			case WHITE_SIDE: do
			{
				int x = game.randDev(game.random) + game.temp.x;
				int y = game.randDev(game.random) + game.temp.y;

				if (game.chessBoard[x][y] == EMPTY_CHESS && x < TABLE_LARGE && y < TABLE_LARGE && x >= 0 && y >= 0)
				{
					position = { x, y };
					break;
				}
			} while (true); break;
		}
	}
	else { position = { bestPoint.x, bestPoint.y }; }

	game.temp = position;
	game.chessBoard[position.x][position.y] = chessColor;
	game.turn = -game.turn;
	game.turnCount += 1;
	maxScore = 0;
}