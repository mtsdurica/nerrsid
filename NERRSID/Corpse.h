#pragma once
#include "Chest.h"
class Corpse final : public Chest
{

public:
	Corpse();
	Corpse(int positionXCoordinate, int positionYCoordinate);
};

