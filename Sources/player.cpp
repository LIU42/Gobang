#include "gobang.h"

void Player::init(int side, char color)
{
	this->side = side;
	this->chessColor = color;
}

void Player::play(Point pos)
{
	game.temp = pos;
	game.chessBoard[pos.x][pos.y] = chessColor;
	game.turn = -game.turn;
	game.turnCount += 1;
}

void AIPlayer::init(int side, char color)
{
	Player::init(side, color);
	score = 0;
	maxScore = 0;
}

void AIPlayer::identify()
{
	for (int line = 0; line < LINE_COUNT; line++)
	{
		for (int i = 0; i < game.lineData[line].size(); i++)
		{
			if (game.lineData[line][i] != EMPTY_CHESS && game.lineData[line][i] != NOW_CHESS)
			{
				switch (game.lineData[line][i] == chessColor)
				{
					case true:  game.lineData[line][i] = SELF_CHESS; break;
					case false: game.lineData[line][i] = OPPOSITE_CHESS; break;
				}
			}
		}
	}
}

void AIPlayer::clearFormatData()
{
	memset(&format, 0, sizeof(format));
	memset(&score, 0, sizeof(score));
}

void AIPlayer::getFormatData()
{
	static bool isFindRushFour;
	static bool isFindEndFour;
	static bool isFindPreFour;

	for (int line = 0; line < LINE_COUNT; line++)
	{
		isFindRushFour = false;
		isFindEndFour = false;
		isFindPreFour = false;

		if (game.lineData[line].find("SSSSN") != game.lineData[line].npos ||
			game.lineData[line].find("SSSNS") != game.lineData[line].npos ||
			game.lineData[line].find("SSNSS") != game.lineData[line].npos ||
			game.lineData[line].find("SNSSS") != game.lineData[line].npos ||
			game.lineData[line].find("NSSSS") != game.lineData[line].npos)
		{
			format.rushFive += 1;
		}
		if (game.lineData[line].find("0SSSN0") != game.lineData[line].npos ||
			game.lineData[line].find("0SSNS0") != game.lineData[line].npos ||
			game.lineData[line].find("0SNSS0") != game.lineData[line].npos ||
			game.lineData[line].find("0NSSS0") != game.lineData[line].npos)
		{
			format.aliveFour += 1;
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
			format.rushFour += 1; isFindRushFour = true;
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
			format.aliveThree += (!isFindRushFour) ? 1 : 0;
		}
		if (game.lineData[line].find("OOOON") != game.lineData[line].npos ||
			game.lineData[line].find("OOONO") != game.lineData[line].npos ||
			game.lineData[line].find("OONOO") != game.lineData[line].npos ||
			game.lineData[line].find("ONOOO") != game.lineData[line].npos ||
			game.lineData[line].find("NOOOO") != game.lineData[line].npos)
		{
			format.endFour += 1; isFindEndFour = true;
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
			format.endThree += (!isFindEndFour) ? 1 : 0;
		}
		if (game.lineData[line].find("0SN0") != game.lineData[line].npos ||
			game.lineData[line].find("0NS0") != game.lineData[line].npos)
		{
			format.aliveTwo += 1;
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
			format.preFour += 1; isFindPreFour = true;
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
			format.preThree += (!isFindPreFour) ? 1 : 0;
		}
	}
}

void AIPlayer::analysisData(Point pos)
{
	if (format.rushFive > 0)													{ score = 30; }
	else if (format.endFour > 1)												{ score = 29; }
	else if (format.endFour > 0 && format.rushFour > 0)							{ score = 28; }
	else if (format.endFour > 0 && format.endThree > 0)							{ score = 27; }
	else if (format.endFour > 0 && format.aliveThree > 0)						{ score = 26; }
	else if (format.endFour > 0)												{ score = 25; }
	else if (format.aliveFour > 0)												{ score = 24; }
	else if (format.rushFour > 1)												{ score = 23; }
	else if (format.rushFour > 0 && format.aliveThree > 0)						{ score = 22; }
	else if (format.rushFour > 0 && format.endThree > 0)						{ score = 21; }
	else if (format.endThree > 1)												{ score = 20; }
	else if (format.endThree > 0 && format.preFour > 1)							{ score = 19; }
	else if (format.endThree > 0 && format.preFour > 0 && format.preThree > 0)	{ score = 18; }
	else if (format.endThree > 0 && format.aliveThree > 0)						{ score = 17; }
	else if (format.endThree > 0)												{ score = 16; }
	else if (format.preFour > 1)												{ score = 15; }
	else if (format.preFour > 0 && format.preThree > 0)							{ score = 14; }
	else if (format.aliveThree > 1)												{ score = 13; }
	else if (format.aliveThree > 0 && format.linkTwo > 2)						{ score = 12; }
	else if (format.aliveThree > 0 && format.linkTwo > 1)						{ score = 11; }
	else if (format.aliveThree > 0 && format.linkTwo > 0)						{ score = 10; }
	else if (format.aliveThree > 0)												{ score = 9; }
	else if (format.preThree > 1)												{ score = 8; }
	else if (format.rushFour > 0 && format.linkTwo > 2)							{ score = 7; }
	else if (format.rushFour > 0 && format.linkTwo > 1)							{ score = 6; }
	else if (format.rushFour > 0 && format.linkTwo > 0)							{ score = 5; }
	else if (format.rushFour > 0)												{ score = 4; }
	else if (format.aliveTwo > 2)												{ score = 3; }
	else if (format.aliveTwo > 1)												{ score = 2; }
	else if (format.aliveTwo > 0)												{ score = 1; }

	if (score > maxScore)
	{
		maxScore = score;
		bestPoint = pos;
	}
}

void AIPlayer::autoPlay()
{
	static Point position;

	if (maxScore == 0)
	{
		if (side == WHITE_SIDE)
		{
			while (true)
			{
				int x = (rand() % 3) - 1 + game.temp.x;
				int y = (rand() % 3) - 1 + game.temp.y;

				if (game.chessBoard[x][y] == EMPTY_CHESS && x < TABLE_LARGE && y < TABLE_LARGE && x >= 0 && y >= 0)
				{
					position = { x, y };
					break;
				}
			}
		}
		else { position = { TABLE_LARGE / 2, TABLE_LARGE / 2 }; }
	}
	else { position = bestPoint; }

	game.temp = position;
	game.chessBoard[position.x][position.y] = chessColor;
	game.turn = -game.turn;
	game.turnCount += 1;
	maxScore = 0;
}