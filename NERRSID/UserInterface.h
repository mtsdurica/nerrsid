#pragma once

#include <SDL.h>
#include <tuple>

#include "Map.h"
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
	void DrawMap(Map* map, const Tilemap* tilemap) const;
	void DrawText(SDL_Texture*, int textPositionX, int textPositionY, const std::string& text) const;
	void DrawStatusBar(SDL_Texture* tilemapTexture, const std::string& message) const;
	void DrawInventoryPopup(SDL_Texture* tilemapTexture, Player* player, int selectedItem, int startingItem, int endingItem) const;
	void DrawInventoryItems(SDL_Texture* tilemapTexture, std::array<Item, 50>* inventory, int itemsInInventory, int selectedItem, int startingItem, int endingItem) const;
	void DrawVendorPopup(SDL_Texture* tilemapTexture, Vendor* vendor, int selectedItem, int startingItem, int endingItem) const;
	void DrawStartupMenu(SDL_Texture* tilemapTexture, int selectedItem) const;
	void DrawPlayerClassSelection(SDL_Texture* tilemapTexture, int selectedItem) const;
	void DrawPlayerCreationName(SDL_Texture* tilemapTexture, const std::string& playerName) const;
};