
#include "GameEventHandler.h"

HandledEvent GameEventHandler::KeypressHandler(Player* player, const SDL_Event* eventToBeHandledSDL, const std::array<std::array<Tiles, MaxY>, MaxX>& mapTiles)
{
	/// TODO: Needs rework

	switch (eventToBeHandledSDL->key.keysym.sym)
	{
	case SDLK_UP:
		if (mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() - 1] == WalkableTile || mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() - 1] == VendorTile)
			player->SetPositionYCoordinate(player->GetPositionYCoordinate() - 1);
		return PlayerNavigationKeypressHandled;
	case SDLK_DOWN:
		if (mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() + 1] == WalkableTile || mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() + 1] == VendorTile)
			player->SetPositionYCoordinate(player->GetPositionYCoordinate() + 1);
		return PlayerNavigationKeypressHandled;
	case SDLK_LEFT:
		if (mapTiles[player->GetPositionXCoordinate() - 1][player->GetPositionYCoordinate()] == WalkableTile || mapTiles[player->GetPositionXCoordinate() - 1][player->GetPositionYCoordinate()] == VendorTile)
			player->SetPositionXCoordinate(player->GetPositionXCoordinate() - 1);
		return PlayerNavigationKeypressHandled;
	case SDLK_RIGHT:
		if (mapTiles[player->GetPositionXCoordinate() + 1][player->GetPositionYCoordinate()] == WalkableTile || mapTiles[player->GetPositionXCoordinate() + 1][player->GetPositionYCoordinate()] == VendorTile)
			player->SetPositionXCoordinate(player->GetPositionXCoordinate() + 1);
		return PlayerNavigationKeypressHandled;
	case SDLK_ESCAPE:
		return ExitKeypressHandled;
	case SDLK_RETURN:
		return EnterKeypressHandled;
	case SDLK_i:
		return InventoryKeypressHandled;
	default:
		break;
	}
	return UnusedKeypressHandled;
}

HandledEvent GameEventHandler::VendorKeypressHandler(const SDL_Event* eventToBeHandledSDL)
{
	switch (eventToBeHandledSDL->key.keysym.sym)
	{
	case SDLK_UP:
		return ScrollUpKeypressHandled;
	case SDLK_DOWN:
		return ScrollDownKeypressHandled;
	case SDLK_ESCAPE:
		return ExitKeypressHandled;
	case SDLK_RETURN:
		return EnterKeypressHandled;
	default:
		break;
	}
	return UnusedKeypressHandled;
}

HandledEvent GameEventHandler::InventoryKeypressHandler(const SDL_Event& eventToBeHandledSDL)
{
	switch (eventToBeHandledSDL.key.keysym.sym)
	{
	case SDLK_UP:
		return ScrollUpKeypressHandled;
	case SDLK_DOWN:
		return ScrollDownKeypressHandled;
	case SDLK_ESCAPE:
	case SDLK_i:
		return ExitKeypressHandled;
	case SDLK_RETURN:
		return EnterKeypressHandled;
	default:
		break;
	}
	return UnusedKeypressHandled;
}

GameEvent GameEventHandler::CollisionHandler(const Player& player, Map map)
{
	GameEvent collisionEvent(EmptyEvent, "");

	const auto mapTiles = map.GetMapTiles();

	switch (mapTiles[player.GetPositionXCoordinate()][player.GetPositionYCoordinate()])
	{

	case VendorTile:
		collisionEvent.SetTypeOfEvent(VendorEvent);
		collisionEvent.SetEventMessage("Press ENTER to interact with vendor");
		break;
	case WallTile:
	case PlayerTile:
	case WalkableTile:
		break;
	}

	return collisionEvent;
}