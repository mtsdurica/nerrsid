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

SDL_Rect Tilemap::charToRect(char srcChar)
{
	switch (srcChar)
	{
	case 'a':
		return alpha_a;
		break;
	case 'b':
		return alpha_b;
		break;
	case 'c':
		return alpha_c;
		break;
	case 'd':
		return alpha_d;
		break;
	case 'e':
		return alpha_e;
		break;
	case 'f':
		return alpha_f;
		break;
	case 'g':
		return alpha_g;
		break;
	case 'h':
		return alpha_h;
		break;
	case 'i':
		return alpha_i;
		break;
	case 'j':
		return alpha_j;
		break;
	case 'k':
		return alpha_k;
		break;
	case 'l':
		return alpha_l;
		break;
	case 'm':
		return alpha_m;
		break;
	case 'n':
		return alpha_n;
		break;
	case 'o':
		return alpha_o;
		break;
	case 'p':
		return alpha_p;
		break;
	case 'q':
		return alpha_q;
		break;
	case 'r':
		return alpha_r;
		break;
	case 's':
		return alpha_s;
		break;
	case 't':
		return alpha_t;
		break;
	case 'u':
		return alpha_u;
		break;
	case 'v':
		return alpha_v;
		break;
	case 'w':
		return alpha_w;
		break;
	case 'x':
		return alpha_x;
		break;
	case 'y':
		return alpha_y;
		break;
	case 'z':
		return alpha_z;
		break;
	case 'A':
		return alpha_A;
		break;
	case 'B':
		return alpha_B;
		break;
	case 'C':
		return alpha_C;
		break;
	case 'D':
		return alpha_D;
		break;
	case 'E':
		return alpha_E;
		break;
	case 'F':
		return alpha_F;
		break;
	case 'G':
		return alpha_G;
		break;
	case 'H':
		return alpha_H;
		break;
	case 'I':
		return alpha_I;
		break;
	case 'J':
		return alpha_J;
		break;
	case 'K':
		return alpha_K;
		break;
	case 'L':
		return alpha_M;
		break;
	case 'N':
		return alpha_N;
		break;
	case 'O':
		return alpha_O;
		break;
	case 'P':
		return alpha_P;
		break;
	case 'Q':
		return alpha_Q;
		break;
	case 'R':
		return alpha_R;
		break;
	case 'S':
		return alpha_S;
		break;
	case 'T':
		return alpha_T;
		break;
	case 'U':
		return alpha_U;
		break;
	case 'V':
		return alpha_V;
		break;
	case 'W':
		return alpha_W;
		break;
	case 'X':
		return alpha_X;
		break;
	case 'Y':
		return alpha_Y;
		break;
	case 'Z':
		return alpha_Z;
		break;
	case '0':
		return num_0;
		break;
	case '1':
		return num_1;
		break;
	case '2':
		return num_2;
		break;
	case '3':
		return num_3;
		break;
	case '4':
		return num_4;
		break;
	case '5':
		return num_5;
		break;
	case '6':
		return num_6;
		break;
	case '7':
		return num_7;
		break;
	case '8':
		return num_8;
		break;
	case '9':
		return num_9;
		break;
	case ' ':
		return space;
		break;
	case ':':
		return colon;
		break;
	}
}
