#pragma once
#include <string>


typedef enum itemClass
{
	Weapon,
	Helmet,
	Chestplate,
	Leggings,
} itemClass_t;

class Player;

class Item
{
private:
	std::string itemName;
	int itemMinimumLevel;
	int itemPrice;
	int itemBonusStrength;
	int itemBonusDexterity;
	int itemBonusIntellect;
	bool isEquipped;
	itemClass_t itemClass;

public:
	Item();
	/// TODO: Add itemMinimumLevel to constructor
	Item(std::string itemName, itemClass_t itemClass, int itemPrice, int itemBonusStrength, int itemBonusDexterity, int itemBonusIntellect);
	~Item();
	std::string GetItemName();
	int GetItemMinimumLevel();
	int GetItemPrice();
	int GetItemBonusStrength();
	int GetItemBonusDexterity();
	int GetItemBonusIntellect();
	bool GetIsEquipped();
	itemClass_t GetItemClass();
	void SetIsEquipped(bool isEquipped);
};

