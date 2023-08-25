#include <cstdlib>
#include <iostream>

#include "Game.h"

Game::Game(int screenWidth, int screenHeight) : screenWidth(screenWidth), screenHeight(screenHeight)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		exit(EXIT_FAILURE);

	gameWindow = SDL_CreateWindow("NERRSID",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		screenWidth,
		screenHeight,
		SDL_WINDOW_SHOWN);
	if (!gameWindow)
		exit(EXIT_FAILURE);

	gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);

	this->tileMap = new Tilemap(gameRenderer);
}
Game::~Game()
{
	SDL_DestroyRenderer(gameRenderer);
	tileMap->~Tilemap();
	SDL_Quit();
}
SDL_Renderer* Game::getRenderer()
{
	return gameRenderer;
}
Tilemap* Game::getTileMap()
{
	return tileMap;
}
int Game::getScreenWidth()
{
	return screenWidth;
}
int Game::getScreenHeight()
{
	return screenHeight;
}
void Game::Build(int newScreenWidth, int newScreenHeight)
{
	Game* game = new Game(newScreenWidth, newScreenHeight);
	Map* map = new Map();
	UI* userInterface = new UI(game->getRenderer());
	auto* player = new Player("mts", Warrior);

	bool gameIsRunning = true;

	while (gameIsRunning)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				gameIsRunning = false;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				player->KeyPressHandler(event, *map);
			}
		}

		userInterface->refreshUserInterface();

		userInterface->dumpMap(game->getRenderer(), map, game->getTileMap());
		userInterface->drawPlayer(game->getRenderer(), game->getTileMap()->GetTileMapTexture(), player);
		userInterface->drawPlayerInfo(game->getRenderer(), game->getTileMap()->GetTileMapTexture(), player);
		
		SDL_RenderPresent(game->getRenderer());
	}

}