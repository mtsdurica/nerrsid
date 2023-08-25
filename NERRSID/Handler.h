#pragma once
#include <SDL.h>

#include "Player.h"
#include "Event.h"
#include "Map.h"

typedef enum HandledEvent
{
	ExitKeypressHandled, EnterKeypressHandled, PlayerNavigationKeypressHandled
} HandledEvent;

class Handler
{
public:
	static HandledEvent KeyPressHandler(Player* player, SDL_Event eventToBeHandledSDL, Event eventToBeHandledGame, Map map);
	static HandledEvent VendorKeyPressHandler(SDL_Event eventToBeHandledSDL, Event eventToBeHandledGame);
	static Event CollisionHandler(Player player, Map map);
};


