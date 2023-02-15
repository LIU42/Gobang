#include "gobang.h"

int main(int argc, char* argv[])
{
	MainGame game;

	Uint32 startTick = 0;
	Uint32 endTick = 0;
	Uint32 delayTick = 0;

	srand((unsigned)time(NULL));

	game.initEnvironment();
	game.initWindow();
	game.initGame();
	game.loadImage();
	game.loadFont();

	while (game.isRunning())
	{
		startTick = SDL_GetTicks();

		game.update();
		game.events();
		game.display();

		endTick = SDL_GetTicks();
		delayTick = game.getDelayTick(startTick, endTick);

		SDL_Delay(delayTick);
	}
	game.close();
	return 0;
}