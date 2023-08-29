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
	/// 
	/// </summary>
	/// <param name="player"></param>
	/// <param name="eventToBeHandledSDL"></param>
	/// <param name="mapTiles"></param>
	/// <returns></returns>
	static HandledEvent KeyPressHandler(Player* player, SDL_Event* eventToBeHandledSDL, std::array<std::array<tiles, MAX_Y>, MAX_X> mapTiles);
	/// <summary>
	/// Vendor popup keypress handler
	/// </summary>
	/// <param name="eventToBeHandledSDL">SDL event containing the keypress</param>
	/// <param name="eventToBeHandledGame"></param>
	/// <returns></returns>
	static HandledEvent VendorKeyPressHandler(SDL_Event* eventToBeHandledSDL);
	/// <summary>
	/// Inventory popup keypress handler
	/// </summary>
	/// <param name="eventToBeHandledSDL"></param>
	/// <returns></returns>
	static HandledEvent InventoryKeyPressHandler(SDL_Event eventToBeHandledSDL);
	/// <summary>
	/// Player collision handler
	/// </summary>
	/// <param name="player"></param>
	/// <param name="map"></param>
	/// <returns></returns>
	static GameEvent CollisionHandler(Player player, Map map);
};


