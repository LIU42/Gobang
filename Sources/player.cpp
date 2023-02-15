#include "player.h"

void Player::init(Side side, Chess chess, Board* pBoard)
{
	this->side = side;
	this->chess = chess;
	this->pBoard = pBoard;
}

void Player::play(int x, int y)
{
	pBoard->play(chess, x, y);
}

Side Player::getSide()
{
	return side;
}

void PlayerAI::init(Side side, Chess chess, Board* pBoard)
{
	Player::init(side, chess, pBoard);
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
	for (string& line : lineData)
	{
		bool isFindRushFour = false;
		bool isFindEndFour = false;
		bool isFindPreFour = false;

		if (line.find("SSSSN") != line.npos ||
			line.find("SSSNS") != line.npos ||
			line.find("SSNSS") != line.npos ||
			line.find("SNSSS") != line.npos ||
			line.find("NSSSS") != line.npos)
		{
			format.rushFive += 1;
		}
		if (line.find("0SSSN0") != line.npos ||
			line.find("0SSNS0") != line.npos ||
			line.find("0SNSS0") != line.npos ||
			line.find("0NSSS0") != line.npos)
		{
			format.aliveFour += 1;
		}
		if (line.find("SSSN0") != line.npos ||
			line.find("SSNS0") != line.npos ||
			line.find("SNSS0") != line.npos ||
			line.find("NSSS0") != line.npos ||
			line.find("SSS0N") != line.npos ||
			line.find("SSN0S") != line.npos ||
			line.find("SNS0S") != line.npos ||
			line.find("NSS0S") != line.npos ||
			line.find("SS0SN") != line.npos ||
			line.find("SS0NS") != line.npos ||
			line.find("SN0SS") != line.npos ||
			line.find("NS0SS") != line.npos ||
			line.find("S0SSN") != line.npos ||
			line.find("S0SNS") != line.npos ||
			line.find("S0NSS") != line.npos ||
			line.find("N0SSS") != line.npos ||
			line.find("0SSSN") != line.npos ||
			line.find("0SSNS") != line.npos ||
			line.find("0SNSS") != line.npos ||
			line.find("0NSSS") != line.npos)
		{
			format.rushFour += 1; isFindRushFour = true;
		}
		if (line.find("0SSN00") != line.npos ||
			line.find("0SNS00") != line.npos ||
			line.find("0NSS00") != line.npos ||
			line.find("00SSN0") != line.npos ||
			line.find("00SNS0") != line.npos ||
			line.find("00NSS0") != line.npos ||
			line.find("0SS0N0") != line.npos ||
			line.find("0SN0S0") != line.npos ||
			line.find("0NS0S0") != line.npos ||
			line.find("0S0SN0") != line.npos ||
			line.find("0S0NS0") != line.npos ||
			line.find("0N0SS0") != line.npos)
		{
			format.aliveThree += (!isFindRushFour) ? 1 : 0;
		}
		if (line.find("OOOON") != line.npos ||
			line.find("OOONO") != line.npos ||
			line.find("OONOO") != line.npos ||
			line.find("ONOOO") != line.npos ||
			line.find("NOOOO") != line.npos)
		{
			format.endFour += 1; isFindEndFour = true;
		}
		if (line.find("0OOON0") != line.npos ||
			line.find("0NOOO0") != line.npos ||
			line.find("0OONO0") != line.npos ||
			line.find("0OO0ON") != line.npos ||
			line.find("NOO0O0") != line.npos ||
			line.find("0ONOO0") != line.npos ||
			line.find("NO0OO0") != line.npos ||
			line.find("0O0OON") != line.npos)
		{
			format.endThree += (!isFindEndFour) ? 1 : 0;
		}
		if (line.find("0SN0") != line.npos ||
			line.find("0NS0") != line.npos)
		{
			format.aliveTwo += 1;
		}
		if (line.find("SN") != line.npos ||
			line.find("NS") != line.npos)
		{
			format.linkTwo += 1;
		}
		if (line.find("OOON0") != line.npos ||
			line.find("OONO0") != line.npos ||
			line.find("ONOO0") != line.npos ||
			line.find("NOOO0") != line.npos ||
			line.find("OOO0N") != line.npos ||
			line.find("OON0O") != line.npos ||
			line.find("ONO0O") != line.npos ||
			line.find("NOO0O") != line.npos ||
			line.find("OO0ON") != line.npos ||
			line.find("OO0NO") != line.npos ||
			line.find("ON0OO") != line.npos ||
			line.find("NO0OO") != line.npos ||
			line.find("O0OON") != line.npos ||
			line.find("O0ONO") != line.npos ||
			line.find("O0NOO") != line.npos ||
			line.find("N0OOO") != line.npos ||
			line.find("0OOON") != line.npos ||
			line.find("0OONO") != line.npos ||
			line.find("0ONOO") != line.npos ||
			line.find("0NOOO") != line.npos)
		{
			format.preFour += 1; isFindPreFour = true;
		}
		if (line.find("0OON00") != line.npos ||
			line.find("0ONO00") != line.npos ||
			line.find("0NOO00") != line.npos ||
			line.find("00OON0") != line.npos ||
			line.find("00ONO0") != line.npos ||
			line.find("00NOO0") != line.npos ||
			line.find("0OO0N0") != line.npos ||
			line.find("0ON0O0") != line.npos ||
			line.find("0NO0O0") != line.npos ||
			line.find("0O0ON0") != line.npos ||
			line.find("0O0NO0") != line.npos ||
			line.find("0N0OO0") != line.npos)
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
			if (pBoard->getTableData(x, y) == Chess::EMPTY)
			{
				LineData lineData = pBoard->getLineData(x, y, true);

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
				int x = (rand() % 3) - 1 + pBoard->getTempX();
				int y = (rand() % 3) - 1 + pBoard->getTempY();

				if (pBoard->getTableData(x, y) == Chess::EMPTY && x < Board::LARGE && y < Board::LARGE && x >= 0 && y >= 0)
				{
					pBoard->play(chess, x, y);
					break;
				}
			}
		}
		else { pBoard->play(chess, Board::LARGE / 2, Board::LARGE / 2); }
	}
	else { pBoard->play(chess, bestPoint.x, bestPoint.y); }

	maxScore = 0;
}