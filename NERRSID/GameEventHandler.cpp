
#include "GameEventHandler.h"

HandledEvent GameEventHandler::KeypressHandler(Player* player, const SDL_Event* eventToBeHandledSDL, const std::array<std::array<Tiles, MaxY>, MaxX>& mapTiles)
{
	/// TODO: Needs rework

	switch (eventToBeHandledSDL->key.keysym.sym)
	{
	case SDLK_UP:
		if (player->GetPlayerMovesLeft() > 0)
		{
			if (mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() - 1] == WalkableTile
				|| mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() - 1] == VendorTile
				|| mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() - 1] == ChestTile
				|| mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() - 1] == StairsTile
				)
			{
				player->SetIdleStatus(false);
				player->SetPositionYCoordinate(player->GetPositionYCoordinate() - 1);
				player->SetPlayerMovesLeft(player->GetPlayerMovesLeft() - 1);
			}
		}
		return PlayerNavigationKeypressHandled;
	case SDLK_DOWN:
		if (player->GetPlayerMovesLeft() > 0)
		{
			if (mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() + 1] == WalkableTile
				|| mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() + 1] == VendorTile
				|| mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() + 1] == ChestTile
				|| mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() + 1] == StairsTile
				)
			{
				player->SetIdleStatus(false);
				player->SetPositionYCoordinate(player->GetPositionYCoordinate() + 1);
				player->SetPlayerMovesLeft(player->GetPlayerMovesLeft() - 1);
			}
		}
		return PlayerNavigationKeypressHandled;
	case SDLK_LEFT:
		if (player->GetPlayerMovesLeft() > 0)
		{
			if (mapTiles[player->GetPositionXCoordinate() - 1][player->GetPositionYCoordinate()] == WalkableTile
				|| mapTiles[player->GetPositionXCoordinate() - 1][player->GetPositionYCoordinate()] == VendorTile
				|| mapTiles[player->GetPositionXCoordinate() - 1][player->GetPositionYCoordinate()] == ChestTile
				|| mapTiles[player->GetPositionXCoordinate() - 1][player->GetPositionYCoordinate()] == StairsTile
				)
			{
				player->SetIdleStatus(false);
				player->SetPositionXCoordinate(player->GetPositionXCoordinate() - 1);
				player->SetPlayerMovesLeft(player->GetPlayerMovesLeft() - 1);
			}
		}
		return PlayerNavigationKeypressHandled;
	case SDLK_RIGHT:
		if (player->GetPlayerMovesLeft() > 0)
		{
			if (mapTiles[player->GetPositionXCoordinate() + 1][player->GetPositionYCoordinate()] == WalkableTile
				|| mapTiles[player->GetPositionXCoordinate() + 1][player->GetPositionYCoordinate()] == VendorTile
				|| mapTiles[player->GetPositionXCoordinate() + 1][player->GetPositionYCoordinate()] == ChestTile
				|| mapTiles[player->GetPositionXCoordinate() + 1][player->GetPositionYCoordinate()] == StairsTile
				)
			{
				player->SetIdleStatus(false);
				player->SetPositionXCoordinate(player->GetPositionXCoordinate() + 1);
				player->SetPlayerMovesLeft(player->GetPlayerMovesLeft() - 1);
			}
		}
		return PlayerNavigationKeypressHandled;
	case SDLK_ESCAPE:
		return ExitKeypressHandled;
	case SDLK_RETURN:
		return EnterKeypressHandled;
	case SDLK_i:
		return InventoryKeypressHandled;
	case SDLK_n:
		return NextTurnKeypressHandled;
	default:
		break;
	}
	return UnusedKeypressHandled;
}
HandledEvent GameEventHandler::EntityInventoryKeypressHandler(const SDL_Event* eventToBeHandledSDL)
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
	case ChestTile:
		collisionEvent.SetTypeOfEvent(ChestEvent);
		collisionEvent.SetEventMessage("Press ENTER to loot chest");
		break;
	case StairsTile:
		collisionEvent.SetTypeOfEvent(StairsEvent);
		collisionEvent.SetEventMessage("Press ENTER to traverse to lower level");
		break;
	case WallTile:
	case PlayerTile:
	case WalkableTile:
		break;
	}

	return collisionEvent;
}