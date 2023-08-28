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
	/// <summary>
	/// Get width of the game window
	/// </summary>
	/// <returns>Game window width</returns>
	int GetScreenWidth() const;
	/// <summary>
	/// Get height of the game window
	/// </summary>
	/// <returns>Game window height</returns>
	int GetScreenHeight() const;
	/// <summary>
	/// Get renderer of the game
	/// </summary>
	/// <returns>Game renderer</returns>
	SDL_Renderer* GetRenderer() const;
	/// <summary>
	/// Get tilemap of the game
	/// </summary>
	/// <returns>Game tilemap</returns>
	Tilemap* GetTileMap() const;
	/// <summary>
	/// Build the game logic
	/// </summary>
	/// <param name="gameScreenWidth">Width of the game window</param>
	/// <param name="gameScreenHeight">Height of the game window</param>
	static void Build(int gameScreenWidth, int gameScreenHeight);
};
