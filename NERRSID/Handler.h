#pragma once
#include <SDL.h>

#include "Player.h"
#include "Event.h"
#include "Map.h"

typedef enum HandledEvent
{
	ExitKeypressHandled, EnterKeypressHandled, PlayerNavigationKeypressHandled, InventoryKeypressHandled
} HandledEvent;

class Handler
{
public:
	static HandledEvent KeyPressHandler(Player* player, SDL_Event eventToBeHandledSDL, Event eventToBeHandledGame, Map map);
	static HandledEvent VendorKeyPressHandler(SDL_Event eventToBeHandledSDL, Event eventToBeHandledGame);
	static HandledEvent InventoryKeyPressHandler(SDL_Event eventToBeHandledSDL);
	static Event CollisionHandler(Player player, Map map);
};


