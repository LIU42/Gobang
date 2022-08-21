#include "gobang.h"

MainGame game;

int main(int argc, char* argv[])
{
	int startTick = 0;
	int endTick = 0;
	int delayTick = 0;

	srand((unsigned)time(NULL));

	game.initWindow();
	game.initGame();
	game.loadImage();
	game.loadFont();

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
	game.close();
	return 0;
}