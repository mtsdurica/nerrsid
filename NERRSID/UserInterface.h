#pragma once

#include <SDL.h>
#include <tuple>

#include "GameEvent.h"
#include "Map.h"
#include "Menu.h"
#include "Player.h"
#include "Tilemap.h"

typedef enum CornerType
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight
} CornerType;

class UserInterface
{
private:
	SDL_Renderer* Renderer;
	SDL_Rect UserInterfaceRect[GameResolutionWidth / 16][GameResolutionHeight / 16];
	void DrawHorizontalLine(SDL_Texture* tilemapTexture, int row, int startingPoint, int endingPoint) const;
	void DrawVerticalLine(SDL_Texture* tilemapTexture, int column, int startingPoint, int endingPoint) const;
	void DrawPopupBorder(SDL_Texture* tilemapTexture) const;
	void DrawCorner(SDL_Texture* tilemapTexture, CornerType cornerType, int column, int row) const;
	void DrawBox(SDL_Texture* tilemapTexture, int topLeftCornerPositionX, int topLeftCornerPositionY, int width, int height) const;

public:
	UserInterface(SDL_Renderer* renderer, int userInterfaceRectWidth, int userInterfaceRectHeight);
	~UserInterface();
	SDL_Renderer* GetRenderer() const;

	void RefreshUserInterface() const;
	void DrawPlayer(SDL_Texture* tilemapTexture, const Player* player) const;
	void DrawPlayerInfo(SDL_Texture* tilemapTexture, const Player* player) const;
	void DrawMap(SDL_Texture* tilemapTexture, Map* map) const;
	void DrawText(SDL_Texture*, int textPositionX, int textPositionY, const std::string& text) const;
	void DrawStatusBar(SDL_Texture* tilemapTexture, const std::string& message) const;
	void DrawInventoryItems(SDL_Texture* tilemapTexture, std::array<Item, 50>* inventory, const int itemsInInventory, const int selectedItem, const int startingItem, const int endingItem) const;
	void DrawEntityPopup(SDL_Texture* tilemapTexture, Player* entity, const int selectedItem, const int startingItem, const int endingItem) const;
	void DrawEntityPopup(SDL_Texture* tilemapTexture, Vendor* entity, const int selectedItem, const int startingItem, const int endingItem) const;
	void DrawEntityPopup(SDL_Texture* tilemapTexture, Chest* entity, const int selectedItem, const int startingItem, const int endingItem) const;
	void DrawStartupMenu(SDL_Texture* tilemapTexture, const int selectedItem) const;
	void DrawPlayerClassSelection(SDL_Texture* tilemapTexture, const int selectedItem) const;
	void DrawPlayerCreationName(SDL_Texture* tilemapTexture, const std::string& playerName) const;

	void UpdateUserInterface(SDL_Texture* tilemapTexture, Map* map, const Player* player, Vendor* vendor, const Menu* menu, const std::string& message) const;
	void UpdateUserInterface(SDL_Texture* tilemapTexture, Map* map, const Player* player, Chest* chest, const Menu* menu, const std::string& message) const;
	void UpdateUserInterface(SDL_Texture* tilemapTexture, Map* map, Player* player, const Menu* menu, const std::string& message) const;
	void UpdateUserInterface(SDL_Texture* tilemapTexture, Map* map, const Player* player, const std::string& message) const;
};