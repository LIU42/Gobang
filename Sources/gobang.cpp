#include "gobang.h"

using namespace std;

SDL_RWops* MainGame::getResource(HINSTANCE hInst, LPCWSTR name, LPCWSTR type)
{
	HRSRC hRsrc = FindResource(hInst, name, type);
	DWORD size = SizeofResource(hInst, hRsrc);
	LPVOID data = LockResource(LoadResource(hInst, hRsrc));
	return SDL_RWFromConstMem(data, size);
}

SDL_Surface* MainGame::loadSurface(int id)
{
	SDL_RWops* src = getResource(hInstance, MAKEINTRESOURCE(id), TEXT("PNG"));
	SDL_Surface* originSurface = IMG_LoadPNG_RW(src);
	SDL_Surface* convertSurface = SDL_ConvertSurface(originSurface, image.format, NULL);
	SDL_FreeSurface(originSurface);
	SDL_FreeRW(src);
	return convertSurface;
}

void MainGame::initWindow()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	hInstance = GetModuleHandle(0);
	window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_GetWindowSize(window, &rect.screen.w, &rect.screen.h);
}

void MainGame::loadFont()
{
	TTF_Init();
	font = TTF_OpenFontRW(getResource(hInstance, MAKEINTRESOURCE(IDR_FONT1), RT_FONT), 1, FONT_SIZE);
}

void MainGame::loadImage()
{
	image.format = SDL_AllocFormat(IMG_FORMAT);
	image.surface = SDL_GetWindowSurface(window);
	image.background = loadSurface(IDB_PNG3);
	image.blackChess = loadSurface(IDB_PNG2);
	image.whiteChess = loadSurface(IDB_PNG4);
	image.alert = loadSurface(IDB_PNG1);
}

void MainGame::freeImage()
{
	SDL_FreeFormat(image.format);
	SDL_FreeSurface(image.background);
	SDL_FreeSurface(image.blackChess);
	SDL_FreeSurface(image.whiteChess);
	SDL_FreeSurface(image.alert);
}

void MainGame::freeFont() { TTF_CloseFont(font); }

void MainGame::close()
{
	SDL_DestroyWindow(window);
	freeImage();
	freeFont();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void MainGame::initGame()
{
	for (int x = 0; x < TABLE_LARGE; x++)
	{
		for (int y = 0; y < TABLE_LARGE; y++)
		{
			chessBoard[x][y] = EMPTY_CHESS;
		}
	}
	status = PLAYING;
	turn = BLACK_SIDE;
	turnCount = 0;
	winner = NONE_SIDE;

	switch (rand() % 2)
	{
		case 0: player.init(BLACK_SIDE, BLACK_CHESS); ai.init(WHITE_SIDE, WHITE_CHESS); break;
		case 1: player.init(WHITE_SIDE, WHITE_CHESS); ai.init(BLACK_SIDE, BLACK_CHESS); break;
	}
}

void MainGame::getLineData(int x, int y)
{
	char tempChess = chessBoard[x][y];
	chessBoard[x][y] = NOW_CHESS;

	for (int line = 0; line < 4; line++) { lineData[line].clear(); }
	for (int i = 0; i < TABLE_LARGE; i++)
	{
		lineData[0] += chessBoard[x][i];
		lineData[1] += chessBoard[i][y];
	}
	switch ((bool)(x > y))
	{
		case true: for (int i = 0; i < TABLE_LARGE - (x - y); i++) { lineData[2] += chessBoard[i + x - y][i]; } break;
		case false: for (int i = 0; i < TABLE_LARGE - (y - x); i++) { lineData[2] += chessBoard[i][i + y - x]; } break;
	}
	switch ((bool)(x + y < TABLE_LARGE))
	{
		case true: for (int i = 0; i <= x + y; i++) { lineData[3] += chessBoard[i][x + y - i]; } break;
		case false: for (int i = x + y - TABLE_LARGE + 1; i < TABLE_LARGE; i++) { lineData[3] += chessBoard[i][x + y - i]; } break;
	}
	chessBoard[x][y] = tempChess;
}

void MainGame::gameover()
{
	getLineData(temp.x, temp.y);

	for (int line = 0; line < LINE_COUNT; line++)
	{
		for (int i = 0; i < lineData[line].size(); i++)
		{
			if (lineData[line][i] == NOW_CHESS)
			{
				lineData[line][i] = (turn == WHITE_SIDE) ? BLACK_CHESS : WHITE_CHESS;
			}
		}
	}
	for (int line = 0; line < LINE_COUNT; line++)
	{
		bool isBlackWin = (lineData[line].find("BBBBB") != lineData[line].npos);
		bool isWhiteWin = (lineData[line].find("WWWWW") != lineData[line].npos);
		int position = 0;

		if (isBlackWin || isWhiteWin)
		{
			switch (isBlackWin)
			{
				case true:  winner = BLACK_SIDE; position = (int)lineData[line].find("BBBBB"); break;
				case false: winner = WHITE_SIDE; position = (int)lineData[line].find("WWWWW"); break;
			}
			switch (line)
			{
				case 0: for (int i = 0; i < WIN_CHESS_COUNT; i++) { winPoint[i] = { temp.x, position + i }; } break;
				case 1: for (int i = 0; i < WIN_CHESS_COUNT; i++) { winPoint[i] = { position + i, temp.y }; } break;
				case 2: for (int i = 0; i < WIN_CHESS_COUNT; i++)
				{
					if (temp.x > temp.y) { winPoint[i] = { position + i + (temp.x - temp.y),position + i }; }
					else { winPoint[i] = { position + i,position + i + (temp.y - temp.x) }; }
				} break;

				default: for (int i = 0; i < WIN_CHESS_COUNT; i++)
				{
					if (temp.x + temp.y < TABLE_LARGE) { winPoint[i] = { position + i,temp.x + temp.y - position - i }; }
					else { winPoint[i] = { position + i + temp.x + temp.y - TABLE_LARGE + 1,TABLE_LARGE - position - i - 1 }; }
				} break;
			}
			status = OVER;
		}
	}
}

void MainGame::update()
{
	if (status == PLAYING && turn == ai.side)
	{
		for (int x = 0; x < TABLE_LARGE; x++)
		{
			for (int y = 0; y < TABLE_LARGE; y++)
			{
				if (chessBoard[x][y] == EMPTY_CHESS)
				{
					getLineData(x, y);
					ai.identify();
					ai.clearFormatData();
					ai.getFormatData();
					ai.analysisData(x, y);
				}
			}
		}
		ai.play();
		gameover();
	}
}

void MainGame::control()
{
	while (SDL_PollEvent(&events))
	{
		if (events.type == SDL_QUIT) { status = EXIT; }
		if (events.type == SDL_MOUSEBUTTONDOWN)
		{
			if (status == PLAYING)
			{
				int mouseX = events.motion.x;
				int mouseY = events.motion.y;

				if (mouseX >= REGION_BORDER && mouseX <= SCREEN_WIDTH - REGION_BORDER && mouseY >= REGION_BORDER && mouseY <= SCREEN_WIDTH - REGION_BORDER)
				{
					int x = (int)((mouseX - BORDER - BLOCK / 2) / BLOCK);
					int y = (int)((mouseY - BORDER - BLOCK / 2) / BLOCK);

					if (chessBoard[x][y] == EMPTY_CHESS && turn == player.side)
					{
						player.play(x, y);
						gameover();
					}
				}
			}
			else if (status == OVER)
			{
				status = PLAYING;
				initGame();
			}
		}
	}
}

void MainGame::displayText(const char* text, int x, int y)
{
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, TEXT_COLOR);
	SDL_Rect textRect = { x, y, TEXT_RECT_WIDTH, TEXT_RECT_HEIGHT };
	SDL_BlitSurface(textSurface, NULL, image.surface, &textRect);
	SDL_FreeSurface(textSurface);
}

void MainGame::displayChess()
{
	if (status == OVER)
	{
		for (int i = 0; i < WIN_CHESS_COUNT; i++)
		{
			rect.block = { BORDER + (int)(BLOCK * (winPoint[i].x + 0.5)), BORDER + (int)(BLOCK * (winPoint[i].y + 0.5)), BLOCK, BLOCK };
			SDL_BlitSurface(image.alert, NULL, image.surface, &rect.block);
		}
	}
	else if (turnCount != 0)
	{
		rect.block = { BORDER + (int)(BLOCK * (temp.x + 0.5)), BORDER + (int)(BLOCK * (temp.y + 0.5)), BLOCK, BLOCK };
		SDL_BlitSurface(image.alert, NULL, image.surface, &rect.block);
	}
	for (int x = 0; x < TABLE_LARGE; x++)
	{
		for (int y = 0; y < TABLE_LARGE; y++)
		{
			if (chessBoard[x][y] == BLACK_CHESS)
			{
				rect.block = { BORDER + (int)(BLOCK * (x + 0.5)), BORDER + (int)(BLOCK * (y + 0.5)), BLOCK, BLOCK };
				SDL_BlitSurface(image.blackChess, NULL, image.surface, &rect.block);
			}
			else if (chessBoard[x][y] == WHITE_CHESS)
			{
				rect.block = { BORDER + (int)(BLOCK * (x + 0.5)), BORDER + (int)(BLOCK * (y + 0.5)), BLOCK, BLOCK };
				SDL_BlitSurface(image.whiteChess, NULL, image.surface, &rect.block);
			}
		}
	}
}

void MainGame::displayInfo()
{
	static char text[TEXT_MAX_LEN];

	if (status == PLAYING)
	{
		switch (player.side)
		{
			case BLACK_SIDE: SDL_snprintf(text, TEXT_MAX_LEN, "-> You are BLACK"); break;
			case WHITE_SIDE: SDL_snprintf(text, TEXT_MAX_LEN, "-> You are WHITE"); break;
		}
	}
	else if (status == OVER)
	{
		switch (bool(winner == player.side))
		{
			case true: SDL_snprintf(text, TEXT_MAX_LEN, "-> Winner!"); break;
			case false: SDL_snprintf(text, TEXT_MAX_LEN, "-> Loser!"); break;
		}
	}
	displayText(text, BORDER, SCREEN_HEIGHT - (BORDER + FONT_SIZE));
	SDL_snprintf(text, TEXT_MAX_LEN, "Turn: %d", game.turnCount);
	displayText(text, SCREEN_WIDTH - 120, SCREEN_HEIGHT - (BORDER + FONT_SIZE));
}

void MainGame::display()
{
	SDL_BlitSurface(image.background, NULL, image.surface, &rect.screen);
	displayChess();
	displayInfo();
	SDL_UpdateWindowSurface(window);
}