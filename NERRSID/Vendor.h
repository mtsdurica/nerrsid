#pragma once

#include <string>

#include "Chest.h"

class Vendor final : public Chest
{
private:
public:
	Vendor();
	Vendor(const std::string& vendorName, int positionXCoordinate, int positionYCoordinate);
};