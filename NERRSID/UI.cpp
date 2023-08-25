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

}
void UI::RefreshUserInterface()
{
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
	SDL_RenderClear(this->renderer);
	SDL_Delay(30);
}
void UI::DrawPlayer(SDL_Renderer* renderer, SDL_Texture* tileMapTexture, Player* player)
{
	SDL_Rect playerTile = Tilemap::FindTile(0, 4);

	SDL_RenderCopy(renderer,
		tileMapTexture,
		&playerTile,
		&userInterfaceRect[player->GetPlayerPosX()][player->GetPlayerPosY()]);
}
void UI::DrawText(SDL_Renderer* renderer, SDL_Texture* tileMapTexture, int textPositionX, int textPositionY, std::string text)
{
	/// TODO: Add rest of characters
	SDL_Rect letterTile;
	for (int index = 0; index < text.length(); index++)
	{
		letterTile = Tilemap::CharToRect(text[index]);
		SDL_RenderCopy(renderer,
			tileMapTexture,
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
	DrawText(renderer, tileMapTexture, 45, 0, "Name:       " + player->GetPlayerName());
	DrawText(renderer, tileMapTexture, 45, 1, "Class:      " + classString);
	DrawText(renderer, tileMapTexture, 45, 2, "Level:      " + std::to_string(player->GetPlayerLevel()));
	DrawText(renderer, tileMapTexture, 45, 3, "Experience: " + std::to_string(player->GetPlayerExperience()));
	DrawText(renderer, tileMapTexture, 45, 4, "Gold:       " + std::to_string(player->GetPlayerGold()));
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

void UI::DrawInventoryPopup(SDL_Renderer* renderer, SDL_Texture* tileMapTexture, Player* player)
{
	DrawText(renderer, tileMapTexture, 45, 10, "Inventory: " + std::to_string(player->GetPlayerItemsInInventory()));
	DrawText(renderer, tileMapTexture, 45, 11, "Item name:");
	DrawText(renderer, tileMapTexture, 57, 11, "Item stats:");
	DrawText(renderer, tileMapTexture, 70, 11, "Item quantity:");
	DrawText(renderer, tileMapTexture, 86, 11, "Equipped:");
	DrawInventoryItems(renderer, tileMapTexture, player->GetPlayerInventory());
}

void UI::DrawInventoryItems(SDL_Renderer* renderer, SDL_Texture* tileMapTexture, std::vector<Item> inventory)
{
	int itemCount = 0;
	for (Item x : inventory)
	{
		DrawText(renderer, tileMapTexture, 45, 12, x.GetItemName());
		DrawText(renderer, tileMapTexture, 57, 12, std::to_string(x.GetItemBonusStrength()) + " " + std::to_string(x.GetItemBonusDexterity()) + " " + std::to_string(x.GetItemBonusIntellect()));
		DrawText(renderer, tileMapTexture, 86, 12 + itemCount, std::to_string(x.GetIsEquipped()));
		itemCount++;
	}
}

void UI::DrawVendorPopup(SDL_Renderer* renderer, SDL_Texture* tileMapTexture, Vendor* vendor)
{
	DrawText(renderer, tileMapTexture, 45, 10, "Vendor " + vendor->GetVendorName() + ":");
	DrawText(renderer, tileMapTexture, 45, 11, "Item name:");
	DrawText(renderer, tileMapTexture, 57, 11, "Item stats:");
	DrawText(renderer, tileMapTexture, 70, 11, "Item quantity:");
	DrawText(renderer, tileMapTexture, 86, 11, "Item price:");
}

