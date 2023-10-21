#include "Corpse.h"

Corpse::Corpse()
{
}

Corpse::Corpse(const int positionXCoordinate, const int positionYCoordinate)
	: Chest(positionXCoordinate, positionYCoordinate)
{
}

Corpse::~Corpse() = default;
