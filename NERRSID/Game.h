#pragma once
#include <SDL.h>

#include "Player.h"
#include "Map.h"
#include "Tilemap.h"
#include "UserInterface.h"

class Game
{
private:
	int ScreenWidth;
	int ScreenHeight;
	SDL_Window* GameWindow;
	SDL_Renderer* GameRenderer;
	Tilemap* TileMap;
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
	Tilemap* GetTilemap() const;
	/// <summary>
	/// </summary>
	/// <param name="userInterface">Pointer to the UserInterface object</param>
	/// <param name="tilemapTexture"></param>
	/// <returns></returns>
	static std::tuple<bool, Player> IntroSequence(UserInterface* userInterface, SDL_Texture* tilemapTexture);
	/// <summary>
	/// Build the game logic
	/// </summary>
	/// <param name="gameScreenWidth">Width of the game window</param>
	/// <param name="gameScreenHeight">Height of the game window</param>
	static void Build(int gameScreenWidth, int gameScreenHeight);
};
