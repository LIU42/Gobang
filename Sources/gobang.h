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
	int attackFive;
	int doubleFour;
	int attackFour;
	int defendFour;
	int formatFour;
	int attackThree;
	int defendThree;
	int formatThree;
	int attackTwo;
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
		void play(int, int);
};

class AI : public Player
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
		void analysisData(int, int);
		void play();
};

class MainGame
{
	public:
		HINSTANCE hInstance;
		SDL_Window* window;
		SDL_Event events;
		TTF_Font* font;

	public:
		Image image;
		Rect rect;
		Point temp;
		Point winPoint[WIN_CHESS_COUNT];
		string lineData[LINE_COUNT];

	public:
		Player player;
		AI ai;

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
		void getLineData(int, int);
		void gameover();
		void update();
		void control();
		void displayText(const char*, int, int);
		void displayChess();
		void displayInfo();
		void display();
};

extern MainGame game;
#endif