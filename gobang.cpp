#include "gobang.h"

using namespace std;

SDL_RWops* Window::getResource(HINSTANCE hInst, LPCWSTR name, LPCWSTR type)
{
	HRSRC hRsrc = FindResource(hInst, name, type);
	DWORD size = SizeofResource(hInst, hRsrc);
	LPVOID data = LockResource(LoadResource(hInst, hRsrc));
	return SDL_RWFromConstMem(data, size);
}

SDL_Surface* Window::loadSurface(DWORD ID)
{
	SDL_RWops* src = getResource(hInstance, MAKEINTRESOURCE(ID), TEXT("PNG"));
	SDL_Surface* originImage = IMG_LoadPNG_RW(src);
	SDL_Surface* convertImage = SDL_ConvertSurface(originImage, format, NULL);
	SDL_FreeSurface(originImage);
	SDL_FreeRW(src);
	return convertImage;
}

void Window::text(const char* text, int x, int y)
{
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, TEXT_COLOR);
	SDL_Rect textRect = { x, y, TEXT_RECT_WIDTH, TEXT_RECT_HEIGHT };
	SDL_BlitSurface(textSurface, NULL, surface, &textRect);
	SDL_FreeSurface(textSurface);
}

void Window::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	hInstance = GetModuleHandle(0);
	window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	surface = SDL_GetWindowSurface(window);
	screenRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	format = SDL_AllocFormat(IMG_FORMAT);
}

void Window::loadFont()
{
	TTF_Init();
	font = TTF_OpenFontRW(getResource(hInstance, MAKEINTRESOURCE(IDR_FONT1), RT_FONT), 1, FONT_SIZE);
}

void Window::loadImage()
{
	backgroundImg = loadSurface(IDB_PNG3);
	blackChessImg = loadSurface(IDB_PNG2);
	whiteChessImg = loadSurface(IDB_PNG4);
	alertImg = loadSurface(IDB_PNG1);
}

void Window::freeImage()
{
	SDL_FreeSurface(backgroundImg);
	SDL_FreeSurface(blackChessImg);
	SDL_FreeSurface(whiteChessImg);
	SDL_FreeSurface(alertImg);
}

void Window::freeFont() { TTF_CloseFont(font); }

void Window::close()
{
	SDL_DestroyWindow(window);
	SDL_FreeFormat(format);
	freeImage();
	freeFont();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

Game::Game() : random((unsigned)time(NULL)), randDev(-1, 1) {}

void Game::init()
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

	if (randP(random))
	{
		userPlayer.init(BLACK_SIDE, BLACK_CHESS);
		aiPlayer.init(WHITE_SIDE, WHITE_CHESS);
	}
	else
	{
		userPlayer.init(WHITE_SIDE, WHITE_CHESS);
		aiPlayer.init(BLACK_SIDE, BLACK_CHESS);
	}
}

void Game::getLineData(int x, int y)
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

void Game::gameover()
{
	getLineData(temp.x, temp.y);
	for (int line = 0; line < 4; line++)
	{
		for (int i = 0; i < lineData[line].size(); i++)
		{
			if (lineData[line][i] == NOW_CHESS)
			{
				lineData[line][i] = (turn == WHITE_SIDE) ? BLACK_CHESS : WHITE_CHESS;
			}
		}
	}
	for (int line = 0; line < 4; line++)
	{
		bool isBlackWin = (lineData[line].find("BBBBB") != lineData[line].npos);
		bool isWhiteWin = (lineData[line].find("WWWWW") != lineData[line].npos);
		int position = 0;

		if (isBlackWin || isWhiteWin)
		{
			if (isBlackWin)
			{
				winner = BLACK_SIDE;
				position = (int)lineData[line].find("BBBBB");
			}
			else
			{
				winner = WHITE_SIDE;
				position = (int)lineData[line].find("WWWWW");
			}
			switch (line)
			{
				case 0: for (int i = 0; i < 5; i++) { winPoint[i] = { temp.x, position + i }; } break;
				case 1: for (int i = 0; i < 5; i++) { winPoint[i] = { position + i, temp.y }; } break;
				case 2: for (int i = 0; i < 5; i++)
				{
					if (temp.x > temp.y) { winPoint[i] = { position + i + (temp.x - temp.y),position + i }; }
					else { winPoint[i] = { position + i,position + i + (temp.y - temp.x) }; }
				} break;

				default: for (int i = 0; i < 5; i++)
				{
					if (temp.x + temp.y < TABLE_LARGE) { winPoint[i] = { position + i,temp.x + temp.y - position - i }; }
					else { winPoint[i] = { position + i + temp.x + temp.y - TABLE_LARGE + 1,TABLE_LARGE - position - i - 1 }; }
				} break;
			}
			status = OVER;
		}
	}
}

void Game::update()
{
	if (status == PLAYING && turn == aiPlayer.side)
	{
		for (int x = 0; x < TABLE_LARGE; x++)
		{
			for (int y = 0; y < TABLE_LARGE; y++)
			{
				if (chessBoard[x][y] == EMPTY_CHESS)
				{
					getLineData(x, y);
					aiPlayer.identify();
					aiPlayer.analysis(x, y);
				}
			}
		}
		aiPlayer.play();
		gameover();
	}
}

void Game::events()
{
	while (SDL_PollEvent(&window.events))
	{
		if (window.events.type == SDL_QUIT) { status = EXIT; }
		if (window.events.type == SDL_MOUSEBUTTONDOWN)
		{
			if (status == PLAYING)
			{
				int mouseX = window.events.motion.x;
				int mouseY = window.events.motion.y;

				if (mouseX >= REGION_BORDER && mouseX <= SCREEN_WIDTH - REGION_BORDER && mouseY >= REGION_BORDER && mouseY <= SCREEN_WIDTH - REGION_BORDER)
				{
					int x = (int)((mouseX - BORDER - BLOCK * 0.5) / BLOCK);
					int y = (int)((mouseY - BORDER - BLOCK * 0.5) / BLOCK);

					if (chessBoard[x][y] == EMPTY_CHESS && turn == userPlayer.side)
					{
						userPlayer.play(x, y);
						gameover();
					}
				}
			}
			else if (status == OVER)
			{
				status = PLAYING;
				init();
			}
		}
	}
}

void Game::displayChess()
{
	if (game.status == OVER)
	{
		for (int i = 0; i < 5; i++)
		{
			window.blockRect = { BORDER + (int)(BLOCK * (winPoint[i].x + 0.5)), BORDER + (int)(BLOCK * (winPoint[i].y + 0.5)), BLOCK, BLOCK };
			SDL_BlitSurface(window.alertImg, NULL, window.surface, &window.blockRect);
		}
	}
	else if (game.turnCount != 0)
	{
		window.blockRect = { BORDER + (int)(BLOCK * (temp.x + 0.5)), BORDER + (int)(BLOCK * (temp.y + 0.5)), BLOCK, BLOCK };
		SDL_BlitSurface(window.alertImg, NULL, window.surface, &window.blockRect);
	}
	for (int x = 0; x < TABLE_LARGE; x++)
	{
		for (int y = 0; y < TABLE_LARGE; y++)
		{
			if (game.chessBoard[x][y] == BLACK_CHESS)
			{
				window.blockRect = { BORDER + (int)(BLOCK * (x + 0.5)), BORDER + (int)(BLOCK * (y + 0.5)), BLOCK, BLOCK };
				SDL_BlitSurface(window.blackChessImg, NULL, window.surface, &window.blockRect);
			}
			else if (game.chessBoard[x][y] == WHITE_CHESS)
			{
				window.blockRect = { BORDER + (int)(BLOCK * (x + 0.5)), BORDER + (int)(BLOCK * (y + 0.5)), BLOCK, BLOCK };
				SDL_BlitSurface(window.whiteChessImg, NULL, window.surface, &window.blockRect);
			}
		}
	}
}

void Game::displayInfo()
{
	if (status == PLAYING)
	{
		if (userPlayer.side == BLACK_SIDE) { SDL_snprintf(text, TEXT_MAX_LEN, "-> You are BLACK"); }
		else { SDL_snprintf(text, TEXT_MAX_LEN, "-> You are WHITE"); }
	}
	else if (status == OVER)
	{
		if (winner == userPlayer.side) { SDL_snprintf(text, TEXT_MAX_LEN, "-> Winner!"); }
		else { SDL_snprintf(text, TEXT_MAX_LEN, "-> Loser!"); }
	}
	window.text(text, BORDER, SCREEN_HEIGHT - (BORDER + FONT_SIZE));
	SDL_snprintf(text, TEXT_MAX_LEN, "Turn: %d", game.turnCount);
	window.text(text, SCREEN_WIDTH - 120, SCREEN_HEIGHT - (BORDER + FONT_SIZE));
}

void Game::display()
{
	SDL_BlitSurface(window.backgroundImg, NULL, window.surface, &window.screenRect);
	displayChess();
	displayInfo();
	SDL_UpdateWindowSurface(window.window);
}