#ifndef __GOBANG_H__
#define __GOBANG_H__ 

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Windows.h>
#include <time.h>
#include <string>

#include "config.h"
#include "resource.h"

using namespace std;

struct Point
{
	int x;
	int y;
};

struct Format
{
	int rushFive;
	int aliveFour;
	int rushFour;
	int endFour;
	int preFour;
	int aliveThree;
	int endThree;
	int preThree;
	int aliveTwo;
	int linkTwo;
};

struct Image
{
	SDL_PixelFormat* format;
	SDL_Surface* surface;
	SDL_Surface* background;
	SDL_Surface* blackChess;
	SDL_Surface* whiteChess;
	SDL_Surface* alert;
};

struct Rect
{
	SDL_Rect screen;
	SDL_Rect block;
};

class Player
{
	public:
		int side;
		char chessColor;

	public:
		void init(int, char);
		void play(Point);
};

class PlayerAI : public Player
{
	public:
		Format format;
		Point bestPoint;
		int score;
		int maxScore;

	public:
		void init(int, char);
		void identify();
		void clearFormatData();
		void getFormatData();
		void analysisData(Point);
		void autoPlay();
};

class MainGame
{
	public:
		HINSTANCE hInstance;
		SDL_Window* window;
		SDL_Event event;
		TTF_Font* font;

	public:
		Image image;
		Rect rect;
		Point temp;
		Point winPoint[WIN_CHESS_COUNT];
		string lineData[LINE_COUNT];

	public:
		Player player;
		PlayerAI ai;

	public:
		char chessBoard[TABLE_LARGE][TABLE_LARGE];
		int status;
		int turn;
		int turnCount;
		int winner;

	public:
		SDL_RWops* getResource(HINSTANCE, LPCWSTR, LPCWSTR);
		SDL_Surface* loadSurface(int);

	public:
		void initGame();
		void initWindow();
		void loadImage();
		void loadFont();
		void freeImage();
		void freeFont();
		void close();

	public:
		void getLineData(Point);
		void gameover();
		void update();
		void events();
		void displayText(const char*, Point);
		void displayChess();
		void displayInfo();
		void display();
};

extern MainGame game;
#endif