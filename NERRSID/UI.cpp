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
void UI::DrawPlayer(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, Player* player)
{
	SDL_Rect playerTile = Tilemap::FindTile(0, 4);

	SDL_RenderCopy(renderer,
		tilemapTexture,
		&playerTile,
		&userInterfaceRect[player->GetPositionXCoordinate()][player->GetPositionYCoordinate()]);
}
void UI::DrawText(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, int textPositionX, int textPositionY, std::string text)
{
	/// TODO: Add rest of characters
	SDL_Rect letterTile;
	for (int index = 0; index < text.length(); index++)
	{
		letterTile = Tilemap::CharToRect(text[index]);
		SDL_RenderCopy(renderer,
			tilemapTexture,
			&letterTile,
			&userInterfaceRect[textPositionX + index][textPositionY]);
	}
}
void UI::DrawPlayerInfo(SDL_Renderer* renderer, SDL_Texture* tileMapTexture, Player* player)
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
	DrawText(renderer, tileMapTexture, 45, 0, "Name:       " + player->GetName());
	DrawText(renderer, tileMapTexture, 45, 1, "Class:      " + classString);
	DrawText(renderer, tileMapTexture, 45, 2, "Level:      " + std::to_string(player->GetPlayerLevel()));
	DrawText(renderer, tileMapTexture, 45, 3, "Experience: " + std::to_string(player->GetPlayerExperience()));
	DrawText(renderer, tileMapTexture, 45, 4, "Gold:       " + std::to_string(player->GetGold()));
	DrawText(renderer, tileMapTexture, 45, 5, "Strength:   " + std::to_string(player->GetPlayerStrength()));
	DrawText(renderer, tileMapTexture, 45, 6, "Dexterity:  " + std::to_string(player->GetPlayerDexterity()));
	DrawText(renderer, tileMapTexture, 45, 7, "Intellect:  " + std::to_string(player->GetPlayerIntellect()));
}
void UI::DrawMap(SDL_Renderer* renderer, Map* map, Tilemap* tileMap)
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
				SDL_RenderCopy(renderer, tileMap->GetTileMapTexture(), &wallTile, &this->userInterfaceRect[x][y]);
				break;
			case Walkable:
				SDL_RenderCopy(renderer, tileMap->GetTileMapTexture(), &walkableTile, &this->userInterfaceRect[x][y]);
				break;
			case VendorTile:
				SDL_RenderCopy(renderer, tileMap->GetTileMapTexture(), &vendorTile, &this->userInterfaceRect[x][y]);
				break;
			default:
				break;
			}
		}
	}
}
void UI::DrawStatusBar(SDL_Renderer* renderer, SDL_Texture* tileMapTexture, std::string message)
{
	/// TODO: Add borders
	DrawText(renderer, tileMapTexture, 46, 43, message);
}

void UI::DrawInventoryPopup(SDL_Renderer* renderer, SDL_Texture* tileMapTexture, Player* player, int selectedItem, int startingItem, int endingItem)
{
	DrawText(renderer, tileMapTexture, 45, 10, "Inventory: " + std::to_string(player->GetItemsInInventory()));
	DrawText(renderer, tileMapTexture, 45, 11, "Item name:");
	DrawText(renderer, tileMapTexture, 57, 11, "Item stats:");
	DrawText(renderer, tileMapTexture, 70, 11, "Item quantity:");
	DrawText(renderer, tileMapTexture, 86, 11, "Equipped:");
	DrawInventoryItems(renderer, tileMapTexture, player->GetInventory(), player->GetItemsInInventory(), selectedItem, startingItem, endingItem);
}

void UI::DrawInventoryItems(SDL_Renderer* renderer, SDL_Texture* tileMapTexture, std::array<Item, 50>* inventory, int itemsInInventory, int selectedItem, int startingItem, int endingItem)
{
	if (itemsInInventory < endingItem)
		endingItem = itemsInInventory;

	int positionOfCursor = 0;
	for (int i = startingItem; i < endingItem; i++)
	{
		if (i == selectedItem)
			DrawText(renderer, tileMapTexture, 44, 12 + positionOfCursor, "1");
		DrawText(renderer, tileMapTexture, 45, 12 + positionOfCursor, inventory->at(i).GetItemName());
		DrawText(renderer, tileMapTexture, 57, 12 + positionOfCursor, std::to_string(inventory->at(i).GetItemBonusStrength()) + " " + std::to_string(inventory->at(i).GetItemBonusDexterity()) + " " + std::to_string(inventory->at(i).GetItemBonusIntellect()));
		DrawText(renderer, tileMapTexture, 86, 12 + positionOfCursor, std::to_string(inventory->at(i).GetIsEquipped()));
		positionOfCursor++;
	}
}

void UI::DrawVendorPopup(SDL_Renderer* renderer, SDL_Texture* tileMapTexture, Vendor* vendor, int selectedItem, int startingItem, int endingItem)
{
	DrawText(renderer, tileMapTexture, 45, 10, "Vendor " + vendor->GetName() + ": " + std::to_string(vendor->GetItemsInInventory()));
	DrawText(renderer, tileMapTexture, 45, 11, "Item name:");
	DrawText(renderer, tileMapTexture, 57, 11, "Item stats:");
	DrawText(renderer, tileMapTexture, 70, 11, "Item quantity:");
	DrawText(renderer, tileMapTexture, 86, 11, "Item price:");
	DrawInventoryItems(renderer, tileMapTexture, vendor->GetInventory(), vendor->GetItemsInInventory(), selectedItem, startingItem, endingItem);
}

void UI::DrawUI()
{
}