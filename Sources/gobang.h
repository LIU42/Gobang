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

struct Image
{
	SDL_PixelFormat* format;
	SDL_Surface* surface;
	SDL_Surface* background;
	SDL_Surface* blackChess;
	SDL_Surface* whiteChess;
	SDL_Surface* alert;
};

struct Font
{
	TTF_Font* info;
};

class MainGame
{
	public:
		static constexpr auto TITLE = "Gobang";

	public:
		static const int SCREEN_WIDTH = 620;
		static const int SCREEN_HEIGHT = 650;
		static const int FPS = 10;

	public:
		static const int FONT_SIZE = 20;
		static const int TEXT_LENGTH = 30;
		static const int TURN_INFO_LENGTH = 120;

	public:
		static const int BLOCK_SIZE = 30;
		static const int BORDER = 10;
		static const int REGION_BORDER = 25;

	public:
		static constexpr SDL_Color BLACK = { 0, 0, 0 };

	private:
		SDL_Window* window;
		SDL_SysWMinfo sysInfo;
		SDL_Rect screen;
		SDL_Event event;

	private:
		Image image;
		Font font;

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
		void freeImage();
		void freeFont();
		void turnSide();
		void gameover();

	private:
		void displayText(const char*, int, int);
		void displayChess();
		void displayInfo();

	public:
		void initWindow();
		void initGame();
		void loadImage();
		void loadFont();
		void close();

	public:
		bool isRunning();
		void update();
		void events();
		void display();
};
#endif