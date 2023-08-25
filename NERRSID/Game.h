#pragma once
#include <SDL.h>
#include "Player.h"
#include "Map.h"
#include "Tilemap.h"
#include "UI.h"

class Game
{
private:
	int screenWidth;
	int screenHeight;
	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;
	Tilemap* tileMap;
	Game(int, int);

public:
	~Game();
	/**
	 *
	 * @return Width of the game window
	 */
	int getScreenWidth();
	/**
	 *
	 * @return Height of the game window
	 */
	int getScreenHeight();
	/**
	 *
	 * @return Game renderer
	 */
	SDL_Renderer* getRenderer();
	/**
	 *
	 * @return Game tile map
	 */
	Tilemap* getTileMap();
	/**
	 * @brief Method used to build the game application
	 */
	static void Build(int, int);
};
