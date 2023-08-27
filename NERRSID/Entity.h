#pragma once
#include <string>
#include <array>

#include "Item.h"

class Entity
{
protected:
	std::string name;
	int gold;
	std::array<Item, 50> inventory;
	int itemsInInventory;
	int maximumItemsInInventory;
	int positionXCoordinate;
	int positionYCoordinate;
public:
	Entity(std::string name, int gold, int itemsInInventory, int maximumItemsInInventory, int positionXCoordinate, int positionYCoordinate);
	virtual ~Entity();
	std::string GetName() const;
	int GetGold() const;
	std::array<Item, 50>* GetInventory();
	int GetItemsInInventory() const;
	int GetMaximumItemsInInventory() const;
	int GetPositionXCoordinate() const;
	int GetPositionYCoordinate() const;
	void SetName(const std::string& name);
	void SetGold(int gold);
	void SetItemsInInventory(int itemsInInventory);
	bool InsertIntoInventory(Item item);
	void SetPositionXCoordinate(int positionXCoordinate);
	void SetPositionYCoordinate(int positionYCoordinate);
};
