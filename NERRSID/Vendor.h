#pragma once

#include <string>

#include "Entity.h";
#include "Player.h"

class Vendor : public Entity
{
public:
	Vendor(std::string vendorName, int vendorPosX, int vendorPosY);
	~Vendor();
	void RemoveItemFromInventory(int selectedItem);
};

