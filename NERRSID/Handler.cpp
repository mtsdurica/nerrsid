
#include "Handler.h"

HandledEvent Handler::KeyPressHandler(Player* player, SDL_Event eventToBeHandledSDL, Event eventToBeHandledGame, Map map)
{
	auto mapTiles = map.GetMapTiles();

	switch (eventToBeHandledSDL.key.keysym.sym)
	{
	case SDLK_UP:
		if (mapTiles[player->GetPlayerPosX()][player->GetPlayerPosY() - 1] == Walkable || mapTiles[player->GetPlayerPosX()][player->GetPlayerPosY() - 1] == VendorTile)
			player->SetPlayerPosY(player->GetPlayerPosY() - 1);
		return PlayerNavigationKeypressHandled;
		break;
	case SDLK_DOWN:
		if (mapTiles[player->GetPlayerPosX()][player->GetPlayerPosY() + 1] == Walkable || mapTiles[player->GetPlayerPosX()][player->GetPlayerPosY() + 1] == VendorTile)
			player->SetPlayerPosY(player->GetPlayerPosY() + 1);
		return PlayerNavigationKeypressHandled;
		break;
	case SDLK_LEFT:
		if (mapTiles[player->GetPlayerPosX() - 1][player->GetPlayerPosY()] == Walkable || mapTiles[player->GetPlayerPosX() - 1][player->GetPlayerPosY()] == VendorTile)
			player->SetPlayerPosX(player->GetPlayerPosX() - 1);
		return PlayerNavigationKeypressHandled;
		break;
	case SDLK_RIGHT:
		if (mapTiles[player->GetPlayerPosX() + 1][player->GetPlayerPosY()] == Walkable || mapTiles[player->GetPlayerPosX() + 1][player->GetPlayerPosY()] == VendorTile)
			player->SetPlayerPosX(player->GetPlayerPosX() + 1);
		return PlayerNavigationKeypressHandled;
		break;
	case SDLK_ESCAPE:
		return ExitKeypressHandled;
		break;
	case SDLK_RETURN:
		switch (eventToBeHandledGame.GetTypeOfEvent())
		{
		case VendorEvent:
			return EnterKeypressHandled;
			break;
		}
	}
}

HandledEvent Handler::VendorKeyPressHandler(SDL_Event eventToBeHandledSDL, Event eventToBeHandledGame)
{
	switch (eventToBeHandledSDL.key.keysym.sym)
	{
	case SDLK_UP:

		return PlayerNavigationKeypressHandled;
		break;
	case SDLK_DOWN:

		return PlayerNavigationKeypressHandled;
		break;
	case SDLK_LEFT:

		return PlayerNavigationKeypressHandled;
		break;
	case SDLK_RIGHT:

		return PlayerNavigationKeypressHandled;
		break;
	case SDLK_ESCAPE:
		return ExitKeypressHandled;
		break;
	case SDLK_RETURN:
		switch (eventToBeHandledGame.GetTypeOfEvent())
		{
		case VendorEvent:
			return EnterKeypressHandled;
			break;
		}
	}
}

Event Handler::CollisionHandler(Player player, Map map)
{
	Event* collisionEvent = nullptr;

	auto mapTiles = map.GetMapTiles();

	switch (mapTiles[player.GetPlayerPosX()][player.GetPlayerPosY()])
	{
	case VendorTile:
		collisionEvent = new Event(VendorEvent, "Press ENTER to interact with vendor");
		break;
	default:
		collisionEvent = new Event(EmptyEvent, "");
		break;
	}

	return *collisionEvent;
}