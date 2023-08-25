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
	SDL_Rect letterTile;
	for (int index = 0; index < text.length(); index++)
	{
		switch (text[index])
		{
		case 'a':
			letterTile = alpha_a;
			break;
		case 'b':
			letterTile = alpha_b;
			break;
		case 'c':
			letterTile = alpha_c;
			break;
		case 'd':
			letterTile = alpha_d;
			break;
		case 'e':
			letterTile = alpha_e;
			break;
		case 'f':
			letterTile = alpha_f;
			break;
		case 'g':
			letterTile = alpha_g;
			break;
		case 'h':
			letterTile = alpha_h;
			break;
		case 'i':
			letterTile = alpha_i;
			break;
		case 'j':
			letterTile = alpha_j;
			break;
		case 'k':
			letterTile = alpha_k;
			break;
		case 'l':
			letterTile = alpha_l;
			break;
		case 'm':
			letterTile = alpha_m;
			break;
		case 'n':
			letterTile = alpha_n;
			break;
		case 'o':
			letterTile = alpha_o;
			break;
		case 'p':
			letterTile = alpha_p;
			break;
		case 'q':
			letterTile = alpha_q;
			break;
		case 'r':
			letterTile = alpha_r;
			break;
		case 's':
			letterTile = alpha_s;
			break;
		case 't':
			letterTile = alpha_t;
			break;
		case 'u':
			letterTile = alpha_u;
			break;
		case 'v':
			letterTile = alpha_v;
			break;
		case 'w':
			letterTile = alpha_w;
			break;
		case 'x':
			letterTile = alpha_x;
			break;
		case 'y':
			letterTile = alpha_y;
			break;
		case 'z':
			letterTile = alpha_z;
			break;
		case '0':
			letterTile = num_0;
			break;
		case '1':
			letterTile = num_1;
			break;
		case '2':
			letterTile = num_2;
			break;
		case '3':
			letterTile = num_3;
			break;
		case '4':
			letterTile = num_4;
			break;
		case '5':
			letterTile = num_5;
			break;
		case '6':
			letterTile = num_6;
			break;
		case '7':
			letterTile = num_7;
			break;
		case '8':
			letterTile = num_8;
			break;
		case '9':
			letterTile = num_9;
			break;
		case ' ':
			letterTile = space;
			break;
		case ':':
			letterTile = colon;
			break;
		}
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
		classString = "warrior";
		break;
	case Assassin:
		classString = "assassin";
		break;
	case Wizard:
		classString = "wizard";
		break;
	}
	drawText(renderer, tileMap, 45, 0, "name:		" + player->GetPlayerName());
	drawText(renderer, tileMap, 45, 1, "class:      " + classString);
	drawText(renderer, tileMap, 45, 2, "level:      " + std::to_string(player->GetPlayerLevel()));
	drawText(renderer, tileMap, 45, 3, "experience: " + std::to_string(player->GetPlayerExperience()));
	drawText(renderer, tileMap, 45, 4, "gold:       " + std::to_string(player->GetPlayerGold()));
	drawText(renderer, tileMap, 45, 5, "strength:   " + std::to_string(player->GetPlayerStrength()));
	drawText(renderer, tileMap, 45, 6, "dexterity:  " + std::to_string(player->GetPlayerDexterity()));
	drawText(renderer, tileMap, 45, 7, "intellect:  " + std::to_string(player->GetPlayerIntellect()));
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