#include "Corpse.h"

Corpse::Corpse() = default;

Corpse::Corpse(const int positionXCoordinate, const int positionYCoordinate, const Util::Tiles standingOnTile)
	: Chest(positionXCoordinate, positionYCoordinate, standingOnTile)
{
}