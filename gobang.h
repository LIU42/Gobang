#ifndef __GOBANG_H__
#define __GOBANG_H__ 

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Windows.h>
#include <random>
#include <string>

#include "config.h"
#include "resource.h"

using namespace std;

struct Point
{
	int x;
	int y;
};

class Window
{
	public:
		HINSTANCE hInstance;
		SDL_Window* window;
		SDL_Event events;
		SDL_PixelFormat* format;
		TTF_Font* font;
		SDL_Rect screenRect;
		SDL_Rect blockRect;

	public:
		SDL_Surface* surface;
		SDL_Surface* backgroundImg;
		SDL_Surface* blackChessImg;
		SDL_Surface* whiteChessImg;
		SDL_Surface* alertImg;

	public:
		SDL_RWops* getResource(HINSTANCE, LPCWSTR, LPCWSTR);
		SDL_Surface* loadSurface(DWORD);

	public:
		void text(const char*, int, int);
		void init();
		void loadImage();
		void loadFont();
		void freeImage();
		void freeFont();
		void close();
};

class Game
{
	public:
		char chessBoard[TABLE_LARGE][TABLE_LARGE];
		char text[TEXT_MAX_LEN];
		int status;
		int turn;
		int turnCount;
		int winner;

	public:
		Point temp;
		Point winPoint[5];
		string lineData[4];

	public:
		default_random_engine random;
		uniform_int_distribution <int> randDev;
		bernoulli_distribution randP;

	public:
		Game();
		void init();
		void getLineData(int, int);
		void gameover();
		void update();
		void events();
		void displayChess();
		void displayInfo();
		void display();
};

class Player
{
	public:
		int side;
		char chessColor;

	public:
		void init(int, char);
		void play(int, int);
};

class AI : public Player
{
	public:
		Point bestPoint;
		int maxScore;

	public:
		void init(int, char);
		void identify();
		void analysis(int, int);
		void play();
};

extern Game game;
extern Window window;
extern Player userPlayer;
extern AI aiPlayer;
#endif