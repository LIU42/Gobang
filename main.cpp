#include "gobang.h"

using namespace std;

Game game;
Window window;
Player userPlayer;
AI aiPlayer;

int main(int argc, char* argv[])
{
	Uint32 startTick = 0;
	Uint32 endTick = 0;
	INT32 delayTick = 0;

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
		delayTick = (1000 / GAME_FPS) - (endTick - startTick);

		SDL_Delay((delayTick > 0) ? delayTick : 0);
	}
	window.close();
	return 0;
}