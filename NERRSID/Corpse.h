#pragma once
#include "Chest.h"
#include "Util.h"
class Corpse final : public Chest
{
public:
	Corpse();
	Corpse(int positionXCoordinate, int positionYCoordinate, Util::Tiles standingOnTile);
};

