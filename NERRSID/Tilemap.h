#pragma once
#include <SDL.h>
#include <string>

#define num_0 Tilemap::findTile(0, 3)
#define num_1 Tilemap::findTile(1, 3)
#define num_2 Tilemap::findTile(2, 3)
#define num_3 Tilemap::findTile(3, 3)
#define num_4 Tilemap::findTile(4, 3)
#define num_5 Tilemap::findTile(5, 3)
#define num_6 Tilemap::findTile(6, 3)
#define num_7 Tilemap::findTile(7, 3)
#define num_8 Tilemap::findTile(8, 3)
#define num_9 Tilemap::findTile(9, 3)
#define alpha_a Tilemap::findTile(1, 6)
#define alpha_b Tilemap::findTile(2, 6)
#define alpha_c Tilemap::findTile(3, 6)
#define alpha_d Tilemap::findTile(4, 6)
#define alpha_e Tilemap::findTile(5, 6)
#define alpha_f Tilemap::findTile(6, 6)
#define alpha_g Tilemap::findTile(7, 6)
#define alpha_h Tilemap::findTile(8, 6)
#define alpha_i Tilemap::findTile(9, 6)
#define alpha_j Tilemap::findTile(10, 6)
#define alpha_k Tilemap::findTile(11, 6)
#define alpha_l Tilemap::findTile(12, 6)
#define alpha_m Tilemap::findTile(13, 6)
#define alpha_n Tilemap::findTile(14, 6)
#define alpha_o Tilemap::findTile(15, 6)
#define alpha_p Tilemap::findTile(0, 7)
#define alpha_q Tilemap::findTile(1, 7)
#define alpha_r Tilemap::findTile(2, 7)
#define alpha_s Tilemap::findTile(3, 7)
#define alpha_t Tilemap::findTile(4, 7)
#define alpha_u Tilemap::findTile(5, 7)
#define alpha_v Tilemap::findTile(6, 7)
#define alpha_w Tilemap::findTile(7, 7)
#define alpha_x Tilemap::findTile(8, 7)
#define alpha_y Tilemap::findTile(9, 7)
#define alpha_z Tilemap::findTile(10, 7)
#define space Tilemap::findTile(0, 0)
#define colon Tilemap::findTile(10, 3)


class Tilemap
{
private:
	SDL_Texture* tileMapTexture;
public:
	Tilemap(SDL_Renderer*);
	~Tilemap();
	static SDL_Rect findTile(int, int);
	SDL_Texture* GetTileMapTexture() const;
};

