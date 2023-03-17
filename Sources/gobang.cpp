#include "gobang.h"

SDL_RWops* MainGame::getResource(LPCWSTR name, LPCWSTR type)
{
	HINSTANCE hInst = windowInfo.info.win.hinstance;
	HRSRC hRsrc = FindResource(hInst, name, type);
	DWORD size = SizeofResource(hInst, hRsrc);
	HGLOBAL hGlobal = LoadResource(hInst, hRsrc);
	LPVOID data = LockResource(hGlobal);
	return SDL_RWFromConstMem(data, size);
}

SDL_Surface* MainGame::loadSurface(Uint32 id)
{
	SDL_RWops* pResource = getResource(MAKEINTRESOURCE(id), TEXT("PNG"));
	SDL_Surface* pOriginalSurface = IMG_LoadPNG_RW(pResource);
	SDL_Surface* pConvertedSurface = SDL_ConvertSurface(pOriginalSurface, pFormat, NULL);
	SDL_FreeSurface(pOriginalSurface);
	SDL_FreeRW(pResource);
	return pConvertedSurface;
}

void MainGame::getVersion()
{
	windowInfo.version.major = SDL_MAJOR_VERSION;
	windowInfo.version.minor = SDL_MINOR_VERSION;
	windowInfo.version.patch = SDL_PATCHLEVEL;
}

void MainGame::initSystem()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
}

void MainGame::initWindow()
{
	pWindow = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	pSurface = SDL_GetWindowSurface(pWindow);
	pFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
	screenRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_GetWindowWMInfo(pWindow, &windowInfo);
}

void MainGame::loadFont()
{
	fonts.pInfo = TTF_OpenFontRW(getResource(MAKEINTRESOURCE(IDR_FONT1), RT_FONT), 1, FONT_SIZE);
}

void MainGame::loadImage()
{
	images.pBackground = loadSurface(IDB_PNG3);
	images.pBlackChess = loadSurface(IDB_PNG2);
	images.pWhiteChess = loadSurface(IDB_PNG4);
	images.pAlert = loadSurface(IDB_PNG1);
}

void MainGame::freeImage()
{
	SDL_FreeSurface(images.pBackground);
	SDL_FreeSurface(images.pBlackChess);
	SDL_FreeSurface(images.pWhiteChess);
	SDL_FreeSurface(images.pAlert);
}

void MainGame::freeFont()
{
	TTF_CloseFont(fonts.pInfo);
}

void MainGame::closeWindow()
{
	SDL_DestroyWindow(pWindow);
	SDL_FreeFormat(pFormat);
}

void MainGame::closeSystem()
{
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void MainGame::initGame()
{
	switch (rand() % 2)
	{
		case 0: player.init(Side::BLACK, Chess::BLACK, &board); playerAI.init(Side::WHITE, Chess::WHITE, &board); break;
		case 1: player.init(Side::WHITE, Chess::WHITE, &board); playerAI.init(Side::BLACK, Chess::BLACK, &board); break;
	}
	board.init();
	status = PLAYING;
	turn = Side::BLACK;
	turnCount = 0;
	winner = Side::NOBODY;
}

void MainGame::turnSide()
{
	switch (turn)
	{
		case Side::BLACK: turn = Side::WHITE; break;
		case Side::WHITE: turn = Side::BLACK; break;
	}
	turnCount += 1;
}

void MainGame::gameover()
{
	int tempX = board.getTempX();
	int tempY = board.getTempY();

	LineData lineData = board.getLineData(tempX, tempY, false);

	if (board.isBlackWin(lineData))
	{
		winner = Side::BLACK;
		status = OVER;
	}
	else if (board.isWhiteWin(lineData))
	{
		winner = Side::WHITE;
		status = OVER;
	}
}

void MainGame::displayText(const char* pText, int x, int y)
{
	SDL_Surface* pTextSurface = TTF_RenderText_Blended(fonts.pInfo, pText, BLACK);
	SDL_Rect textRect = { x, y, 0, 0 };

	SDL_BlitSurface(pTextSurface, NULL, pSurface, &textRect);
	SDL_FreeSurface(pTextSurface);
}

void MainGame::displayChess()
{
	static SDL_Rect chessRect;

	int tempX = board.getTempX();
	int tempY = board.getTempY();

	if (status == OVER)
	{
		LineData lineData = board.getLineData(tempX, tempY, false);
		LinkData linkData = board.getLinkData(lineData);

		for (int i = 0; i < board.LINK_COUNT; i++)
		{
			chessRect.x = BORDER + (int)(BLOCK_SIZE * (linkData[i].x + 0.5));
			chessRect.y = BORDER + (int)(BLOCK_SIZE * (linkData[i].y + 0.5));

			SDL_BlitSurface(images.pAlert, NULL, pSurface, &chessRect);
		}
	}
	else if (turnCount != 0)
	{
		chessRect.x = BORDER + (int)(BLOCK_SIZE * (tempX + 0.5));
		chessRect.y = BORDER + (int)(BLOCK_SIZE * (tempY + 0.5));

		SDL_BlitSurface(images.pAlert, NULL, pSurface, &chessRect);
	}
	for (int x = 0; x < board.LARGE; x++)
	{
		for (int y = 0; y < board.LARGE; y++)
		{
			chessRect.x = BORDER + (int)(BLOCK_SIZE * (x + 0.5));
			chessRect.y = BORDER + (int)(BLOCK_SIZE * (y + 0.5));

			switch (board.getTableData(x, y))
			{
				case Chess::BLACK: SDL_BlitSurface(images.pBlackChess, NULL, pSurface, &chessRect); break;
				case Chess::WHITE: SDL_BlitSurface(images.pWhiteChess, NULL, pSurface, &chessRect); break;
			}
		}
	}
}

void MainGame::displayInfo()
{
	static char text[TEXT_LENGTH];

	if (status == PLAYING)
	{
		switch (player.getSide())
		{
			case Side::BLACK: SDL_snprintf(text, TEXT_LENGTH, "-> You are BLACK"); break;
			case Side::WHITE: SDL_snprintf(text, TEXT_LENGTH, "-> You are WHITE"); break;
		}
	}
	else if (status == OVER)
	{
		switch (winner == player.getSide())
		{
			case true:  SDL_snprintf(text, TEXT_LENGTH, "-> Winner!"); break;
			case false: SDL_snprintf(text, TEXT_LENGTH, "-> Loser!"); break;
		}
	}
	displayText(text, BORDER, SCREEN_HEIGHT - (BORDER + FONT_SIZE));
	SDL_snprintf(text, TEXT_LENGTH, "Turn: %d", turnCount);
	displayText(text, SCREEN_WIDTH - TURN_INFO_LENGTH, SCREEN_HEIGHT - (BORDER + FONT_SIZE));
}

MainGame::MainGame()
{
	srand((unsigned)time(NULL));
	getVersion();
	initSystem();
	initWindow();
	initGame();
	loadImage();
	loadFont();
}

MainGame::~MainGame()
{
	freeImage();
	freeFont();
	closeWindow();
	closeSystem();
}

bool MainGame::isRunning()
{
	return status != EXIT;
}

void MainGame::update()
{
	if (status == PLAYING && turn == playerAI.getSide())
	{
		playerAI.analysis();
		playerAI.play();
		turnSide();
		gameover();
	}
}

void MainGame::events()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			status = EXIT;
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (status == PLAYING)
			{
				int mouseX = event.motion.x;
				int mouseY = event.motion.y;

				if (mouseX < REGION_BORDER || mouseX > SCREEN_WIDTH - REGION_BORDER) { continue; }
				if (mouseY < REGION_BORDER || mouseY > SCREEN_WIDTH - REGION_BORDER) { continue; }

				int x = (mouseX - BORDER - BLOCK_SIZE / 2) / BLOCK_SIZE;
				int y = (mouseY - BORDER - BLOCK_SIZE / 2) / BLOCK_SIZE;

				if (board.getTableData(x, y) == Chess::EMPTY && turn == player.getSide())
				{
					player.play(x, y);
					turnSide();
					gameover();
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

void MainGame::display()
{
	SDL_BlitSurface(images.pBackground, NULL, pSurface, &screenRect);
	displayChess();
	displayInfo();
	SDL_UpdateWindowSurface(pWindow);
}

void MainGame::delay(Uint32 startTick, Uint32 endTick)
{
	int deltaTick = endTick - startTick;
	int delayTick = 1000 / GAME_FPS - deltaTick;

	SDL_Delay((delayTick > 0) ? delayTick : 0);
}