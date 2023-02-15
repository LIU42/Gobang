#include "board.h"

void Board::init()
{
	for (int x = 0; x < LARGE; x++)
	{
		for (int y = 0; y < LARGE; y++)
		{
			table[x][y] = Chess::EMPTY;
		}
	}
}

void Board::play(Chess chess, int x, int y)
{
	tempPoint.x = x;
	tempPoint.y = y;
	table[x][y] = chess;
}

int Board::getTempX()
{
	return tempPoint.x;
}

int Board::getTempY()
{
	return tempPoint.y;
}

bool Board::isBlackWin(LineData& lineData)
{
	for (string& line : lineData)
	{
		if (line.find("BBBBB") != line.npos)
		{
			return true;
		}
	}
	return false;
}

bool Board::isWhiteWin(LineData& lineData)
{
	for (string& line : lineData)
	{
		if (line.find("WWWWW") != line.npos)
		{
			return true;
		}
	}
	return false;
}

Chess Board::getTableData(int x, int y)
{
	return table[x][y];
}

LineData Board::getLineData(int x, int y, bool isNeedNowFlag)
{
	LineData lineData(LINE_COUNT);

	if (isNeedNowFlag)
	{
		tempChess = table[x][y];
		table[x][y] = Chess::NOW;
	}
	for (int line = 0; line < LINE_COUNT; line++)
	{
		lineData[line].clear();
	}
	for (int i = 0; i < LARGE; i++)
	{
		lineData[0] += (char)table[x][i];
		lineData[1] += (char)table[i][y];
	}
	switch (x > y)
	{
		case true:  for (int i = 0; i < LARGE - (x - y); i++) { lineData[2] += (char)table[i + x - y][i]; } break;
		case false: for (int i = 0; i < LARGE - (y - x); i++) { lineData[2] += (char)table[i][i + y - x]; } break;
	}
	switch (x + y < LARGE)
	{
		case true:  for (int i = 0; i <= x + y; i++) { lineData[3] += (char)table[i][x + y - i]; } break;
		case false: for (int i = x + y - LARGE + 1; i < LARGE; i++) { lineData[3] += (char)table[i][x + y - i]; } break;
	}
	if (isNeedNowFlag)
	{
		table[x][y] = tempChess;
	}
	return lineData;
}

LinkData Board::getLinkData(LineData& lineData)
{
	LinkData linkData(LINK_COUNT);

	int x = tempPoint.x;
	int y = tempPoint.y;

	for (int line = 0; line < LINE_COUNT; line++)
	{
		bool isBlackWin = (lineData[line].find("BBBBB") != lineData[line].npos);
		bool isWhiteWin = (lineData[line].find("WWWWW") != lineData[line].npos);

		int winInit = 0;

		if (!isBlackWin && !isWhiteWin)
		{
			continue;
		}
		switch (isBlackWin)
		{
			case true:  winInit = (int)lineData[line].find("BBBBB"); break;
			case false: winInit = (int)lineData[line].find("WWWWW"); break;
		}
		for (int i = 0; i < LINK_COUNT; i++) switch (line)
		{
			case 0: linkData[i] = { x, winInit + i }; break;
			case 1: linkData[i] = { winInit + i, y }; break;

			case 2: switch (x > y)
			{
				case true:  linkData[i] = { winInit + i + (x - y), winInit + i }; break;
				case false: linkData[i] = { winInit + i, winInit + i + (y - x) }; break;
			}; break;

			case 3: switch (x + y < LARGE)
			{
				case true:  linkData[i] = { winInit + i, x + y - winInit - i }; break;
				case false: linkData[i] = { winInit + i + x + y - LARGE + 1, LARGE - winInit - i - 1 }; break;
			}; break;
		}
		break;
	}
	return linkData;
}
