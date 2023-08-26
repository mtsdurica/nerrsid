#include <cstdlib>
#include <SDL.h>
#include "Game.h"
#include "Map.h"

int main(int argc, char* args[])
{
	Game::Build(GAME_RESOLUTION_WIDTH, GAME_RESOLUTION_HEIGHT);

	return EXIT_SUCCESS;
}