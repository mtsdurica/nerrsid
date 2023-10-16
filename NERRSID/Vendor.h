#pragma once

#include <string>

#include "Entity.h"
#include "Player.h"

class Vendor final : public Entity
{
private:
	static int RandomInRange(int min, int max);
public:
	Vendor();
	Vendor(const std::string& vendorName, int positionXCoordinate, int positionYCoordinate);
	void RemoveItemFromInventory(int selectedItem);
	bool CreateInventory();
};