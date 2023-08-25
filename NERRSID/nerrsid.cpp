#include <cstdlib>
#include <SDL.h>
#include "Game.h"

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 720;

int main(int argc, char* args[])
{
	Game::Build(SCREEN_WIDTH, SCREEN_HEIGHT);

	return EXIT_SUCCESS;
}