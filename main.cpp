#include "gobang.h"

using namespace std;

Game game;
Window window;
Player player;
Computer computer;

int main(int argc, char* argv[])
{
	Uint32 startTick = 0;
	Uint32 endTick = 0;
	Uint32 delta = 0;

	game.init();
	window.init();
	window.loadImage();
	window.loadFont();

	while (game.status != EXIT)
	{
		startTick = SDL_GetTicks();

		game.update();
		game.events();
		game.display();

		endTick = SDL_GetTicks();
		delta = (1000 / GAME_FPS) - (endTick - startTick);
		if (delta >= 0 && delta <= (1000 / GAME_FPS)) { SDL_Delay(delta); }
	}
	window.close();
	return 0;
}