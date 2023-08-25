#pragma once
#include <SDL.h>
#include <string>

/// Lowercase definitions
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
/// Capital definitions
#define alpha_A Tilemap::findTile(1, 4)
#define alpha_B Tilemap::findTile(2, 4)
#define alpha_C Tilemap::findTile(3, 4)
#define alpha_D Tilemap::findTile(4, 4)
#define alpha_E Tilemap::findTile(5, 4)
#define alpha_F Tilemap::findTile(6, 4)
#define alpha_G Tilemap::findTile(7, 4)
#define alpha_H Tilemap::findTile(8, 4)
#define alpha_I Tilemap::findTile(9, 4)
#define alpha_J Tilemap::findTile(10, 4)
#define alpha_K Tilemap::findTile(11, 4)
#define alpha_L Tilemap::findTile(12, 4)
#define alpha_M Tilemap::findTile(13, 4)
#define alpha_N Tilemap::findTile(14, 4)
#define alpha_O Tilemap::findTile(15, 4)
#define alpha_P Tilemap::findTile(0, 5)
#define alpha_Q Tilemap::findTile(1, 5)
#define alpha_R Tilemap::findTile(2, 5)
#define alpha_S Tilemap::findTile(3, 5)
#define alpha_T Tilemap::findTile(4, 5)
#define alpha_U Tilemap::findTile(5, 5)
#define alpha_V Tilemap::findTile(6, 5)
#define alpha_W Tilemap::findTile(7, 5)
#define alpha_X Tilemap::findTile(8, 5)
#define alpha_Y Tilemap::findTile(9, 5)
#define alpha_Z Tilemap::findTile(10, 5)
/// Numerical definitions
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
/// Other
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
	static SDL_Rect charToRect(char);
};

