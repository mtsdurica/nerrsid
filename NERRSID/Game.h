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
	Game(int screenWidth, int screenHeight);

public:
	~Game();
	/**
	 *
	 * @return Width of the game window
	 */
	int GetScreenWidth() const;
	/**
	 *
	 * @return Height of the game window
	 */
	int GetScreenHeight() const;
	/**
	 *
	 * @return Game renderer
	 */
	SDL_Renderer* GetRenderer() const;
	/**
	 *
	 * @return Game tile map
	 */
	Tilemap* GetTileMap() const;
	/**
	 * @brief Method used to build the game application
	 */
	static void Build(int gameScreenWidth, int gameScreenHeight);
};
