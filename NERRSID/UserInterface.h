#pragma once

#include <SDL.h>
#include <tuple>

#include "Map.h"
#include "Menu.h"
#include "Player.h"
#include "Util.h"

typedef enum CornerType
{
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight
} CornerType;

typedef enum HelpType
{
	InteractionHelp,
	InventoryHelp,
	VendorHelp,
	ChestHelp,
	CorpseHelp
} HelpType;

class UserInterface
{
private:
	SDL_Renderer* Renderer;
	SDL_Rect UserInterfaceRect[Util::GAME_RESOLUTION_WIDTH / 16][Util::GAME_RESOLUTION_HEIGHT / 16];
	void DrawHorizontalLine(SDL_Texture* tilemapTexture, int row, int startingPoint, int endingPoint) const;
	void DrawVerticalLine(SDL_Texture* tilemapTexture, int column, int startingPoint, int endingPoint) const;
	void DrawPopupBorder(SDL_Texture* tilemapTexture) const;
	void DrawItemDetailsBorder(SDL_Texture* tilemapTexture) const;
	void DrawCorner(SDL_Texture* tilemapTexture, CornerType cornerType, int column, int row) const;
	void DrawBox(SDL_Texture* tilemapTexture, int topLeftCornerPositionX, int topLeftCornerPositionY, int width, int height) const;
	void DrawPlayer(SDL_Texture* tilemapTexture, const Player* player) const;
	void DrawPlayerInfo(SDL_Texture* tilemapTexture, const Player* player) const;
	void DrawMap(SDL_Texture* tilemapTexture, Map* map, const Player* player, bool debugMode) const;
	void DrawText(SDL_Texture*, int textPositionX, int textPositionY, const std::string& text) const;
	std::string DrawAnimatedText(SDL_Texture*, int textPositionX, int textPositionY, const std::string& text, int lastUpdate) const;
	void DrawStatusBar(SDL_Texture* tilemapTexture, const std::string& message) const;
	void DrawInventoryItems(SDL_Texture* tilemapTexture, const Player* player, std::array<Item, 50>* inventory, int itemsInInventory, int selectedItem, int startingItem, int endingItem, bool itemDetails) const;
	void DrawHelp(SDL_Texture* tilemapTexture, HelpType typeOfHelp) const;
	void DrawEntityPopup(SDL_Texture* tilemapTexture, Player* entity, int selectedItem, int startingItem, int endingItem, bool itemDetails) const;
	void DrawEntityPopup(SDL_Texture* tilemapTexture, const Player* player, Vendor* entity, int selectedItem, int startingItem, int endingItem, bool itemDetails) const;
	void DrawEntityPopup(SDL_Texture* tilemapTexture, const Player* player, Chest* entity, int selectedItem, int startingItem, int endingItem, bool isCorpse, bool itemDetails) const;
	void DrawGameLogo(SDL_Texture* tilemapTexture) const;
	// Colored texture
	static void SetTextureToWhite(SDL_Texture* tilemapTexture);
	static void SetTextureToRed(SDL_Texture* tilemapTexture);
	static void SetTextureToGreen(SDL_Texture* tilemapTexture);
	static void SetTextureToBlue(SDL_Texture* tilemapTexture);

public:
	UserInterface(SDL_Renderer* renderer, int userInterfaceRectWidth, int userInterfaceRectHeight);
	~UserInterface();
	SDL_Renderer* GetRenderer() const;
	void RefreshUserInterface() const;
	void DrawStartupMenu(SDL_Texture* tilemapTexture, int selectedItem) const;
	void DrawPlayerClassSelection(SDL_Texture* tilemapTexture, int selectedItem) const;
	void DrawPlayerCreationName(SDL_Texture* tilemapTexture, const std::string& playerName) const;
	void UpdateUserInterface(SDL_Texture* tilemapTexture, Map* map, const Player* player, Vendor* vendor, const Menu* menu, const std::string& message, bool helpDisplayed, bool itemDetails) const;
	void UpdateUserInterface(SDL_Texture* tilemapTexture, Map* map, const Player* player, Chest* chest, const Menu* menu, const std::string& message, bool isCorpse, bool helpDisplayed, bool itemDetails) const;
	void UpdateUserInterface(SDL_Texture* tilemapTexture, Map* map, Player* player, const Menu* menu, const std::string& message, bool helpDisplayed, bool itemDetails) const;
	void UpdateUserInterface(SDL_Texture* tilemapTexture, Map* map, const Player* player, const std::string& message, bool helpDisplayed, bool debugMode) const;
};