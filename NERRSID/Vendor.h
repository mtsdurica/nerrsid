#pragma once

#include <string>

class Vendor
{
private:
	std::string vendorName;
	int vendorGold;
	/// Vendor item array?
	int vendorItemsInInventory;
	int vendorPosX;
	int vendorPosY;
public:
	Vendor(std::string vendorName, int vendorPosX, int vendorPosY);
	~Vendor();
	std::string GetVendorName() const;
	int GetVendorGold() const;
	int GetVendorItemsInInventory() const;
	int GetVendorPosX() const;
	int GetVendorPosY() const;
	void SetVendorGold(int vendorGold);
	void SetVendorItemsInInventory(int vendorItemsInInventory);
};

