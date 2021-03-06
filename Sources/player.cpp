#include "gobang.h"

using namespace std;

void Player::init(int side, char color)
{
	this->side = side;
	this->chessColor = color;
}

void Player::play(int x, int y)
{
	game.temp = { x, y };
	game.chessBoard[x][y] = chessColor;
	game.turn = -game.turn;
	game.turnCount += 1;
}

void AI::init(int side, char color)
{
	this->side = side;
	this->chessColor = color;
	this->bestPoint = { 0, 0 };
	this->score = 0;
	this->maxScore = 0;
}

void AI::identify()
{
	for (int line = 0; line < LINE_COUNT; line++)
	{
		for (int i = 0; i < game.lineData[line].size(); i++)
		{
			if (game.lineData[line][i] != EMPTY_CHESS && game.lineData[line][i] != NOW_CHESS)
			{
				switch (bool(game.lineData[line][i] == chessColor))
				{
					case true: game.lineData[line][i] = SELF_CHESS; break;
					case false: game.lineData[line][i] = OPPOSITE_CHESS; break;
				}
			}
		}
	}
}

void AI::clearFormatData()
{
	memset(&format, 0, sizeof(format));
	memset(&score, 0, sizeof(score));
}

void AI::getFormatData()
{
	for (int line = 0; line < LINE_COUNT; line++)
	{
		if (game.lineData[line].find("SSSSN") != game.lineData[line].npos ||
			game.lineData[line].find("SSSNS") != game.lineData[line].npos ||
			game.lineData[line].find("SSNSS") != game.lineData[line].npos ||
			game.lineData[line].find("SNSSS") != game.lineData[line].npos ||
			game.lineData[line].find("NSSSS") != game.lineData[line].npos)
		{
			format.attackFive += 1;
		}
		if (game.lineData[line].find("0SSSN0") != game.lineData[line].npos ||
			game.lineData[line].find("0SSNS0") != game.lineData[line].npos ||
			game.lineData[line].find("0SNSS0") != game.lineData[line].npos ||
			game.lineData[line].find("0NSSS0") != game.lineData[line].npos)
		{
			format.doubleFour += 1;
		}
		if (game.lineData[line].find("SSSN0") != game.lineData[line].npos ||
			game.lineData[line].find("SSNS0") != game.lineData[line].npos ||
			game.lineData[line].find("SNSS0") != game.lineData[line].npos ||
			game.lineData[line].find("NSSS0") != game.lineData[line].npos ||
			game.lineData[line].find("SSS0N") != game.lineData[line].npos ||
			game.lineData[line].find("SSN0S") != game.lineData[line].npos ||
			game.lineData[line].find("SNS0S") != game.lineData[line].npos ||
			game.lineData[line].find("NSS0S") != game.lineData[line].npos ||
			game.lineData[line].find("SS0SN") != game.lineData[line].npos ||
			game.lineData[line].find("SS0NS") != game.lineData[line].npos ||
			game.lineData[line].find("SN0SS") != game.lineData[line].npos ||
			game.lineData[line].find("NS0SS") != game.lineData[line].npos ||
			game.lineData[line].find("S0SSN") != game.lineData[line].npos ||
			game.lineData[line].find("S0SNS") != game.lineData[line].npos ||
			game.lineData[line].find("S0NSS") != game.lineData[line].npos ||
			game.lineData[line].find("N0SSS") != game.lineData[line].npos ||
			game.lineData[line].find("0SSSN") != game.lineData[line].npos ||
			game.lineData[line].find("0SSNS") != game.lineData[line].npos ||
			game.lineData[line].find("0SNSS") != game.lineData[line].npos ||
			game.lineData[line].find("0NSSS") != game.lineData[line].npos)
		{
			format.attackFour += 1;
		}
		if (game.lineData[line].find("0SSN00") != game.lineData[line].npos ||
			game.lineData[line].find("0SNS00") != game.lineData[line].npos ||
			game.lineData[line].find("0NSS00") != game.lineData[line].npos ||
			game.lineData[line].find("00SSN0") != game.lineData[line].npos ||
			game.lineData[line].find("00SNS0") != game.lineData[line].npos ||
			game.lineData[line].find("00NSS0") != game.lineData[line].npos ||
			game.lineData[line].find("0SS0N0") != game.lineData[line].npos ||
			game.lineData[line].find("0SN0S0") != game.lineData[line].npos ||
			game.lineData[line].find("0NS0S0") != game.lineData[line].npos ||
			game.lineData[line].find("0S0SN0") != game.lineData[line].npos ||
			game.lineData[line].find("0S0NS0") != game.lineData[line].npos ||
			game.lineData[line].find("0N0SS0") != game.lineData[line].npos)
		{
			format.attackThree += (format.attackFour == 0) ? 1 : 0;
		}
		if (game.lineData[line].find("OOOON") != game.lineData[line].npos ||
			game.lineData[line].find("OOONO") != game.lineData[line].npos ||
			game.lineData[line].find("OONOO") != game.lineData[line].npos ||
			game.lineData[line].find("ONOOO") != game.lineData[line].npos ||
			game.lineData[line].find("NOOOO") != game.lineData[line].npos)
		{
			format.defendFour += 1;
		}
		if (game.lineData[line].find("0OOON0") != game.lineData[line].npos ||
			game.lineData[line].find("0NOOO0") != game.lineData[line].npos ||
			game.lineData[line].find("0OONO0") != game.lineData[line].npos ||
			game.lineData[line].find("0OO0ON") != game.lineData[line].npos ||
			game.lineData[line].find("NOO0O0") != game.lineData[line].npos ||
			game.lineData[line].find("0ONOO0") != game.lineData[line].npos ||
			game.lineData[line].find("NO0OO0") != game.lineData[line].npos ||
			game.lineData[line].find("0O0OON") != game.lineData[line].npos)
		{
			format.defendThree += (format.defendFour == 0) ? 1 : 0;
		}
		if (game.lineData[line].find("0SN0") != game.lineData[line].npos ||
			game.lineData[line].find("0NS0") != game.lineData[line].npos)
		{
			format.attackTwo += 1;
		}
		if (game.lineData[line].find("SN") != game.lineData[line].npos ||
			game.lineData[line].find("NS") != game.lineData[line].npos)
		{
			format.linkTwo += 1;
		}
		if (game.lineData[line].find("OOON0") != game.lineData[line].npos ||
			game.lineData[line].find("OONO0") != game.lineData[line].npos ||
			game.lineData[line].find("ONOO0") != game.lineData[line].npos ||
			game.lineData[line].find("NOOO0") != game.lineData[line].npos ||
			game.lineData[line].find("OOO0N") != game.lineData[line].npos ||
			game.lineData[line].find("OON0O") != game.lineData[line].npos ||
			game.lineData[line].find("ONO0O") != game.lineData[line].npos ||
			game.lineData[line].find("NOO0O") != game.lineData[line].npos ||
			game.lineData[line].find("OO0ON") != game.lineData[line].npos ||
			game.lineData[line].find("OO0NO") != game.lineData[line].npos ||
			game.lineData[line].find("ON0OO") != game.lineData[line].npos ||
			game.lineData[line].find("NO0OO") != game.lineData[line].npos ||
			game.lineData[line].find("O0OON") != game.lineData[line].npos ||
			game.lineData[line].find("O0ONO") != game.lineData[line].npos ||
			game.lineData[line].find("O0NOO") != game.lineData[line].npos ||
			game.lineData[line].find("N0OOO") != game.lineData[line].npos ||
			game.lineData[line].find("0OOON") != game.lineData[line].npos ||
			game.lineData[line].find("0OONO") != game.lineData[line].npos ||
			game.lineData[line].find("0ONOO") != game.lineData[line].npos ||
			game.lineData[line].find("0NOOO") != game.lineData[line].npos)
		{
			format.formatFour += 1;
		}
		if (game.lineData[line].find("0OON00") != game.lineData[line].npos ||
			game.lineData[line].find("0ONO00") != game.lineData[line].npos ||
			game.lineData[line].find("0NOO00") != game.lineData[line].npos ||
			game.lineData[line].find("00OON0") != game.lineData[line].npos ||
			game.lineData[line].find("00ONO0") != game.lineData[line].npos ||
			game.lineData[line].find("00NOO0") != game.lineData[line].npos ||
			game.lineData[line].find("0OO0N0") != game.lineData[line].npos ||
			game.lineData[line].find("0ON0O0") != game.lineData[line].npos ||
			game.lineData[line].find("0NO0O0") != game.lineData[line].npos ||
			game.lineData[line].find("0O0ON0") != game.lineData[line].npos ||
			game.lineData[line].find("0O0NO0") != game.lineData[line].npos ||
			game.lineData[line].find("0N0OO0") != game.lineData[line].npos)
		{
			format.formatThree += (format.formatFour == 0) ? 1 : 0;
		}
	}
}

void AI::analysisData(int x, int y)
{
	if (format.attackFive > 0)															{ score = 30; }
	else if (format.defendFour > 1)														{ score = 29; }
	else if (format.defendFour > 0 && format.attackFour > 0)							{ score = 28; }
	else if (format.defendFour > 0 && format.defendThree > 0)							{ score = 27; }
	else if (format.defendFour > 0 && format.attackThree > 0)							{ score = 26; }
	else if (format.defendFour > 0)														{ score = 25; }
	else if (format.doubleFour > 0)														{ score = 24; }
	else if (format.attackFour > 1)														{ score = 23; }
	else if (format.attackFour > 0 && format.attackThree > 0)							{ score = 22; }
	else if (format.attackFour > 0 && format.defendThree > 0)							{ score = 21; }
	else if (format.defendThree > 1)													{ score = 20; }
	else if (format.defendThree > 0 && format.formatFour > 1)							{ score = 19; }
	else if (format.defendThree > 0 && format.formatFour > 0 && format.formatThree > 0)	{ score = 18; }
	else if (format.defendThree > 0 && format.attackThree > 0)							{ score = 17; }
	else if (format.defendThree > 0)													{ score = 16; }
	else if (format.formatFour > 1)														{ score = 15; }
	else if (format.formatFour > 0 && format.formatThree > 0)							{ score = 14; }
	else if (format.attackThree > 1)													{ score = 13; }
	else if (format.attackThree > 0 && format.linkTwo > 2)								{ score = 12; }
	else if (format.attackThree > 0 && format.linkTwo > 1)								{ score = 11; }
	else if (format.attackThree > 0 && format.linkTwo > 0)								{ score = 10; }
	else if (format.attackThree > 0)													{ score = 9; }
	else if (format.formatThree > 1)													{ score = 8; }
	else if (format.attackFour > 0 && format.linkTwo > 2)								{ score = 7; }
	else if (format.attackFour > 0 && format.linkTwo > 1)								{ score = 6; }
	else if (format.attackFour > 0 && format.linkTwo > 0)								{ score = 5; }
	else if (format.attackFour > 0)														{ score = 4; }
	else if (format.attackTwo > 2)														{ score = 3; }
	else if (format.attackTwo > 1)														{ score = 2; }
	else if (format.attackTwo > 0)														{ score = 1; }

	if (score > maxScore)
	{
		maxScore = score;
		bestPoint = { x, y };
	}
}

void AI::play()
{
	Point position = { 0, 0 };

	if (maxScore == 0)
	{
		switch (side)
		{
			case BLACK_SIDE: position = { TABLE_LARGE / 2,TABLE_LARGE / 2 }; break;
			case WHITE_SIDE: do
			{
				int x = (rand() % 3) - 1 + game.temp.x;
				int y = (rand() % 3) - 1 + game.temp.y;

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