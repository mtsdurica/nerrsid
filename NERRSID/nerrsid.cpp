#include <cstdlib>
#include <SDL.h>
#include "Game.h"
#include "Util.h"

int main(int argc, char* argv[])
{
	Game::Build(Util::GAME_RESOLUTION_WIDTH, Util::GAME_RESOLUTION_HEIGHT);

	return EXIT_SUCCESS;
}