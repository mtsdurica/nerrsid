#include <string>

#include "UserInterface.h"

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
	const SDL_Rect playerTile = Tilemap::FindTile(0, 4);

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
}

void UserInterface::DrawMap(SDL_Texture* tilemapTexture, Map* map) const
{
	const SDL_Rect wallTile = Tilemap::FindTile(3, 2);
	const SDL_Rect walkableTile = Tilemap::FindTile(0, 0);
	const SDL_Rect vendorTile = ALPHA_V;
	const SDL_Rect chestTile = ALPHA_C;
	const SDL_Rect stairsTile = STAIRS;


	for (int x = 0; x < MaxX; x++)
	{
		for (int y = 0; y < MaxY; y++)
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
	{
		SDL_RenderCopy(this->Renderer,
			tilemapTexture,
			&rect,
			&this->UserInterfaceRect[i][row]);
	}
}

void UserInterface::DrawVerticalLine(SDL_Texture* tilemapTexture, const int column, const int startingPoint, const int endingPoint) const
{
	const SDL_Rect rect = LINE_VERTICAL;
	for (int i = startingPoint; i < endingPoint; i++)
	{
		SDL_RenderCopy(this->Renderer,
			tilemapTexture,
			&rect,
			&this->UserInterfaceRect[column][i]);
	}
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

void UserInterface::DrawInventoryItems(SDL_Texture* tilemapTexture, std::array<Item, 50>* inventory, const int itemsInInventory, const int selectedItem, const int startingItem, int endingItem) const
{
	if (itemsInInventory <= endingItem)
		endingItem = itemsInInventory;

	int positionOfCursor = 0;
	for (int i = startingItem; i < endingItem; i++)
	{
		if (i == selectedItem)
		{
			const SDL_Rect selectorTile = SELECTOR_LEFT;
			SDL_RenderCopy(this->Renderer, tilemapTexture, &selectorTile, &this->UserInterfaceRect[45][13 + positionOfCursor]);
		}
		this->DrawText(tilemapTexture, 46, 13 + positionOfCursor, inventory->at(i).GetItemName());
		this->DrawText(tilemapTexture, 58, 13 + positionOfCursor, std::to_string(inventory->at(i).GetItemBonusStrength()) + " " + std::to_string(inventory->at(i).GetItemBonusDexterity()) + " " + std::to_string(inventory->at(i).GetItemBonusIntellect()));
		if (inventory->at(i).GetIsEquipped())
		{
			/// this->DrawText(tilemapTexture, 87, 13 + positionOfCursor, std::to_string(i));
			const SDL_Rect selectorTile = SELECTOR_CENTER;
			SDL_RenderCopy(this->Renderer, tilemapTexture, &selectorTile, &this->UserInterfaceRect[87][13 + positionOfCursor]);
		}
		else
		{
			this->DrawText(tilemapTexture, 87, 13 + positionOfCursor, " ");
		}
		positionOfCursor++;
	}
}

void UserInterface::DrawEntityPopup(SDL_Texture* tilemapTexture, Player* entity, const int selectedItem, const int startingItem, const int endingItem) const
{
	this->DrawText(tilemapTexture, 45, 10, "Inventory: " + std::to_string(entity->GetItemsInInventory()));
	this->DrawText(tilemapTexture, 46, 11, "Item name:");
	this->DrawText(tilemapTexture, 58, 11, "Item stats:");
	this->DrawText(tilemapTexture, 71, 11, "Item quantity:");
	this->DrawText(tilemapTexture, 87, 11, "Equipped:");
	this->DrawPopupBorder(tilemapTexture);
	if (entity->GetItemsInInventory())
		this->DrawInventoryItems(tilemapTexture, entity->GetInventory(), entity->GetItemsInInventory(), selectedItem, startingItem, endingItem);
	else
		this->DrawText(tilemapTexture, 46, 13, "No items in inventory");
}

void UserInterface::DrawEntityPopup(SDL_Texture* tilemapTexture, Chest* entity, const int selectedItem, const int startingItem, const int endingItem) const
{
	this->DrawText(tilemapTexture, 45, 10, "Chest: " + std::to_string(entity->GetItemsInInventory()));
	this->DrawText(tilemapTexture, 46, 11, "Item name:");
	this->DrawText(tilemapTexture, 58, 11, "Item stats:");
	this->DrawText(tilemapTexture, 71, 11, "Item quantity:");
	this->DrawText(tilemapTexture, 87, 11, "Item price:");
	this->DrawPopupBorder(tilemapTexture);
	if (entity->GetItemsInInventory())
		this->DrawInventoryItems(tilemapTexture, entity->GetInventory(), entity->GetItemsInInventory(), selectedItem, startingItem, endingItem);
	else
		this->DrawText(tilemapTexture, 46, 13, "Chest is empty");
}

void UserInterface::DrawEntityPopup(SDL_Texture* tilemapTexture, Vendor* entity, const int selectedItem, const int startingItem, const int endingItem) const
{
	this->DrawText(tilemapTexture, 45, 10, "Vendor " + entity->GetName() + ": " + std::to_string(entity->GetItemsInInventory()));
	this->DrawText(tilemapTexture, 46, 11, "Item name:");
	this->DrawText(tilemapTexture, 58, 11, "Item stats:");
	this->DrawText(tilemapTexture, 71, 11, "Item quantity:");
	this->DrawText(tilemapTexture, 87, 11, "Item price:");
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

void UserInterface::DrawStartupMenu(SDL_Texture* tilemapTexture, const int selectedItem) const
{
	for (int i = 0; i < 2; i++)
	{
		if (i == selectedItem)
			this->DrawText(tilemapTexture, 0, 0 + i, "1");
		this->DrawText(tilemapTexture, 1, 0, "Create new character");
		this->DrawText(tilemapTexture, 1, 1, "Exit game");
	}
}

void UserInterface::DrawPlayerClassSelection(SDL_Texture* tilemapTexture, const int selectedItem) const
{
	for (int i = 0; i < 3; i++)
	{
		if (i == selectedItem)
			this->DrawText(tilemapTexture, 0, 0 + i, "1");
		this->DrawText(tilemapTexture, 1, 0, "Warrior");
		this->DrawText(tilemapTexture, 1, 1, "Wizard");
		this->DrawText(tilemapTexture, 1, 2, "Assassin");
	}
}

void UserInterface::DrawPlayerCreationName(SDL_Texture* tilemapTexture, const std::string& playerName) const
{
	this->DrawText(tilemapTexture, 0, 1, playerName);
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
	Chest* chest, const Menu* menu, const std::string& message) const
{
	this->RefreshUserInterface();
	this->DrawMap(tilemapTexture, map);
	this->DrawPlayer(tilemapTexture, player);
	this->DrawPlayerInfo(tilemapTexture, player);
	this->DrawEntityPopup(tilemapTexture, chest, menu->GetSelectedItem(), menu->GetStartingItem(), menu->GetEndingItem());
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