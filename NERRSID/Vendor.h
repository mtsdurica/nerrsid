#pragma once

#include <string>

#include "Entity.h"
#include "Player.h"

class Vendor : public Entity
{
private:
	static int RandomInRange(int min, int max);
public:
	Vendor();
	Vendor(std::string vendorName, int vendorPosX, int vendorPosY);
	~Vendor();
	void RemoveItemFromInventory(int selectedItem);
	bool CreateInventory();
};

