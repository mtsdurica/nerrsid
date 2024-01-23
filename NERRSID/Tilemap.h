#pragma once
#include <SDL.h>
#include <string>

/// Lowercase definitions
#define ALPHA_a Tilemap::FindTile(1, 6)
#define ALPHA_b Tilemap::FindTile(2, 6)
#define ALPHA_c Tilemap::FindTile(3, 6)
#define ALPHA_d Tilemap::FindTile(4, 6)
#define ALPHA_e Tilemap::FindTile(5, 6)
#define ALPHA_f Tilemap::FindTile(6, 6)
#define ALPHA_g Tilemap::FindTile(7, 6)
#define ALPHA_h Tilemap::FindTile(8, 6)
#define ALPHA_i Tilemap::FindTile(9, 6)
#define ALPHA_j Tilemap::FindTile(10, 6)
#define ALPHA_k Tilemap::FindTile(11, 6)
#define ALPHA_l Tilemap::FindTile(12, 6)
#define ALPHA_m Tilemap::FindTile(13, 6)
#define ALPHA_n Tilemap::FindTile(14, 6)
#define ALPHA_o Tilemap::FindTile(15, 6)
#define ALPHA_p Tilemap::FindTile(0, 7)
#define ALPHA_q Tilemap::FindTile(1, 7)
#define ALPHA_r Tilemap::FindTile(2, 7)
#define ALPHA_s Tilemap::FindTile(3, 7)
#define ALPHA_t Tilemap::FindTile(4, 7)
#define ALPHA_u Tilemap::FindTile(5, 7)
#define ALPHA_v Tilemap::FindTile(6, 7)
#define ALPHA_w Tilemap::FindTile(7, 7)
#define ALPHA_x Tilemap::FindTile(8, 7)
#define ALPHA_y Tilemap::FindTile(9, 7)
#define ALPHA_z Tilemap::FindTile(10, 7)
/// Capital definitions
#define ALPHA_A Tilemap::FindTile(1, 4)
#define ALPHA_B Tilemap::FindTile(2, 4)
#define ALPHA_C Tilemap::FindTile(3, 4)
#define ALPHA_D Tilemap::FindTile(4, 4)
#define ALPHA_E Tilemap::FindTile(5, 4)
#define ALPHA_F Tilemap::FindTile(6, 4)
#define ALPHA_G Tilemap::FindTile(7, 4)
#define ALPHA_H Tilemap::FindTile(8, 4)
#define ALPHA_I Tilemap::FindTile(9, 4)
#define ALPHA_J Tilemap::FindTile(10, 4)
#define ALPHA_K Tilemap::FindTile(11, 4)
#define ALPHA_L Tilemap::FindTile(12, 4)
#define ALPHA_M Tilemap::FindTile(13, 4)
#define ALPHA_N Tilemap::FindTile(14, 4)
#define ALPHA_O Tilemap::FindTile(15, 4)
#define ALPHA_P Tilemap::FindTile(0, 5)
#define ALPHA_Q Tilemap::FindTile(1, 5)
#define ALPHA_R Tilemap::FindTile(2, 5)
#define ALPHA_S Tilemap::FindTile(3, 5)
#define ALPHA_T Tilemap::FindTile(4, 5)
#define ALPHA_U Tilemap::FindTile(5, 5)
#define ALPHA_V Tilemap::FindTile(6, 5)
#define ALPHA_W Tilemap::FindTile(7, 5)
#define ALPHA_X Tilemap::FindTile(8, 5)
#define ALPHA_Y Tilemap::FindTile(9, 5)
#define ALPHA_Z Tilemap::FindTile(10, 5)
/// Numerical definitions
#define NUM_0 Tilemap::FindTile(0, 3)
#define NUM_1 Tilemap::FindTile(1, 3)
#define NUM_2 Tilemap::FindTile(2, 3)
#define NUM_3 Tilemap::FindTile(3, 3)
#define NUM_4 Tilemap::FindTile(4, 3)
#define NUM_5 Tilemap::FindTile(5, 3)
#define NUM_6 Tilemap::FindTile(6, 3)
#define NUM_7 Tilemap::FindTile(7, 3)
#define NUM_8 Tilemap::FindTile(8, 3)
#define NUM_9 Tilemap::FindTile(9, 3)
/// Other
#define SPACE Tilemap::FindTile(0, 0)
#define COLON Tilemap::FindTile(10, 3)
#define AT Tilemap::FindTile(0, 4)
#define HASH Tilemap::FindTile(3, 2)
#define DOT Tilemap::FindTile(14, 2)
#define AMPERSAND Tilemap::FindTile(6, 2)
#define MINUS Tilemap::FindTile(13, 2)
#define SLASH Tilemap::FindTile(15, 2)




#define LINE_HORIZONTAL Tilemap::FindTile(4, 12)
#define LINE_VERTICAL Tilemap::FindTile(3, 11)
#define CORNER_TOP_RIGHT Tilemap::FindTile(15, 11)
#define CORNER_TOP_LEFT Tilemap::FindTile(10, 13)
#define CORNER_BOTTOM_LEFT Tilemap::FindTile(0, 12)
#define CORNER_BOTTOM_RIGHT Tilemap::FindTile(9, 13)
#define SELECTOR_LEFT Tilemap::FindTile(0, 1)
#define SELECTOR_CENTER Tilemap::FindTile(7, 0)
#define STAIRS Tilemap::FindTile(8, 0)

class Tilemap
{
private:
	SDL_Texture* TileMapTexture;
public:
	explicit Tilemap(SDL_Renderer* renderer);
	~Tilemap();
	static SDL_Rect FindTile(int tilePositionX, int tilePositionY);
	SDL_Texture* GetTileMapTexture() const;
	static SDL_Rect CharToRect(char srcChar);
};