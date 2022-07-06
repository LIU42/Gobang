#include "gobang.h"

using namespace std;

MainGame game;

int main(int argc, char* argv[])
{
	Uint32 startTick = 0;
	Uint32 endTick = 0;
	INT32 delayTick = 0;

	srand((unsigned)time(NULL));

	game.initWindow();
	game.initGame();
	game.loadImage();
	game.loadFont();

	while (game.status != EXIT)
	{
		startTick = SDL_GetTicks();

		game.update();
		game.control();
		game.display();

		endTick = SDL_GetTicks();
		delayTick = (1000 / GAME_FPS) - (endTick - startTick);

		SDL_Delay((delayTick > 0) ? delayTick : 0);
	}
	game.close();
	return 0;
}