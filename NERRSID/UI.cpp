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

void UI::DrawPlayerInfo(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, Player* player)
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
	DrawBox(renderer, tilemapTexture, 44, 0, 55, 9);
	DrawVerticalLine(renderer, tilemapTexture, 71, 1, 9);
	DrawCorner(renderer, tilemapTexture, TopLeft, 71, 0);
	DrawCorner(renderer, tilemapTexture, BottomRight, 71, 9);
	DrawText(renderer, tilemapTexture, 45, 1, "Name:       " + player->GetName());
	DrawText(renderer, tilemapTexture, 45, 2, "Class:      " + classString);
	DrawText(renderer, tilemapTexture, 45, 3, "Level:      " + std::to_string(player->GetPlayerLevel()));
	DrawText(renderer, tilemapTexture, 45, 4, "Experience: " + std::to_string(player->GetPlayerExperience()));
	DrawText(renderer, tilemapTexture, 45, 5, "Gold:       " + std::to_string(player->GetGold()));
	DrawText(renderer, tilemapTexture, 45, 6, "Strength:   " + std::to_string(player->GetPlayerStrength()));
	DrawText(renderer, tilemapTexture, 45, 7, "Dexterity:  " + std::to_string(player->GetPlayerDexterity()));
	DrawText(renderer, tilemapTexture, 45, 8, "Intellect:  " + std::to_string(player->GetPlayerIntellect()));
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

void UI::DrawStatusBar(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, std::string message)
{
	DrawBox(renderer, tilemapTexture, 44, 42, 55, 2);
	DrawText(renderer, tilemapTexture, 45, 43, message);
}

void UI::DrawHorizontalLine(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, int row, int startingPoint, int endingPoint)
{
	SDL_Rect rect = line_horizontal;
	for (int i = startingPoint; i < endingPoint; i++)
	{
		SDL_RenderCopy(renderer,
			tilemapTexture,
			&rect,
			&userInterfaceRect[i][row]);
	}
}

void UI::DrawVerticalLine(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, int column, int startingPoint, int endingPoint)
{
	SDL_Rect rect = line_vertical;
	for (int i = startingPoint; i < endingPoint; i++)
	{
		SDL_RenderCopy(renderer,
			tilemapTexture,
			&rect,
			&userInterfaceRect[column][i]);
	}
}

void UI::DrawCorner(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, cornerType cornerType, int column, int row)
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
	SDL_RenderCopy(renderer, tilemapTexture, &rect, &userInterfaceRect[column][row]);
}

void UI::DrawBox(SDL_Renderer* renderer, SDL_Texture* tilemapTexture, int topLeftCornerPositionX, int topLeftCornerPositionY, int width, int height)
{
	DrawHorizontalLine(renderer, tilemapTexture, topLeftCornerPositionY, topLeftCornerPositionX + 1, topLeftCornerPositionX + width);
	DrawHorizontalLine(renderer, tilemapTexture, topLeftCornerPositionY + height, topLeftCornerPositionX + 1, topLeftCornerPositionX + width);
	DrawVerticalLine(renderer, tilemapTexture, topLeftCornerPositionX, topLeftCornerPositionY + 1, topLeftCornerPositionY + height);
	DrawVerticalLine(renderer, tilemapTexture, topLeftCornerPositionX + width, topLeftCornerPositionY + 1, topLeftCornerPositionY + height);
	DrawCorner(renderer, tilemapTexture, TopLeft, topLeftCornerPositionX, topLeftCornerPositionY);
	DrawCorner(renderer, tilemapTexture, TopRight, topLeftCornerPositionX + width, topLeftCornerPositionY);
	DrawCorner(renderer, tilemapTexture, BottomLeft, topLeftCornerPositionX, topLeftCornerPositionY + height);
	DrawCorner(renderer, tilemapTexture, BottomRight, topLeftCornerPositionX + width, topLeftCornerPositionY + height);
}

void UI::DrawPopupBorder(SDL_Renderer* renderer, SDL_Texture* tilemapTexture)
{
	DrawBox(renderer, tilemapTexture, 44, 9, 55, 14);
	DrawHorizontalLine(renderer, tilemapTexture, 12, 45, 99);
	DrawCorner(renderer, tilemapTexture, TopLeft, 44, 12);
	DrawCorner(renderer, tilemapTexture, TopRight, 99, 12);
}

void UI::DrawInventoryPopup(SDL_Renderer* renderer, SDL_Texture* tileMapTexture, Player* player, int selectedItem, int startingItem, int endingItem)
{
	DrawText(renderer, tileMapTexture, 45, 10, "Inventory: " + std::to_string(player->GetItemsInInventory()));
	DrawText(renderer, tileMapTexture, 46, 11, "Item name:");
	DrawText(renderer, tileMapTexture, 58, 11, "Item stats:");
	DrawText(renderer, tileMapTexture, 71, 11, "Item quantity:");
	DrawText(renderer, tileMapTexture, 87, 11, "Equipped:");
	DrawPopupBorder(renderer, tileMapTexture);
	if (player->GetItemsInInventory())
		DrawInventoryItems(renderer, tileMapTexture, player->GetInventory(), player->GetItemsInInventory(), selectedItem, startingItem, endingItem);
	else
		DrawText(renderer, tileMapTexture, 46, 13, "No items in inventory");
}

void UI::DrawInventoryItems(SDL_Renderer* renderer, SDL_Texture* tileMapTexture, std::array<Item, 50>* inventory, int itemsInInventory, int selectedItem, int startingItem, int endingItem)
{
	if (itemsInInventory <= endingItem)
		endingItem = itemsInInventory;

	int positionOfCursor = 0;
	for (int i = startingItem; i < endingItem; i++)
	{
		if (i == selectedItem)
			DrawText(renderer, tileMapTexture, 45, 13 + positionOfCursor, "1");
		DrawText(renderer, tileMapTexture, 46, 13 + positionOfCursor, inventory->at(i).GetItemName());
		DrawText(renderer, tileMapTexture, 58, 13 + positionOfCursor, std::to_string(inventory->at(i).GetItemBonusStrength()) + " " + std::to_string(inventory->at(i).GetItemBonusDexterity()) + " " + std::to_string(inventory->at(i).GetItemBonusIntellect()));
		DrawText(renderer, tileMapTexture, 87, 13 + positionOfCursor, std::to_string(inventory->at(i).GetIsEquipped()));
		positionOfCursor++;
	}
}

void UI::DrawVendorPopup(SDL_Renderer* renderer, SDL_Texture* tileMapTexture, Vendor* vendor, int selectedItem, int startingItem, int endingItem)
{
	DrawText(renderer, tileMapTexture, 45, 10, "Vendor " + vendor->GetName() + ": " + std::to_string(vendor->GetItemsInInventory()));
	DrawText(renderer, tileMapTexture, 46, 11, "Item name:");
	DrawText(renderer, tileMapTexture, 58, 11, "Item stats:");
	DrawText(renderer, tileMapTexture, 71, 11, "Item quantity:");
	DrawText(renderer, tileMapTexture, 87, 11, "Item price:");
	DrawPopupBorder(renderer, tileMapTexture);
	if (vendor->GetItemsInInventory())
		DrawInventoryItems(renderer, tileMapTexture, vendor->GetInventory(), vendor->GetItemsInInventory(), selectedItem, startingItem, endingItem);
	else
		DrawText(renderer, tileMapTexture, 46, 13, "No items for sale");
}

std::tuple<bool, Player> UI::DrawStartingMenu(SDL_Renderer* renderer, SDL_Texture* tilemapTexture)
{
	SDL_Event eventSDL;
	bool menuIsActive = true;
	bool characterCreationFlag = true;
	int positionOfCursor = 0;
	Menu menu(2);
	Player player("", Warrior, 0, 0);
	std::string playerName = "";
	while (menuIsActive)
	{
		this->RefreshUserInterface();
		for (int i = menu.GetStartingItem(); i < menu.GetEndingItem(); i++)
		{
			if (i == menu.GetSelectedItem())
				DrawText(renderer, tilemapTexture, 0, 0 + i, "1");
			DrawText(renderer, tilemapTexture, 1, 0, "Create new character");
			DrawText(renderer, tilemapTexture, 1, 1, "Exit game");
		}
		SDL_RenderPresent(renderer);
		while (SDL_PollEvent(&eventSDL))
		{
			if (eventSDL.type == SDL_QUIT)
				return { false, player };
			else if (eventSDL.type == SDL_KEYDOWN)
			{
				switch (eventSDL.key.keysym.sym)
				{
				case SDLK_UP:
					menu.ScrollUp();
					break;
				case SDLK_DOWN:
					menu.ScrollDown();
					break;
				case SDLK_RETURN:
					switch (menu.GetSelectedItem())
					{
					case 0:
						this->RefreshUserInterface();
						while (characterCreationFlag)
						{
							DrawText(renderer, tilemapTexture, 0, 0, "Enter name");
							SDL_RenderPresent(renderer);
							while (SDL_PollEvent(&eventSDL))
							{
								DrawText(renderer, tilemapTexture, 0, 1, playerName);
								SDL_RenderPresent(renderer);
								if (eventSDL.type == SDL_QUIT)
									return { false, player };
								else if (eventSDL.type == SDL_KEYDOWN)
								{
									switch (eventSDL.key.keysym.sym)
									{
									case SDLK_a:
										playerName += "a";
										break;
									case SDLK_b:
										playerName += "b";
										break;
									case SDLK_c:
										playerName += "c";
										break;
									case SDLK_d:
										playerName += "d";
										break;
									case SDLK_e:
										playerName += "e";
										break;
									case SDLK_f:
										playerName += "f";
										break;
									case SDLK_g:
										playerName += "g";
										break;
									case SDLK_h:
										playerName += "h";
										break;
									case SDLK_i:
										playerName += "i";
										break;
									case SDLK_j:
										playerName += "j";
										break;
									case SDLK_k:
										playerName += "k";
										break;
									case SDLK_l:
										playerName += "l";
										break;
									case SDLK_m:
										playerName += "m";
										break;
									case SDLK_n:
										playerName += "n";
										break;
									case SDLK_o:
										playerName += "o";
										break;
									case SDLK_p:
										playerName += "p";
										break;
									case SDLK_q:
										playerName += "q";
										break;
									case SDLK_r:
										playerName += "r";
										break;
									case SDLK_s:
										playerName += "s";
										break;
									case SDLK_t:
										playerName += "t";
										break;
									case SDLK_u:
										playerName += "u";
										break;
									case SDLK_v:
										playerName += "v";
										break;
									case SDLK_w:
										playerName += "w";
										break;
									case SDLK_x:
										playerName += "x";
										break;
									case SDLK_y:
										playerName += "y";
										break;
									case SDLK_z:
										playerName += "z";
										break;
									case SDLK_RETURN:
										Player player(playerName, Warrior, 1, 1);
										return{ true, player };
										break;
									}
								}
							}
						}
						break;
					case 1:
						return { false, player };
						break;
					}
					break;
				case SDLK_ESCAPE:
					return { false, player };
					break;
				}
			}
		}
	}
}