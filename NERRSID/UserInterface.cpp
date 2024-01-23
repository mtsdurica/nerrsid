#include <string>

#include "UserInterface.h"
#include <iostream>

UserInterface::UserInterface(SDL_Renderer* renderer, const int userInterfaceRectWidth, const int userInterfaceRectHeight) : Renderer(renderer)
{
	for (int x = 0; x < userInterfaceRectWidth / 16; x++)
	{
		for (int y = 0; y < userInterfaceRectHeight / 16; y++)
		{
			this->UserInterfaceRect[x][y].x = x * 16;
			this->UserInterfaceRect[x][y].y = y * 16;
			this->UserInterfaceRect[x][y].w = 16;
			this->UserInterfaceRect[x][y].h = 16;
		}
	}
}

UserInterface::~UserInterface()
{
	SDL_DestroyRenderer(this->Renderer);
}

void UserInterface::RefreshUserInterface() const
{
	SDL_SetRenderDrawColor(this->Renderer, 0, 0, 0, 0);
	SDL_RenderClear(this->Renderer);
	SDL_Delay(30);
}

void UserInterface::DrawPlayer(SDL_Texture* tilemapTexture, const Player* player) const
{
	const SDL_Rect playerTile = AT;
	const SDL_Rect blankTile = SPACE;

	if (player->GetIdleStatus())
		if (SDL_GetTicks64() % 1000 < 500)
			SDL_RenderCopy(this->Renderer,
				tilemapTexture,
				&blankTile,
				&this->UserInterfaceRect[player->GetPositionXCoordinate()][player->GetPositionYCoordinate()]);
		else
			SDL_RenderCopy(this->Renderer,
				tilemapTexture,
				&playerTile,
				&this->UserInterfaceRect[player->GetPositionXCoordinate()][player->GetPositionYCoordinate()]);
	else
		SDL_RenderCopy(this->Renderer,
			tilemapTexture,
			&playerTile,
			&this->UserInterfaceRect[player->GetPositionXCoordinate()][player->GetPositionYCoordinate()]);
}

void UserInterface::DrawText(SDL_Texture* tilemapTexture, const int textPositionX, const int textPositionY, const std::string& text) const
{
	/// TODO: Add rest of characters
	SDL_Rect letterTile;
	for (unsigned long long index = 0; index < text.length(); index++)
	{
		letterTile = Tilemap::CharToRect(text[index]);
		SDL_RenderCopy(this->Renderer,
			tilemapTexture,
			&letterTile,
			&this->UserInterfaceRect[textPositionX + index][textPositionY]);
	}
}

void UserInterface::DrawPlayerInfo(SDL_Texture* tilemapTexture, const Player* player) const
{

	std::string classString;
	switch (player->GetPlayerClass())
	{
	case Warrior:
		classString = "Warrior";
		break;
	case Assassin:
		classString = "Assassin";
		break;
	case Wizard:
		classString = "Wizard";
		break;
	case UndefinedPlayerClass:
		classString = "undef";
		break;
	}
	this->DrawBox(tilemapTexture, 44, 0, 55, 9);
	this->DrawVerticalLine(tilemapTexture, 71, 1, 9);
	this->DrawCorner(tilemapTexture, TopLeft, 71, 0);
	this->DrawCorner(tilemapTexture, BottomRight, 71, 9);
	this->DrawText(tilemapTexture, 45, 1, "Name:       " + player->GetName());
	this->DrawText(tilemapTexture, 45, 2, "Class:      " + classString);
	this->DrawText(tilemapTexture, 45, 3, "Level:      " + std::to_string(player->GetPlayerLevel()));
	this->DrawText(tilemapTexture, 45, 4, "Experience: " + std::to_string(player->GetPlayerExperience()));
	this->DrawText(tilemapTexture, 45, 5, "Gold:       " + std::to_string(player->GetGold()));
	this->DrawText(tilemapTexture, 45, 6, "Strength:   " + std::to_string(player->GetPlayerStrength()));
	this->DrawText(tilemapTexture, 45, 7, "Dexterity:  " + std::to_string(player->GetPlayerDexterity()));
	this->DrawText(tilemapTexture, 45, 8, "Intellect:  " + std::to_string(player->GetPlayerIntellect()));
	this->DrawText(tilemapTexture, 72, 1, "Turn:       " + std::to_string(player->GetPlayerTurn()));
	this->DrawText(tilemapTexture, 72, 2, "Moves left: " + std::to_string(player->GetPlayerMovesLeft()));
}

void UserInterface::DrawMap(SDL_Texture* tilemapTexture, Map* map) const
{
	const SDL_Rect wallTile = HASH;
	const SDL_Rect walkableTile = SPACE;
	const SDL_Rect vendorTile = ALPHA_V;
	const SDL_Rect chestTile = ALPHA_C;
	const SDL_Rect stairsTile = STAIRS;
	const SDL_Rect enemyTile = ALPHA_E;
	const SDL_Rect corpseTile = ALPHA_c;

	for (int x = 0; x < Util::MAX_X; x++)
	{
		for (int y = 0; y < Util::MAX_Y; y++)
		{
			switch (map->GetMapTiles()[x][y])
			{
			case WallTile:
				SDL_RenderCopy(this->Renderer, tilemapTexture, &wallTile, &this->UserInterfaceRect[x][y]);
				break;
			case WalkableTile:
				SDL_RenderCopy(this->Renderer, tilemapTexture, &walkableTile, &this->UserInterfaceRect[x][y]);
				break;
			case VendorTile:
				SDL_RenderCopy(this->Renderer, tilemapTexture, &vendorTile, &this->UserInterfaceRect[x][y]);
				break;
			case ChestTile:
				SDL_RenderCopy(this->Renderer, tilemapTexture, &chestTile, &this->UserInterfaceRect[x][y]);
				break;
			case StairsTile:
				SDL_RenderCopy(this->Renderer, tilemapTexture, &stairsTile, &this->UserInterfaceRect[x][y]);
				break;
			case EnemyTile:
				SDL_RenderCopy(this->Renderer, tilemapTexture, &enemyTile, &this->UserInterfaceRect[x][y]);
				break;
			case CorpseTile:
				SDL_RenderCopy(this->Renderer, tilemapTexture, &corpseTile, &this->UserInterfaceRect[x][y]);
				break;
			case PlayerTile:
				break;
			}
		}
	}
}

void UserInterface::DrawStatusBar(SDL_Texture* tilemapTexture, const std::string& message) const
{
	this->DrawBox(tilemapTexture, 44, 42, 55, 2);
	this->DrawText(tilemapTexture, 45, 43, message);
}

void UserInterface::DrawHorizontalLine(SDL_Texture* tilemapTexture, const int row, const int startingPoint, const int endingPoint) const
{
	const SDL_Rect rect = LINE_HORIZONTAL;
	for (int i = startingPoint; i < endingPoint; i++)
		SDL_RenderCopy(this->Renderer,
			tilemapTexture,
			&rect,
			&this->UserInterfaceRect[i][row]);
}

void UserInterface::DrawVerticalLine(SDL_Texture* tilemapTexture, const int column, const int startingPoint, const int endingPoint) const
{
	const SDL_Rect rect = LINE_VERTICAL;
	for (int i = startingPoint; i < endingPoint; i++)
		SDL_RenderCopy(this->Renderer,
			tilemapTexture,
			&rect,
			&this->UserInterfaceRect[column][i]);
}

void UserInterface::DrawCorner(SDL_Texture* tilemapTexture, const CornerType cornerType, const int column, const int row) const
{
	SDL_Rect rect;
	switch (cornerType)
	{
	case TopLeft:
		rect = CORNER_TOP_LEFT;
		break;
	case TopRight:
		rect = CORNER_TOP_RIGHT;
		break;
	case BottomLeft:
		rect = CORNER_BOTTOM_LEFT;
		break;
	case BottomRight:
		rect = CORNER_BOTTOM_RIGHT;
		break;
	}
	SDL_RenderCopy(this->Renderer, tilemapTexture, &rect, &this->UserInterfaceRect[column][row]);
}

void UserInterface::DrawBox(SDL_Texture* tilemapTexture, const int topLeftCornerPositionX, const int topLeftCornerPositionY, const int width, const int height) const
{
	this->DrawHorizontalLine(tilemapTexture, topLeftCornerPositionY, topLeftCornerPositionX + 1, topLeftCornerPositionX + width);
	this->DrawHorizontalLine(tilemapTexture, topLeftCornerPositionY + height, topLeftCornerPositionX + 1, topLeftCornerPositionX + width);
	this->DrawVerticalLine(tilemapTexture, topLeftCornerPositionX, topLeftCornerPositionY + 1, topLeftCornerPositionY + height);
	this->DrawVerticalLine(tilemapTexture, topLeftCornerPositionX + width, topLeftCornerPositionY + 1, topLeftCornerPositionY + height);
	this->DrawCorner(tilemapTexture, TopLeft, topLeftCornerPositionX, topLeftCornerPositionY);
	this->DrawCorner(tilemapTexture, TopRight, topLeftCornerPositionX + width, topLeftCornerPositionY);
	this->DrawCorner(tilemapTexture, BottomLeft, topLeftCornerPositionX, topLeftCornerPositionY + height);
	this->DrawCorner(tilemapTexture, BottomRight, topLeftCornerPositionX + width, topLeftCornerPositionY + height);
}

void UserInterface::DrawPopupBorder(SDL_Texture* tilemapTexture) const
{
	this->DrawBox(tilemapTexture, 44, 9, 55, 14);
	this->DrawHorizontalLine(tilemapTexture, 12, 45, 99);
	this->DrawCorner(tilemapTexture, TopLeft, 44, 12);
	this->DrawCorner(tilemapTexture, TopRight, 99, 12);
}

std::string UserInterface::DrawAnimatedText(SDL_Texture* tilemapTexture, const int textPositionX, const int textPositionY, const std::string& text, const int lastUpdate) const
{
	/// TODO: Maybe fix, as for now it is not working and i have no clue how to make it work
	std::string textTmp = text;
	if (SDL_GetTicks64() % 500 < 500)
		textTmp.erase(0, 1);
	this->DrawText(tilemapTexture, textPositionX, textPositionY, textTmp);
	return textTmp;
}

void UserInterface::DrawInventoryItems(SDL_Texture* tilemapTexture, std::array<Item, 50>* inventory, const int itemsInInventory, const int selectedItem, const int startingItem, int endingItem) const
{
	if (itemsInInventory <= endingItem)
		endingItem = itemsInInventory;
	int positionOfCursor = 0;
	for (int i = startingItem; i < endingItem; i++)
	{
		/// Drawing cursor
		if (i == selectedItem)
		{
			const SDL_Rect selectorTile = SELECTOR_LEFT;
			SDL_RenderCopy(this->Renderer, tilemapTexture, &selectorTile, &this->UserInterfaceRect[45][13 + positionOfCursor]);
		}
		/// Checking if item name is not longer than 20 characters, if yes, only 20 characters will be displayed
		std::string tempItemName = inventory->at(i).GetItemName();
		if (inventory->at(i).GetItemName().length() > 20)
			tempItemName = tempItemName.substr(20, tempItemName.length() - 20);
		this->DrawText(tilemapTexture, 46, 13 + positionOfCursor, tempItemName);
		this->DrawText(tilemapTexture, 68, 13 + positionOfCursor, std::to_string(inventory->at(i).GetItemBonusStrength()) + " " + std::to_string(inventory->at(i).GetItemBonusDexterity()) + " " + std::to_string(inventory->at(i).GetItemBonusIntellect()));
		if (inventory->at(i).GetIsEquipped())
		{
			/// this->DrawText(tilemapTexture, 87, 13 + positionOfCursor, std::to_string(i));
			const SDL_Rect selectorTile = SELECTOR_CENTER;
			SDL_RenderCopy(this->Renderer, tilemapTexture, &selectorTile, &this->UserInterfaceRect[90][13 + positionOfCursor]);
		}
		else this->DrawText(tilemapTexture, 87, 13 + positionOfCursor, " ");
		positionOfCursor++;
	}
}

void UserInterface::DrawEntityPopup(SDL_Texture* tilemapTexture, Player* entity, const int selectedItem, const int startingItem, const int endingItem) const
{
	this->DrawText(tilemapTexture, 45, 10, "Inventory: " + std::to_string(entity->GetItemsInInventory()));
	this->DrawText(tilemapTexture, 46, 11, "Name:");
	this->DrawText(tilemapTexture, 68, 11, "Stats:");
	this->DrawText(tilemapTexture, 81, 11, "Qty:");
	this->DrawText(tilemapTexture, 90, 11, "Equipped:");
	this->DrawPopupBorder(tilemapTexture);
	if (entity->GetItemsInInventory())
		this->DrawInventoryItems(tilemapTexture, entity->GetInventory(), entity->GetItemsInInventory(), selectedItem, startingItem, endingItem);
	else
		this->DrawText(tilemapTexture, 46, 13, "No items in inventory");
}

void UserInterface::DrawEntityPopup(SDL_Texture* tilemapTexture, Chest* entity, const int selectedItem, const int startingItem, const int endingItem, const bool isCorpse) const
{
	std::string entityTitle;
	if (isCorpse)
		entityTitle = "Corpse: ";
	else
		entityTitle = "Chest: ";
	this->DrawText(tilemapTexture, 45, 10, entityTitle + std::to_string(entity->GetItemsInInventory()));
	this->DrawText(tilemapTexture, 46, 11, "Name:");
	this->DrawText(tilemapTexture, 68, 11, "Stats:");
	this->DrawText(tilemapTexture, 81, 11, "Qty:");
	this->DrawText(tilemapTexture, 90, 11, "Price:");
	this->DrawPopupBorder(tilemapTexture);
	if (entity->GetItemsInInventory())
		this->DrawInventoryItems(tilemapTexture, entity->GetInventory(), entity->GetItemsInInventory(), selectedItem, startingItem, endingItem);
	else
		this->DrawText(tilemapTexture, 46, 13, "Chest is empty");
}

void UserInterface::DrawEntityPopup(SDL_Texture* tilemapTexture, Vendor* entity, const int selectedItem, const int startingItem, const int endingItem) const
{
	this->DrawText(tilemapTexture, 45, 10, "Vendor " + entity->GetName() + ": " + std::to_string(entity->GetItemsInInventory()));
	this->DrawText(tilemapTexture, 46, 11, "Name:");
	this->DrawText(tilemapTexture, 68, 11, "Stats:");
	this->DrawText(tilemapTexture, 81, 11, "Qty:");
	this->DrawText(tilemapTexture, 90, 11, "Price:");
	this->DrawPopupBorder(tilemapTexture);
	if (entity->GetItemsInInventory())
		this->DrawInventoryItems(tilemapTexture, entity->GetInventory(), entity->GetItemsInInventory(), selectedItem, startingItem, endingItem);
	else
		this->DrawText(tilemapTexture, 46, 13, "No items for sale");
}

SDL_Renderer* UserInterface::GetRenderer() const
{
	return this->Renderer;
}

void UserInterface::DrawGameLogo(SDL_Texture* tilemapTexture) const
{
	this->DrawText(tilemapTexture, 20, 5, "###  ##  ######   ######   ######    ####      ##   ####");
	this->DrawText(tilemapTexture, 20, 6, " ###  #       ##       ##       ##  ##   #    ##     ## ##");
	this->DrawText(tilemapTexture, 20, 7, " #### #   ##       ##   #   ##   #  ##        ##     ##  ##");
	this->DrawText(tilemapTexture, 20, 8, " ## # #  #######  #######  #######   #####    ##     ##  ##");
	this->DrawText(tilemapTexture, 20, 9, " ## ###   ##       ####     ####         ##   ##     ##  ##");
	this->DrawText(tilemapTexture, 20, 10, " ##  ##   ##  ##   ## ##    ## ##   #    ##   ##     ## ##");
	this->DrawText(tilemapTexture, 20, 11, "###   #  ######   ###  ##  ###  ##   #####   ##    ####");
}

void UserInterface::DrawStartupMenu(SDL_Texture* tilemapTexture, const int selectedItem) const
{
	this->DrawGameLogo(tilemapTexture);
	this->DrawBox(tilemapTexture, 39, 21, 22, 3);
	const SDL_Rect selectorTile = SELECTOR_LEFT;
	for (int i = 0; i < 2; i++)
		if (i == selectedItem)
			SDL_RenderCopy(this->Renderer, tilemapTexture, &selectorTile, &this->UserInterfaceRect[40][22 + i]);
	this->DrawText(tilemapTexture, 41, 22, "Create New Character");
	this->DrawText(tilemapTexture, 41, 23, "Exit Game");
	this->DrawText(tilemapTexture, 0, 44, "Alpha Release 0.1");
}

void UserInterface::DrawPlayerClassSelection(SDL_Texture* tilemapTexture, const int selectedItem) const
{
	this->DrawBox(tilemapTexture, 39, 21, 22, 5);
	const SDL_Rect selectorTile = SELECTOR_LEFT;
	this->DrawText(tilemapTexture, 40, 22, "Select Class:");
	for (int i = 0; i < 3; i++)
		if (i == selectedItem)
			SDL_RenderCopy(this->Renderer, tilemapTexture, &selectorTile, &this->UserInterfaceRect[40][23 + i]);
	this->DrawText(tilemapTexture, 41, 23, "Warrior");
	this->DrawText(tilemapTexture, 41, 24, "Wizard");
	this->DrawText(tilemapTexture, 41, 25, "Assassin");
}

void UserInterface::DrawPlayerCreationName(SDL_Texture* tilemapTexture, const std::string& playerName) const
{
	this->DrawBox(tilemapTexture, 39, 21, 22, 3);
	this->DrawText(tilemapTexture, 40, 22, "Enter Name:");
	this->DrawText(tilemapTexture, 40, 23, playerName);
}

void UserInterface::UpdateUserInterface(SDL_Texture* tilemapTexture, Map* map, const Player* player,
	Vendor* vendor, const Menu* menu, const std::string& message) const
{
	this->RefreshUserInterface();
	this->DrawMap(tilemapTexture, map);
	this->DrawPlayer(tilemapTexture, player);
	this->DrawPlayerInfo(tilemapTexture, player);
	this->DrawEntityPopup(tilemapTexture, vendor, menu->GetSelectedItem(), menu->GetStartingItem(), menu->GetEndingItem());
	this->DrawStatusBar(tilemapTexture, message);
	SDL_RenderPresent(this->Renderer);
}
void UserInterface::UpdateUserInterface(SDL_Texture* tilemapTexture, Map* map, const Player* player,
	Chest* chest, const Menu* menu, const std::string& message, const bool isCorpse) const
{
	this->RefreshUserInterface();
	this->DrawMap(tilemapTexture, map);
	this->DrawPlayer(tilemapTexture, player);
	this->DrawPlayerInfo(tilemapTexture, player);
	this->DrawEntityPopup(tilemapTexture, chest, menu->GetSelectedItem(), menu->GetStartingItem(), menu->GetEndingItem(), isCorpse);
	this->DrawStatusBar(tilemapTexture, message);
	SDL_RenderPresent(this->Renderer);
}
void UserInterface::UpdateUserInterface(SDL_Texture* tilemapTexture, Map* map, Player* player,
	const Menu* menu, const std::string& message) const
{
	this->RefreshUserInterface();
	this->DrawMap(tilemapTexture, map);
	this->DrawPlayer(tilemapTexture, player);
	this->DrawPlayerInfo(tilemapTexture, player);
	this->DrawEntityPopup(tilemapTexture, player, menu->GetSelectedItem(), menu->GetStartingItem(), menu->GetEndingItem());
	this->DrawStatusBar(tilemapTexture, message);
	SDL_RenderPresent(this->Renderer);
}

void UserInterface::UpdateUserInterface(SDL_Texture* tilemapTexture, Map* map, const Player* player, const std::string& message) const
{
	this->RefreshUserInterface();
	this->DrawMap(tilemapTexture, map);
	this->DrawPlayer(tilemapTexture, player);
	this->DrawPlayerInfo(tilemapTexture, player);
	this->DrawStatusBar(tilemapTexture, message);
	SDL_RenderPresent(this->Renderer);
}