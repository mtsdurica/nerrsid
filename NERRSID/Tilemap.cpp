#include "Tilemap.h"

Tilemap::Tilemap(SDL_Renderer* renderer)
{
	this->tileMapTexture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("tilemap.bmp"));
}
Tilemap::~Tilemap()
{
	SDL_DestroyTexture(tileMapTexture);
}
SDL_Rect Tilemap::findTile(int positionX, int positionY)
{
	SDL_Rect foundTile;
	foundTile.x = positionX * 16;
	foundTile.y = positionY * 16;
	foundTile.w = 16;
	foundTile.h = 16;

	return foundTile;
}
SDL_Texture* Tilemap::GetTileMapTexture() const
{
	return tileMapTexture;
}
