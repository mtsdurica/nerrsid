
#include "GameEventHandler.h"

HandledEvent GameEventHandler::KeypressHandler(Player* player, SDL_Event* eventToBeHandledSDL, std::array<std::array<tiles, MAX_Y>, MAX_X> mapTiles)
{
	/// TODO: Needs rework

	switch (eventToBeHandledSDL->key.keysym.sym)
	{
	case SDLK_UP:
		if (mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() - 1] == Walkable || mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() - 1] == VendorTile)
			player->SetPositionYCoordinate(player->GetPositionYCoordinate() - 1);
		return PlayerNavigationKeypressHandled;
		break;
	case SDLK_DOWN:
		if (mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() + 1] == Walkable || mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() + 1] == VendorTile)
			player->SetPositionYCoordinate(player->GetPositionYCoordinate() + 1);
		return PlayerNavigationKeypressHandled;
		break;
	case SDLK_LEFT:
		if (mapTiles[player->GetPositionXCoordinate() - 1][player->GetPositionYCoordinate()] == Walkable || mapTiles[player->GetPositionXCoordinate() - 1][player->GetPositionYCoordinate()] == VendorTile)
			player->SetPositionXCoordinate(player->GetPositionXCoordinate() - 1);
		return PlayerNavigationKeypressHandled;
		break;
	case SDLK_RIGHT:
		if (mapTiles[player->GetPositionXCoordinate() + 1][player->GetPositionYCoordinate()] == Walkable || mapTiles[player->GetPositionXCoordinate() + 1][player->GetPositionYCoordinate()] == VendorTile)
			player->SetPositionXCoordinate(player->GetPositionXCoordinate() + 1);
		return PlayerNavigationKeypressHandled;
		break;
	case SDLK_ESCAPE:
		return ExitKeypressHandled;
		break;
	case SDLK_RETURN:
		return EnterKeypressHandled;
		break;
	case SDLK_i:
		return InventoryKeypressHandled;
		break;
	}
}

HandledEvent GameEventHandler::VendorKeypressHandler(SDL_Event* eventToBeHandledSDL)
{
	switch (eventToBeHandledSDL->key.keysym.sym)
	{
	case SDLK_UP:
		return ScrollUpKeypressHandled;
		break;
	case SDLK_DOWN:
		return ScrollDownKeypressHandled;
		break;
	case SDLK_ESCAPE:
		return ExitKeypressHandled;
		break;
	case SDLK_RETURN:
		return EnterKeypressHandled;
		break;
	}
}

HandledEvent GameEventHandler::InventoryKeypressHandler(SDL_Event eventToBeHandledSDL)
{
	switch (eventToBeHandledSDL.key.keysym.sym)
	{
	case SDLK_UP:
		return ScrollUpKeypressHandled;
		break;
	case SDLK_DOWN:
		return ScrollDownKeypressHandled;
		break;
	case SDLK_ESCAPE:
	case SDLK_i:
		return ExitKeypressHandled;
		break;
	case SDLK_RETURN:
		return EnterKeypressHandled;
		break;
	}
}

GameEvent GameEventHandler::CollisionHandler(Player player, Map map)
{
	GameEvent collisionEvent(EmptyEvent, "");

	auto mapTiles = map.GetMapTiles();

	switch (mapTiles[player.GetPositionXCoordinate()][player.GetPositionYCoordinate()])
	{
	case VendorTile:
		collisionEvent.SetTypeOfEvent(VendorEvent);
		collisionEvent.SetEventMessage("Press ENTER to interact with vendor");
		break;
	default:;
		break;
	}

	return collisionEvent;
}