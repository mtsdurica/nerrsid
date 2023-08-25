#include <string>

#include "UI.h"

UI::UI(SDL_Renderer* renderer) : renderer(renderer)
{
	for (int x = 0; x < MAX_X * 2; x++)
	{
		for (int y = 0; y < MAX_Y; y++)
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
void UI::refreshUserInterface()
{
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
	SDL_RenderClear(this->renderer);
	SDL_Delay(30);
}
void UI::drawMap()
{

}
void UI::drawPlayer(SDL_Renderer* renderer, SDL_Texture* tileMap, Player* player)
{
	SDL_Rect playerTile = Tilemap::findTile(0, 4);

	SDL_RenderCopy(renderer,
		tileMap,
		&playerTile,
		&userInterfaceRect[player->GetPlayerPosX()][player->GetPlayerPosY()]);
}
void UI::drawText(SDL_Renderer* renderer, SDL_Texture* tileMap, int posX, int posY, std::string text)
{
	/// TODO: Add rest of characters
	SDL_Rect letterTile;
	for (int index = 0; index < text.length(); index++)
	{
		letterTile = Tilemap::charToRect(text[index]);
		SDL_RenderCopy(renderer,
			tileMap,
			&letterTile,
			&userInterfaceRect[posX + index][posY]);
	}
}
void UI::drawPlayerInfo(SDL_Renderer* renderer, SDL_Texture* tileMap, Player* player)
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
	drawText(renderer, tileMap, 45, 0, "Name:       " + player->GetPlayerName());
	drawText(renderer, tileMap, 45, 1, "Class:      " + classString);
	drawText(renderer, tileMap, 45, 2, "Level:      " + std::to_string(player->GetPlayerLevel()));
	drawText(renderer, tileMap, 45, 3, "Experience: " + std::to_string(player->GetPlayerExperience()));
	drawText(renderer, tileMap, 45, 4, "Gold:       " + std::to_string(player->GetPlayerGold()));
	drawText(renderer, tileMap, 45, 5, "Strength:   " + std::to_string(player->GetPlayerStrength()));
	drawText(renderer, tileMap, 45, 6, "Dexterity:  " + std::to_string(player->GetPlayerDexterity()));
	drawText(renderer, tileMap, 45, 7, "Intellect:  " + std::to_string(player->GetPlayerIntellect()));
}
void UI::dumpMap(SDL_Renderer* renderer, Map* map, Tilemap* tileMap)
{
	SDL_Rect wallTile = Tilemap::findTile(3, 2);
	SDL_Rect walkableTile = Tilemap::findTile(0, 0);


	for (int x = 0; x < MAX_X; x++)
	{
		for (int y = 0; y < MAX_Y; y++)
		{
			switch (map->getMapTiles()[x][y])
			{
			case Wall:
				SDL_RenderCopy(renderer, tileMap->GetTileMapTexture(), &wallTile, &this->userInterfaceRect[x][y]);
				break;
			case Walkable:
				SDL_RenderCopy(renderer, tileMap->GetTileMapTexture(), &walkableTile, &this->userInterfaceRect[x][y]);
				break;
			default:
				break;
			}
		}
	}
}