#include "Tilemap.h"

Tilemap::Tilemap(SDL_Renderer* renderer)
{
	// Tilemap downloaded from here under public domain license:
	// http://www.bay12forums.com/smf/index.php?topic=144897.0
	this->TileMapTexture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("tilemap.bmp"));
}

Tilemap::~Tilemap()
{
	SDL_DestroyTexture(TileMapTexture);
}

SDL_Rect Tilemap::FindTile(const int tilePositionX, const int tilePositionY)
{
	SDL_Rect foundTile;
	foundTile.x = tilePositionX * 16;
	foundTile.y = tilePositionY * 16;
	foundTile.w = 16;
	foundTile.h = 16;

	return foundTile;
}

SDL_Texture* Tilemap::GetTileMapTexture() const
{
	return TileMapTexture;
}

SDL_Rect Tilemap::CharToRect(const char srcChar)
{
	switch (srcChar)
	{
	case 'a':
		return ALPHA_a;
	case 'b':
		return ALPHA_b;
	case 'c':
		return ALPHA_c;
	case 'd':
		return ALPHA_d;
	case 'e':
		return ALPHA_e;
	case 'f':
		return ALPHA_f;
	case 'g':
		return ALPHA_g;
	case 'h':
		return ALPHA_h;
	case 'i':
		return ALPHA_i;
	case 'j':
		return ALPHA_j;
	case 'k':
		return ALPHA_k;
	case 'l':
		return ALPHA_l;
	case 'm':
		return ALPHA_m;
	case 'n':
		return ALPHA_n;
	case 'o':
		return ALPHA_o;
	case 'p':
		return ALPHA_p;
	case 'q':
		return ALPHA_q;
	case 'r':
		return ALPHA_r;
	case 's':
		return ALPHA_s;
	case 't':
		return ALPHA_t;
	case 'u':
		return ALPHA_u;
	case 'v':
		return ALPHA_v;
	case 'w':
		return ALPHA_w;
	case 'x':
		return ALPHA_x;
	case 'y':
		return ALPHA_y;
	case 'z':
		return ALPHA_z;
	case 'A':
		return ALPHA_A;
	case 'B':
		return ALPHA_B;
	case 'C':
		return ALPHA_C;
	case 'D':
		return ALPHA_D;
	case 'E':
		return ALPHA_E;
	case 'F':
		return ALPHA_F;
	case 'G':
		return ALPHA_G;
	case 'H':
		return ALPHA_H;
	case 'I':
		return ALPHA_I;
	case 'J':
		return ALPHA_J;
	case 'K':
		return ALPHA_K;
	case 'L':
		return ALPHA_L;
	case 'M':
		return ALPHA_M;
	case 'N':
		return ALPHA_N;
	case 'O':
		return ALPHA_O;
	case 'P':
		return ALPHA_P;
	case 'Q':
		return ALPHA_Q;
	case 'R':
		return ALPHA_R;
	case 'S':
		return ALPHA_S;
	case 'T':
		return ALPHA_T;
	case 'U':
		return ALPHA_U;
	case 'V':
		return ALPHA_V;
	case 'W':
		return ALPHA_W;
	case 'X':
		return ALPHA_X;
	case 'Y':
		return ALPHA_Y;
	case 'Z':
		return ALPHA_Z;
	case '0':
		return NUM_0;
	case '1':
		return NUM_1;
	case '2':
		return NUM_2;
	case '3':
		return NUM_3;
	case '4':
		return NUM_4;
	case '5':
		return NUM_5;
	case '6':
		return NUM_6;
	case '7':
		return NUM_7;
	case '8':
		return NUM_8;
	case '9':
		return NUM_9;
	case ' ':
		return SPACE;
	case ':':
		return COLON;
	case '#':
		return HASH;
	case '.':
		return DOT;
	}
}