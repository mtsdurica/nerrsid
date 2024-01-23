#pragma once
#include <string>


typedef enum ItemClass
{
	UndefinedItemClass = -1,
	Weapon,
	Helmet,
	Chestplate,
	Leggings,
} ItemClassT;

class Player;

class Item
{
private:
	std::string ItemName;
	std::string AnimatedItemName;
	int LastUpdate;
	int ItemMinimumLevel;
	int ItemPrice;
	int ItemBonusStrength;
	int ItemBonusDexterity;
	int ItemBonusIntellect;
	bool IsEquipped;
	ItemClassT ItemClass;

public:
	Item();
	/// TODO: Add itemMinimumLevel to constructor
	Item(std::string itemName, ItemClassT itemClass, int itemPrice, int itemBonusStrength, int itemBonusDexterity, int itemBonusIntellect);
	~Item();
	std::string GetItemName();
	std::string GetAnimatedItemName();
	int GetLastUpdate() const;
	int GetItemMinimumLevel() const;
	int GetItemPrice() const;
	int GetItemBonusStrength() const;
	int GetItemBonusDexterity() const;
	int GetItemBonusIntellect() const;
	bool GetIsEquipped() const;
	ItemClassT GetItemClass() const;
	void SetLastUpdate(const int lastUpate);
	void SetAnimatedItemName(const std::string& animatedItemName);
	void SetIsEquipped(bool isEquipped);
};