#ifndef __GOBANG_H__
#define __GOBANG_H__ 

#include <SDL.h>
#include <SDL_syswm.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <time.h>

#include "board.h"
#include "player.h"
#include "resource.h"

enum Status { PLAYING, OVER, EXIT };

struct Images
{
	SDL_Surface* pBackground;
	SDL_Surface* pBlackChess;
	SDL_Surface* pWhiteChess;
	SDL_Surface* pAlert;
};

struct Fonts
{
	TTF_Font* pInfo;
};

class MainGame
{
	private:
		static constexpr auto TITLE = "Gobang";

	private:
		static const int SCREEN_WIDTH = 620;
		static const int SCREEN_HEIGHT = 650;
		static const int GAME_FPS = 10;

	private:
		static const int FONT_SIZE = 20;
		static const int TEXT_LENGTH = 30;
		static const int TURN_INFO_LENGTH = 120;

	private:
		static const int BLOCK_SIZE = 30;
		static const int BORDER = 10;
		static const int REGION_BORDER = 25;

	private:
		static constexpr SDL_Color BLACK = { 0, 0, 0 };

	private:
		SDL_Window* pWindow;
		SDL_Surface* pSurface;
		SDL_PixelFormat* pFormat;
		SDL_SysWMinfo windowInfo;
		SDL_Rect screenRect;
		SDL_Event event;

	private:
		Images images;
		Fonts fonts;

	private:
		Board board;
		Player player;
		PlayerAI playerAI;

	private:
		Status status;
		Side winner;
		Side turn;
		int turnCount;

	private:
		SDL_RWops* getResource(LPCWSTR, LPCWSTR);
		SDL_Surface* loadSurface(Uint32);

	private:
		void getVersion();
		void initSystem();
		void initWindow();
		void initGame();
		void loadImage();
		void loadFont();

	private:
		void freeImage();
		void freeFont();
		void closeWindow();
		void closeSystem();

	private:
		void turnSide();
		void gameover();

	private:
		void displayText(const char*, int, int);
		void displayChess();
		void displayInfo();

	public:
		MainGame();
		~MainGame();

	public:
		bool isRunning();
		void update();
		void events();
		void display();
		void delay(Uint32, Uint32);
};
#endif