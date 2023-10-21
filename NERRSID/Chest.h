#pragma once
#include "Entity.h"
class Chest : public Entity
{
private:
	static int RandomInRange(int min, int max);
public:
	Chest();
	Chest(const std::string& name, int positionXCoordinate, int positionYCoordinate);
	Chest(int positionXCoordinate, int positionYCoordinate);
	void RemoveItemFromInventory(int selectedItem);
	bool CreateInventory();
};

