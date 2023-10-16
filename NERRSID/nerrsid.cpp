#include <cstdlib>
#include <SDL.h>
#include "Game.h"
#include "Map.h"

int main(int argc, char* argv[])
{
	Game::Build(GameResolutionWidth, GameResolutionHeight);

	return EXIT_SUCCESS;
}