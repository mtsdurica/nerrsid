#include "Vendor.h"

Vendor::Vendor(std::string vendorName, int vendorPosX, int vendorPosY) : vendorName(std::move(vendorName)), vendorItemsInInventory(0), vendorMaximumItemsInInventory(50), vendorPosX(vendorPosX), vendorPosY(vendorPosY)
{
	///TODO: Random generation of items in inventory
}

Vendor::~Vendor() = default;

std::string Vendor::GetVendorName() const
{
	return this->vendorName;
}

int Vendor::GetVendorGold() const
{
	return this->vendorGold;
}

std::vector<Item>* Vendor::GetVendorInventory()
{
	return &this->vendorInventory;
}

int Vendor::GetVendorItemsInInventory() const
{
	return this->vendorItemsInInventory;
}

int Vendor::GetVendorMaximumItemsInInventory() const
{
	return this->vendorMaximumItemsInInventory;
}

int Vendor::GetVendorPosX() const
{
	return this->vendorPosX;
}

int Vendor::GetVendorPosY() const
{
	return this->vendorPosY;
}

void Vendor::SetVendorGold(int vendorGold)
{
	this->vendorGold = vendorGold;
}

void Vendor::SetVendorItemsInInventory(int vendorItemsInInventory)
{
	this->vendorItemsInInventory = vendorItemsInInventory;
}

bool Vendor::InsertIntoVendorInventory(Item item)
{
	if (this->vendorItemsInInventory < this->vendorMaximumItemsInInventory)
	{
		this->vendorItemsInInventory++;
		this->vendorInventory.push_back(item);
		return true;
	}
	return false;
}



