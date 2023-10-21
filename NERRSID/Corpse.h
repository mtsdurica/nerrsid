#pragma once
#include "Chest.h"
class Corpse : public Chest
{

public:
	Corpse();
	Corpse(int positionXCoordinate, int positionYCoordinate);
	~Corpse();
};

