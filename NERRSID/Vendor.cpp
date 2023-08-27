#include "Vendor.h"

Vendor::Vendor(std::string vendorName, int positionXCoordinate, int positionYCoordinate)
	: Entity(vendorName, 0, 0, 50, positionXCoordinate, positionYCoordinate)
{
}

Vendor::~Vendor() = default;




