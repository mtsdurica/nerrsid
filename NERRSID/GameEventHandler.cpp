
#include "GameEventHandler.h"

HandledEvent GameEventHandler::KeyPressHandler(Player* player, SDL_Event eventToBeHandledSDL, Event eventToBeHandledGame, Map map)
{
	auto mapTiles = map.GetMapTiles();

	switch (eventToBeHandledSDL.key.keysym.sym)
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

HandledEvent GameEventHandler::VendorKeyPressHandler(SDL_Event eventToBeHandledSDL, Event eventToBeHandledGame)
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

HandledEvent GameEventHandler::InventoryKeyPressHandler(SDL_Event eventToBeHandledSDL)
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
		return ExitKeypressHandled;
		break;
	case SDLK_RETURN:
		return EnterKeypressHandled;
		break;
	}
}

std::tuple<int, int, int> GameEventHandler::MenuNavigation(HandledEvent keypress, int playerItemsInInventory, int selectedItem, int displayedItems, int startingItem, int endingItem)
{
	switch (keypress)
	{
	case ScrollDownKeypressHandled:
		if (selectedItem < playerItemsInInventory - 1)
			selectedItem++;
		if (selectedItem == endingItem)
		{
			startingItem += displayedItems;
			if ((playerItemsInInventory - startingItem) < displayedItems)
				endingItem = playerItemsInInventory;
			else
				endingItem += displayedItems;
		}
		return { selectedItem, startingItem, endingItem };
		break;
	case ScrollUpKeypressHandled:
		if (selectedItem > 0)
			selectedItem--;
		if ((selectedItem == startingItem - 1) && (selectedItem != 0))
		{
			endingItem -= endingItem - startingItem;
			startingItem -= displayedItems;
		}
		return { selectedItem, startingItem, endingItem };
		break;
	}
}

Event GameEventHandler::CollisionHandler(Player player, Map map)
{
	Event* collisionEvent = nullptr;

	auto mapTiles = map.GetMapTiles();

	switch (mapTiles[player.GetPositionXCoordinate()][player.GetPositionYCoordinate()])
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