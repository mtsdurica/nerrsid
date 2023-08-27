#include "Vendor.h"

Vendor::Vendor(std::string vendorName, int positionXCoordinate, int positionYCoordinate)
	: Entity(vendorName, 0, 0, 50, positionXCoordinate, positionYCoordinate)
{
}

Vendor::~Vendor() = default;

void Vendor::RemoveItemFromInventory(int selectedItem)
{
	for (int i = selectedItem; i < this->itemsInInventory; i++)
	{
		this->inventory.at(i) = this->inventory.at(i + 1);
	}
	this->itemsInInventory--;
}
