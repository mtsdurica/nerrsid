#pragma once

#include <string>
#include <vector>

#include "Item.h"

class Vendor
{
private:
	std::string vendorName;
	int vendorGold;
	std::vector<Item> vendorInventory;
	int vendorItemsInInventory;
	int vendorMaximumItemsInInventory;
	int vendorPosX;
	int vendorPosY;
public:
	Vendor(std::string vendorName, int vendorPosX, int vendorPosY);
	~Vendor();
	std::string GetVendorName() const;
	int GetVendorGold() const;
	std::vector<Item>* GetVendorInventory();
	int GetVendorItemsInInventory() const;
	int GetVendorMaximumItemsInInventory() const;
	int GetVendorPosX() const;
	int GetVendorPosY() const;
	void SetVendorGold(int vendorGold);
	void SetVendorItemsInInventory(int vendorItemsInInventory);
	bool InsertIntoVendorInventory(Item item);
};

