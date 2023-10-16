#pragma once
#include <SDL.h>
#include <tuple>
#include <iostream>

#include "Player.h"
#include "GameEvent.h"
#include "Map.h"

typedef enum HandledEvent
{
	ExitKeypressHandled, EnterKeypressHandled, PlayerNavigationKeypressHandled, InventoryKeypressHandled, ScrollDownKeypressHandled, ScrollUpKeypressHandled
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
	static HandledEvent KeypressHandler(Player* player, SDL_Event* eventToBeHandledSDL, std::array<std::array<tiles, MAX_Y>, MAX_X> mapTiles);
	/// <summary>
	/// Vendor popup keypress handler
	/// </summary>
	/// <param name="eventToBeHandledSDL">SDL event containing the keypress</param>
	/// <returns></returns>
	static HandledEvent VendorKeypressHandler(SDL_Event* eventToBeHandledSDL);
	/// <summary>
	/// Inventory popup keypress handler
	/// </summary>
	/// <param name="eventToBeHandledSDL">SDL event containing the keypress</param>
	/// <returns></returns>
	static HandledEvent InventoryKeypressHandler(SDL_Event eventToBeHandledSDL);
	/// <summary>
	/// Player collision handler
	/// </summary>
	/// <param name="player">Player object</param>
	/// <param name="map">Map object</param>
	/// <returns></returns>
	static GameEvent CollisionHandler(Player player, Map map);
};


