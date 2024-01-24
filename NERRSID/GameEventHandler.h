#pragma once
#include <SDL.h>
#include "GameEvent.h"
#include "Map.h"
#include "Player.h"
#include "Util.h"

typedef enum HandledEvent
{
	UnusedKeypressHandled,
	ExitKeypressHandled,
	EnterKeypressHandled,
	PlayerNavigationKeypressHandled,
	InventoryKeypressHandled,
	NextTurnKeypressHandled,
	ScrollDownKeypressHandled,
	ScrollUpKeypressHandled,
	HelpKeypressHandled
} HandledEvent;

class GameEventHandler
{
public:
	/// <summary>
	/// Main game window keypress handler
	/// </summary>
	/// <param name="player">Pointer to the player object</param>
	/// <param name="eventToBeHandledGame">Game event containing collision information</param>
	/// <param name="eventToBeHandledSDL">SDL event containing the keypress</param>
	/// <param name="mapTiles">Map tiles</param>
	/// <returns>Handled keypress</returns>
	static HandledEvent KeypressHandler(Player* player, const GameEvent& eventToBeHandledGame, const SDL_Event* eventToBeHandledSDL, const std::array<std::array<Util::Tiles, Util::MAX_Y>, Util::MAX_X>& mapTiles);
	/// <summary>
	/// Vendor popup keypress handler
	/// </summary>
	/// <param name="eventToBeHandledSDL">SDL event containing the keypress</param>
	/// <returns>Handled keypress</returns>
	static HandledEvent EntityInventoryKeypressHandler(const SDL_Event* eventToBeHandledSDL);
	/// <summary>
	/// Player collision handler
	/// </summary>
	/// <param name="player">Player object</param>
	/// <param name="map">Map object</param>
	/// <returns>Collision event</returns>
	static GameEvent CollisionHandler(const Player& player, Map map);
};


