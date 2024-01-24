
#include "GameEventHandler.h"

HandledEvent GameEventHandler::KeypressHandler(Player* player, const GameEvent& eventToBeHandledGame, const SDL_Event* eventToBeHandledSDL, const std::array<std::array<Util::Tiles, Util::MAX_Y>, Util::MAX_X>& mapTiles)
{
	/// TODO: Needs rework
	if (eventToBeHandledGame.GetTypeOfEvent() == EnemyEvent)
	{
		if (eventToBeHandledSDL->key.keysym.sym == SDLK_RETURN)
			return EnterKeypressHandled;
		return UnusedKeypressHandled;
	}

	switch (eventToBeHandledSDL->key.keysym.sym)
	{
	case SDLK_UP:
		if (player->GetPlayerMovesLeft() > 0)
		{
			if (mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() - 1] == Util::WalkableTile
				|| mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() - 1] == Util::VendorTile
				|| mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() - 1] == Util::ChestTile
				|| mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() - 1] == Util::StairsTile
				|| mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() - 1] == Util::EnemyTile
				|| mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() - 1] == Util::CorpseTile
				)
			{
				player->SetIdleStatus(false);
				player->SetPositionYCoordinate(player->GetPositionYCoordinate() - 1);
				player->SetPlayerMovesLeft(player->GetPlayerMovesLeft() - 1);
			}
		}
		if (player->GetPlayerMovesLeft() == 0)
			return NextTurnKeypressHandled;
		return PlayerNavigationKeypressHandled;
	case SDLK_DOWN:
		if (player->GetPlayerMovesLeft() > 0)
		{
			if (mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() + 1] == Util::WalkableTile
				|| mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() + 1] == Util::VendorTile
				|| mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() + 1] == Util::ChestTile
				|| mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() + 1] == Util::StairsTile
				|| mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() + 1] == Util::EnemyTile
				|| mapTiles[player->GetPositionXCoordinate()][player->GetPositionYCoordinate() + 1] == Util::CorpseTile
				)
			{
				player->SetIdleStatus(false);
				player->SetPositionYCoordinate(player->GetPositionYCoordinate() + 1);
				player->SetPlayerMovesLeft(player->GetPlayerMovesLeft() - 1);
			}
		}
		if (player->GetPlayerMovesLeft() == 0)
			return NextTurnKeypressHandled;
		return PlayerNavigationKeypressHandled;
	case SDLK_LEFT:
		if (player->GetPlayerMovesLeft() > 0)
		{
			if (mapTiles[player->GetPositionXCoordinate() - 1][player->GetPositionYCoordinate()] == Util::WalkableTile
				|| mapTiles[player->GetPositionXCoordinate() - 1][player->GetPositionYCoordinate()] == Util::VendorTile
				|| mapTiles[player->GetPositionXCoordinate() - 1][player->GetPositionYCoordinate()] == Util::ChestTile
				|| mapTiles[player->GetPositionXCoordinate() - 1][player->GetPositionYCoordinate()] == Util::StairsTile
				|| mapTiles[player->GetPositionXCoordinate() - 1][player->GetPositionYCoordinate()] == Util::EnemyTile
				|| mapTiles[player->GetPositionXCoordinate() - 1][player->GetPositionYCoordinate()] == Util::CorpseTile
				)
			{
				player->SetIdleStatus(false);
				player->SetPositionXCoordinate(player->GetPositionXCoordinate() - 1);
				player->SetPlayerMovesLeft(player->GetPlayerMovesLeft() - 1);
			}
		}
		if (player->GetPlayerMovesLeft() == 0)
			return NextTurnKeypressHandled;
		return PlayerNavigationKeypressHandled;
	case SDLK_RIGHT:
		if (player->GetPlayerMovesLeft() > 0)
		{
			if (mapTiles[player->GetPositionXCoordinate() + 1][player->GetPositionYCoordinate()] == Util::WalkableTile
				|| mapTiles[player->GetPositionXCoordinate() + 1][player->GetPositionYCoordinate()] == Util::VendorTile
				|| mapTiles[player->GetPositionXCoordinate() + 1][player->GetPositionYCoordinate()] == Util::ChestTile
				|| mapTiles[player->GetPositionXCoordinate() + 1][player->GetPositionYCoordinate()] == Util::StairsTile
				|| mapTiles[player->GetPositionXCoordinate() + 1][player->GetPositionYCoordinate()] == Util::EnemyTile
				|| mapTiles[player->GetPositionXCoordinate() + 1][player->GetPositionYCoordinate()] == Util::CorpseTile
				)
			{
				player->SetIdleStatus(false);
				player->SetPositionXCoordinate(player->GetPositionXCoordinate() + 1);
				player->SetPlayerMovesLeft(player->GetPlayerMovesLeft() - 1);
			}
		}
		if (player->GetPlayerMovesLeft() == 0)
			return NextTurnKeypressHandled;
		return PlayerNavigationKeypressHandled;
	case SDLK_ESCAPE:
		return ExitKeypressHandled;
	case SDLK_RETURN:
		return EnterKeypressHandled;
	case SDLK_i:
		return InventoryKeypressHandled;
	case SDLK_n:
		return NextTurnKeypressHandled;
	case SDLK_h:
		return HelpKeypressHandled;
	case SDLK_q:
		return DebugKeypressHandled;
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
	case SDLK_h:
		return HelpKeypressHandled;
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
	case Util::VendorTile:
		collisionEvent.SetTypeOfEvent(VendorEvent);
		collisionEvent.SetEventMessage("Press ENTER to interact with vendor");
		break;
	case Util::ChestTile:
		collisionEvent.SetTypeOfEvent(ChestEvent);
		collisionEvent.SetEventMessage("Press ENTER to loot chest");
		break;
	case Util::StairsTile:
		collisionEvent.SetTypeOfEvent(StairsEvent);
		collisionEvent.SetEventMessage("Press ENTER to traverse to lower level");
		break;
	case Util::EnemyTile:
		collisionEvent.SetTypeOfEvent(EnemyEvent);
		collisionEvent.SetEventMessage("Press ENTER to slay enemy");
		break;
	case Util::CorpseTile:
		collisionEvent.SetTypeOfEvent(CorpseEvent);
		collisionEvent.SetEventMessage("Press ENTER to loot corpse");
		break;
	case Util::WallTile:
	case Util::PlayerTile:
	case Util::WalkableTile:
		break;
	}

	return collisionEvent;
}