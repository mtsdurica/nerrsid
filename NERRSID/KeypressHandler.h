#pragma once

#include <SDL.h>

#include <string>

class KeypressHandler
{
public:
	static std::string SDLKeycodeToChar(SDL_Keysym keysym);
};

