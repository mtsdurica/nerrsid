#include <string>

#include "UI.h"

UI::UI(SDL_Renderer* renderer, int userInterfaceRectWidth, int userInterfaceRectHeight) : renderer(renderer)
{
	for (int x = 0; x < userInterfaceRectWidth / 16; x++)
	{
		for (int y = 0; y < userInterfaceRectHeight / 16; y++)
		{
			userInterfaceRect[x][y].x = x * 16;
			userInterfaceRect[x][y].y = y * 16;
			userInterfaceRect[x][y].w = 16;
			userInterfaceRect[x][y].h = 16;
		}
	}
}

UI::~UI()
{
	SDL_DestroyRenderer(this->renderer);
}

void UI::RefreshUserInterface()
{
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
	SDL_RenderClear(this->renderer);
	SDL_Delay(30);
}

void UI::DrawPlayer(SDL_Texture* tilemapTexture, Player* player)
{
	SDL_Rect playerTile = Tilemap::FindTile(0, 4);

	SDL_RenderCopy(this->renderer,
		tilemapTexture,
		&playerTile,
		&userInterfaceRect[player->GetPositionXCoordinate()][player->GetPositionYCoordinate()]);
}

void UI::DrawText(SDL_Texture* tilemapTexture, int textPositionX, int textPositionY, std::string text)
{
	/// TODO: Add rest of characters
	SDL_Rect letterTile;
	for (int index = 0; index < text.length(); index++)
	{
		letterTile = Tilemap::CharToRect(text[index]);
		SDL_RenderCopy(this->renderer,
			tilemapTexture,
			&letterTile,
			&userInterfaceRect[textPositionX + index][textPositionY]);
	}
}

void UI::DrawPlayerInfo(SDL_Texture* tilemapTexture, Player* player)
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

void UI::DrawMap(Map* map, Tilemap* tileMap)
{
	SDL_Rect wallTile = Tilemap::FindTile(3, 2);
	SDL_Rect walkableTile = Tilemap::FindTile(0, 0);
	SDL_Rect vendorTile = alpha_V;


	for (int x = 0; x < MAX_X; x++)
	{
		for (int y = 0; y < MAX_Y; y++)
		{
			switch (map->GetMapTiles()[x][y])
			{
			case Wall:
				SDL_RenderCopy(this->renderer, tileMap->GetTileMapTexture(), &wallTile, &this->userInterfaceRect[x][y]);
				break;
			case Walkable:
				SDL_RenderCopy(this->renderer, tileMap->GetTileMapTexture(), &walkableTile, &this->userInterfaceRect[x][y]);
				break;
			case VendorTile:
				SDL_RenderCopy(this->renderer, tileMap->GetTileMapTexture(), &vendorTile, &this->userInterfaceRect[x][y]);
				break;
			default:
				break;
			}
		}
	}
}

void UI::DrawStatusBar(SDL_Texture* tilemapTexture, std::string message)
{
	this->DrawBox(tilemapTexture, 44, 42, 55, 2);
	this->DrawText(tilemapTexture, 45, 43, message);
}

void UI::DrawHorizontalLine(SDL_Texture* tilemapTexture, int row, int startingPoint, int endingPoint)
{
	SDL_Rect rect = line_horizontal;
	for (int i = startingPoint; i < endingPoint; i++)
	{
		SDL_RenderCopy(this->renderer,
			tilemapTexture,
			&rect,
			&userInterfaceRect[i][row]);
	}
}

void UI::DrawVerticalLine(SDL_Texture* tilemapTexture, int column, int startingPoint, int endingPoint)
{
	SDL_Rect rect = line_vertical;
	for (int i = startingPoint; i < endingPoint; i++)
	{
		SDL_RenderCopy(this->renderer,
			tilemapTexture,
			&rect,
			&userInterfaceRect[column][i]);
	}
}

void UI::DrawCorner(SDL_Texture* tilemapTexture, cornerType cornerType, int column, int row)
{
	SDL_Rect rect;
	switch (cornerType)
	{
	case TopLeft:
		rect = corner_top_left;
		break;
	case TopRight:
		rect = corner_top_right;
		break;
	case BottomLeft:
		rect = corner_bottom_left;
		break;
	case BottomRight:
		rect = corner_bottom_right;
		break;
	}
	SDL_RenderCopy(this->renderer, tilemapTexture, &rect, &userInterfaceRect[column][row]);
}

void UI::DrawBox(SDL_Texture* tilemapTexture, int topLeftCornerPositionX, int topLeftCornerPositionY, int width, int height)
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

void UI::DrawPopupBorder(SDL_Texture* tilemapTexture)
{
	this->DrawBox(tilemapTexture, 44, 9, 55, 14);
	this->DrawHorizontalLine(tilemapTexture, 12, 45, 99);
	this->DrawCorner(tilemapTexture, TopLeft, 44, 12);
	this->DrawCorner(tilemapTexture, TopRight, 99, 12);
}

void UI::DrawInventoryPopup(SDL_Texture* tileMapTexture, Player* player, int selectedItem, int startingItem, int endingItem)
{
	this->DrawText(tileMapTexture, 45, 10, "Inventory: " + std::to_string(player->GetItemsInInventory()));
	this->DrawText(tileMapTexture, 46, 11, "Item name:");
	this->DrawText(tileMapTexture, 58, 11, "Item stats:");
	this->DrawText(tileMapTexture, 71, 11, "Item quantity:");
	this->DrawText(tileMapTexture, 87, 11, "Equipped:");
	this->DrawPopupBorder(tileMapTexture);
	if (player->GetItemsInInventory())
		this->DrawInventoryItems(tileMapTexture, player->GetInventory(), player->GetItemsInInventory(), selectedItem, startingItem, endingItem);
	else
		this->DrawText(tileMapTexture, 46, 13, "No items in inventory");
}

void UI::DrawInventoryItems(SDL_Texture* tileMapTexture, std::array<Item, 50>* inventory, int itemsInInventory, int selectedItem, int startingItem, int endingItem)
{
	if (itemsInInventory <= endingItem)
		endingItem = itemsInInventory;

	int positionOfCursor = 0;
	for (int i = startingItem; i < endingItem; i++)
	{
		if (i == selectedItem)
			this->DrawText(tileMapTexture, 45, 13 + positionOfCursor, "1");
		this->DrawText(tileMapTexture, 46, 13 + positionOfCursor, inventory->at(i).GetItemName());
		this->DrawText(tileMapTexture, 58, 13 + positionOfCursor, std::to_string(inventory->at(i).GetItemBonusStrength()) + " " + std::to_string(inventory->at(i).GetItemBonusDexterity()) + " " + std::to_string(inventory->at(i).GetItemBonusIntellect()));
		this->DrawText(tileMapTexture, 87, 13 + positionOfCursor, std::to_string(inventory->at(i).GetIsEquipped()));
		positionOfCursor++;
	}
}

void UI::DrawVendorPopup(SDL_Texture* tileMapTexture, Vendor* vendor, int selectedItem, int startingItem, int endingItem)
{
	this->DrawText(tileMapTexture, 45, 10, "Vendor " + vendor->GetName() + ": " + std::to_string(vendor->GetItemsInInventory()));
	this->DrawText(tileMapTexture, 46, 11, "Item name:");
	this->DrawText(tileMapTexture, 58, 11, "Item stats:");
	this->DrawText(tileMapTexture, 71, 11, "Item quantity:");
	this->DrawText(tileMapTexture, 87, 11, "Item price:");
	this->DrawPopupBorder(tileMapTexture);
	if (vendor->GetItemsInInventory())
		this->DrawInventoryItems(tileMapTexture, vendor->GetInventory(), vendor->GetItemsInInventory(), selectedItem, startingItem, endingItem);
	else
		this->DrawText(tileMapTexture, 46, 13, "No items for sale");
}

SDL_Renderer* UI::GetRenderer()
{
	return this->renderer;
}

void UI::DrawStartupMenu(SDL_Texture* tilemapTexture, int selectedItem)
{
	for (int i = 0; i < 2; i++)
	{
		if (i == selectedItem)
			this->DrawText(tilemapTexture, 0, 0 + i, "1");
		this->DrawText(tilemapTexture, 1, 0, "Create new character");
		this->DrawText(tilemapTexture, 1, 1, "Exit game");
	}
}

void UI::DrawPlayerClassSelection(SDL_Texture* tilemapTexture, int selectedItem)
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

void UI::DrawPlayerCreationName(SDL_Texture* tilemapTexture, std::string playerName)
{
	this->DrawText(tilemapTexture, 0, 1, playerName);
}