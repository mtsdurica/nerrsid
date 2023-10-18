#pragma once
#include <SDL.h>
#include "GameEvent.h"
#include "Map.h"
#include "Player.h"

typedef enum HandledEvent
{
	UnusedKeypressHandled,
	ExitKeypressHandled,
	EnterKeypressHandled,
	PlayerNavigationKeypressHandled,
	InventoryKeypressHandled,
	ScrollDownKeypressHandled,
	ScrollUpKeypressHandled
} HandledEvent;

class GameEventHandler
{
public:
	/// <summary>
	/// Main game window keypress handler
	/// </summary>
	/// <param name="player">Pointer to the player object</param>
	/// <param name="eventToBeHandledSDL">SDL event containing the keypress</param>
	/// <param name="mapTiles">Map tiles</param>
	/// <returns></returns>
	static HandledEvent KeypressHandler(Player* player, const SDL_Event* eventToBeHandledSDL, const std::array<std::array<Tiles, MaxY>, MaxX>& mapTiles);
	/// <summary>
	/// Vendor popup keypress handler
	/// </summary>
	/// <param name="eventToBeHandledSDL">SDL event containing the keypress</param>
	/// <returns></returns>
	static HandledEvent EntityInventoryKeypressHandler(const SDL_Event* eventToBeHandledSDL);
	/// <summary>
	/// Player collision handler
	/// </summary>
	/// <param name="player">Player object</param>
	/// <param name="map">Map object</param>
	/// <returns></returns>
	static GameEvent CollisionHandler(const Player& player, Map map);
};


