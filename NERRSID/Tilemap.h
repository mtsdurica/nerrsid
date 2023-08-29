#pragma once
#include <SDL.h>
#include <string>

/// Lowercase definitions
#define alpha_a Tilemap::FindTile(1, 6)
#define alpha_b Tilemap::FindTile(2, 6)
#define alpha_c Tilemap::FindTile(3, 6)
#define alpha_d Tilemap::FindTile(4, 6)
#define alpha_e Tilemap::FindTile(5, 6)
#define alpha_f Tilemap::FindTile(6, 6)
#define alpha_g Tilemap::FindTile(7, 6)
#define alpha_h Tilemap::FindTile(8, 6)
#define alpha_i Tilemap::FindTile(9, 6)
#define alpha_j Tilemap::FindTile(10, 6)
#define alpha_k Tilemap::FindTile(11, 6)
#define alpha_l Tilemap::FindTile(12, 6)
#define alpha_m Tilemap::FindTile(13, 6)
#define alpha_n Tilemap::FindTile(14, 6)
#define alpha_o Tilemap::FindTile(15, 6)
#define alpha_p Tilemap::FindTile(0, 7)
#define alpha_q Tilemap::FindTile(1, 7)
#define alpha_r Tilemap::FindTile(2, 7)
#define alpha_s Tilemap::FindTile(3, 7)
#define alpha_t Tilemap::FindTile(4, 7)
#define alpha_u Tilemap::FindTile(5, 7)
#define alpha_v Tilemap::FindTile(6, 7)
#define alpha_w Tilemap::FindTile(7, 7)
#define alpha_x Tilemap::FindTile(8, 7)
#define alpha_y Tilemap::FindTile(9, 7)
#define alpha_z Tilemap::FindTile(10, 7)
/// Capital definitions
#define alpha_A Tilemap::FindTile(1, 4)
#define alpha_B Tilemap::FindTile(2, 4)
#define alpha_C Tilemap::FindTile(3, 4)
#define alpha_D Tilemap::FindTile(4, 4)
#define alpha_E Tilemap::FindTile(5, 4)
#define alpha_F Tilemap::FindTile(6, 4)
#define alpha_G Tilemap::FindTile(7, 4)
#define alpha_H Tilemap::FindTile(8, 4)
#define alpha_I Tilemap::FindTile(9, 4)
#define alpha_J Tilemap::FindTile(10, 4)
#define alpha_K Tilemap::FindTile(11, 4)
#define alpha_L Tilemap::FindTile(12, 4)
#define alpha_M Tilemap::FindTile(13, 4)
#define alpha_N Tilemap::FindTile(14, 4)
#define alpha_O Tilemap::FindTile(15, 4)
#define alpha_P Tilemap::FindTile(0, 5)
#define alpha_Q Tilemap::FindTile(1, 5)
#define alpha_R Tilemap::FindTile(2, 5)
#define alpha_S Tilemap::FindTile(3, 5)
#define alpha_T Tilemap::FindTile(4, 5)
#define alpha_U Tilemap::FindTile(5, 5)
#define alpha_V Tilemap::FindTile(6, 5)
#define alpha_W Tilemap::FindTile(7, 5)
#define alpha_X Tilemap::FindTile(8, 5)
#define alpha_Y Tilemap::FindTile(9, 5)
#define alpha_Z Tilemap::FindTile(10, 5)
/// Numerical definitions
#define num_0 Tilemap::FindTile(0, 3)
#define num_1 Tilemap::FindTile(1, 3)
#define num_2 Tilemap::FindTile(2, 3)
#define num_3 Tilemap::FindTile(3, 3)
#define num_4 Tilemap::FindTile(4, 3)
#define num_5 Tilemap::FindTile(5, 3)
#define num_6 Tilemap::FindTile(6, 3)
#define num_7 Tilemap::FindTile(7, 3)
#define num_8 Tilemap::FindTile(8, 3)
#define num_9 Tilemap::FindTile(9, 3)
/// Other
#define space Tilemap::FindTile(0, 0)
#define colon Tilemap::FindTile(10, 3)
#define line_horizontal Tilemap::FindTile(4,12)
#define line_vertical Tilemap::FindTile(3,11)
#define corner_top_right Tilemap::FindTile(15,11)
#define corner_top_left Tilemap::FindTile(10,13)
#define corner_bottom_left Tilemap::FindTile(0,12)
#define corner_bottom_right Tilemap::FindTile(9,13)

class Tilemap
{
private:
	SDL_Texture* tileMapTexture;
public:
	Tilemap(SDL_Renderer* renderer);
	~Tilemap();
	static SDL_Rect FindTile(int tilePositionX, int tilePositionY);
	SDL_Texture* GetTileMapTexture() const;
	static SDL_Rect CharToRect(char srcChar);
};

