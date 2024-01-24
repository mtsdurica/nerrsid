#include "Vendor.h"

Vendor::Vendor() : Chest()
{
}

Vendor::Vendor(const std::string& vendorName, const int positionXCoordinate, const int positionYCoordinate)
	: Chest(vendorName, positionXCoordinate, positionYCoordinate, Util::WalkableTile)
{
}