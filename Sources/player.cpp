#include "player.h"

void Player::init(Side side, Chess chess, Board* boardPtr)
{
	this->side = side;
	this->chess = chess;
	this->boardPtr = boardPtr;
}

void Player::play(int x, int y)
{
	boardPtr->play(chess, x, y);
}

Side Player::getSide()
{
	return side;
}

void PlayerAI::init(Side side, Chess chess, Board* boardPtr)
{
	Player::init(side, chess, boardPtr);
	maxScore = 0;
}

void PlayerAI::identify(LineData& lineData)
{
	for (int line = 0; line < Board::LINE_COUNT; line++)
	{
		for (int i = 0; i < lineData[line].size(); i++)
		{
			if (lineData[line][i] != (char)Chess::EMPTY && lineData[line][i] != (char)Chess::NOW)
			{
				switch (lineData[line][i] == (char)chess)
				{
					case true:  lineData[line][i] = (char)Chess::SELF; break;
					case false: lineData[line][i] = (char)Chess::OPPOSITE; break;
				}
			}
		}
	}
}

void PlayerAI::clearFormatData()
{
	memset(&format, 0, sizeof(format));
}

void PlayerAI::getFormatData(LineData& lineData)
{
	for (int line = 0; line < Board::LINE_COUNT; line++)
	{
		bool isFindRushFour = false;
		bool isFindEndFour = false;
		bool isFindPreFour = false;

		if (lineData[line].find("SSSSN") != lineData[line].npos ||
			lineData[line].find("SSSNS") != lineData[line].npos ||
			lineData[line].find("SSNSS") != lineData[line].npos ||
			lineData[line].find("SNSSS") != lineData[line].npos ||
			lineData[line].find("NSSSS") != lineData[line].npos)
		{
			format.rushFive += 1;
		}
		if (lineData[line].find("0SSSN0") != lineData[line].npos ||
			lineData[line].find("0SSNS0") != lineData[line].npos ||
			lineData[line].find("0SNSS0") != lineData[line].npos ||
			lineData[line].find("0NSSS0") != lineData[line].npos)
		{
			format.aliveFour += 1;
		}
		if (lineData[line].find("SSSN0") != lineData[line].npos ||
			lineData[line].find("SSNS0") != lineData[line].npos ||
			lineData[line].find("SNSS0") != lineData[line].npos ||
			lineData[line].find("NSSS0") != lineData[line].npos ||
			lineData[line].find("SSS0N") != lineData[line].npos ||
			lineData[line].find("SSN0S") != lineData[line].npos ||
			lineData[line].find("SNS0S") != lineData[line].npos ||
			lineData[line].find("NSS0S") != lineData[line].npos ||
			lineData[line].find("SS0SN") != lineData[line].npos ||
			lineData[line].find("SS0NS") != lineData[line].npos ||
			lineData[line].find("SN0SS") != lineData[line].npos ||
			lineData[line].find("NS0SS") != lineData[line].npos ||
			lineData[line].find("S0SSN") != lineData[line].npos ||
			lineData[line].find("S0SNS") != lineData[line].npos ||
			lineData[line].find("S0NSS") != lineData[line].npos ||
			lineData[line].find("N0SSS") != lineData[line].npos ||
			lineData[line].find("0SSSN") != lineData[line].npos ||
			lineData[line].find("0SSNS") != lineData[line].npos ||
			lineData[line].find("0SNSS") != lineData[line].npos ||
			lineData[line].find("0NSSS") != lineData[line].npos)
		{
			format.rushFour += 1; isFindRushFour = true;
		}
		if (lineData[line].find("0SSN00") != lineData[line].npos ||
			lineData[line].find("0SNS00") != lineData[line].npos ||
			lineData[line].find("0NSS00") != lineData[line].npos ||
			lineData[line].find("00SSN0") != lineData[line].npos ||
			lineData[line].find("00SNS0") != lineData[line].npos ||
			lineData[line].find("00NSS0") != lineData[line].npos ||
			lineData[line].find("0SS0N0") != lineData[line].npos ||
			lineData[line].find("0SN0S0") != lineData[line].npos ||
			lineData[line].find("0NS0S0") != lineData[line].npos ||
			lineData[line].find("0S0SN0") != lineData[line].npos ||
			lineData[line].find("0S0NS0") != lineData[line].npos ||
			lineData[line].find("0N0SS0") != lineData[line].npos)
		{
			format.aliveThree += (!isFindRushFour) ? 1 : 0;
		}
		if (lineData[line].find("OOOON") != lineData[line].npos ||
			lineData[line].find("OOONO") != lineData[line].npos ||
			lineData[line].find("OONOO") != lineData[line].npos ||
			lineData[line].find("ONOOO") != lineData[line].npos ||
			lineData[line].find("NOOOO") != lineData[line].npos)
		{
			format.endFour += 1; isFindEndFour = true;
		}
		if (lineData[line].find("0OOON0") != lineData[line].npos ||
			lineData[line].find("0NOOO0") != lineData[line].npos ||
			lineData[line].find("0OONO0") != lineData[line].npos ||
			lineData[line].find("0OO0ON") != lineData[line].npos ||
			lineData[line].find("NOO0O0") != lineData[line].npos ||
			lineData[line].find("0ONOO0") != lineData[line].npos ||
			lineData[line].find("NO0OO0") != lineData[line].npos ||
			lineData[line].find("0O0OON") != lineData[line].npos)
		{
			format.endThree += (!isFindEndFour) ? 1 : 0;
		}
		if (lineData[line].find("0SN0") != lineData[line].npos ||
			lineData[line].find("0NS0") != lineData[line].npos)
		{
			format.aliveTwo += 1;
		}
		if (lineData[line].find("SN") != lineData[line].npos ||
			lineData[line].find("NS") != lineData[line].npos)
		{
			format.linkTwo += 1;
		}
		if (lineData[line].find("OOON0") != lineData[line].npos ||
			lineData[line].find("OONO0") != lineData[line].npos ||
			lineData[line].find("ONOO0") != lineData[line].npos ||
			lineData[line].find("NOOO0") != lineData[line].npos ||
			lineData[line].find("OOO0N") != lineData[line].npos ||
			lineData[line].find("OON0O") != lineData[line].npos ||
			lineData[line].find("ONO0O") != lineData[line].npos ||
			lineData[line].find("NOO0O") != lineData[line].npos ||
			lineData[line].find("OO0ON") != lineData[line].npos ||
			lineData[line].find("OO0NO") != lineData[line].npos ||
			lineData[line].find("ON0OO") != lineData[line].npos ||
			lineData[line].find("NO0OO") != lineData[line].npos ||
			lineData[line].find("O0OON") != lineData[line].npos ||
			lineData[line].find("O0ONO") != lineData[line].npos ||
			lineData[line].find("O0NOO") != lineData[line].npos ||
			lineData[line].find("N0OOO") != lineData[line].npos ||
			lineData[line].find("0OOON") != lineData[line].npos ||
			lineData[line].find("0OONO") != lineData[line].npos ||
			lineData[line].find("0ONOO") != lineData[line].npos ||
			lineData[line].find("0NOOO") != lineData[line].npos)
		{
			format.preFour += 1; isFindPreFour = true;
		}
		if (lineData[line].find("0OON00") != lineData[line].npos ||
			lineData[line].find("0ONO00") != lineData[line].npos ||
			lineData[line].find("0NOO00") != lineData[line].npos ||
			lineData[line].find("00OON0") != lineData[line].npos ||
			lineData[line].find("00ONO0") != lineData[line].npos ||
			lineData[line].find("00NOO0") != lineData[line].npos ||
			lineData[line].find("0OO0N0") != lineData[line].npos ||
			lineData[line].find("0ON0O0") != lineData[line].npos ||
			lineData[line].find("0NO0O0") != lineData[line].npos ||
			lineData[line].find("0O0ON0") != lineData[line].npos ||
			lineData[line].find("0O0NO0") != lineData[line].npos ||
			lineData[line].find("0N0OO0") != lineData[line].npos)
		{
			format.preThree += (!isFindPreFour) ? 1 : 0;
		}
	}
}

void PlayerAI::analysisData(int x, int y)
{
	int score = 0;

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
		bestPoint.x = x;
		bestPoint.y = y;
	}
}

void PlayerAI::analysis()
{
	for (int x = 0; x < Board::LARGE; x++)
	{
		for (int y = 0; y < Board::LARGE; y++)
		{
			if (boardPtr->getTableData(x, y) == Chess::EMPTY)
			{
				LineData lineData = boardPtr->getLineData(x, y, true);

				identify(lineData);
				clearFormatData();
				getFormatData(lineData);
				analysisData(x, y);
			}
		}
	}
}

void PlayerAI::play()
{
	if (maxScore == 0)
	{
		if (side == Side::WHITE)
		{
			while (true)
			{
				int x = (rand() % 3) - 1 + boardPtr->getTempX();
				int y = (rand() % 3) - 1 + boardPtr->getTempY();

				if (boardPtr->getTableData(x, y) == Chess::EMPTY && x < Board::LARGE && y < Board::LARGE && x >= 0 && y >= 0)
				{
					boardPtr->play(chess, x, y);
					break;
				}
			}
		}
		else { boardPtr->play(chess, Board::LARGE / 2, Board::LARGE / 2); }
	}
	else { boardPtr->play(chess, bestPoint.x, bestPoint.y); }

	maxScore = 0;
}