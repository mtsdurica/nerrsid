#include "Vendor.h"
#include "Map.h"

Vendor::Vendor() : Entity("", 0, 0, 0, 0, 0)
{
}

Vendor::Vendor(std::string vendorName, int positionXCoordinate, int positionYCoordinate)
	: Entity(vendorName, 0, 0, 5, positionXCoordinate, positionYCoordinate)
{
}

Vendor::~Vendor() = default;

/// TODO: Move to separate inventory class so it could be used for player as well
void Vendor::RemoveItemFromInventory(int selectedItem)
{
	for (int i = selectedItem; i < this->itemsInInventory; i++)
	{
		this->inventory.at(i) = this->inventory.at(i + 1);
	}
	this->itemsInInventory--;
}

int Vendor::RandomInRange(int min, int max)
{
	return (rand() % (max + 1 - min) + min);
}

void Vendor::CreateInventory()
{
	std::array<Item, 5> itemShuffleBag =
	{
		Item("Estoc", Weapon, 0, 1, 0, 0),
		Item("Spanghelm", Helmet, 0, 2, 0, 0),
		Item("Shotel", Weapon, 0, 3, 0, 0),
		Item("Greateaxe", Weapon, 0, 4, 0, 0),
		Item("Balder helm", Helmet, 0, 5, 0, 0),
	};

	this->itemsInInventory = Vendor::RandomInRange(1, 5);
	for (int i = 0; i < this->itemsInInventory; i++)
	{
		int selectedItem = Vendor::RandomInRange(0, 4);
		this->inventory.at(i) = itemShuffleBag.at(selectedItem);
	}
}
