#include "Item.h"
#include "Player.h"


Item::Item()
{
	this->itemName = "";
	this->itemClass = Weapon;
	this->itemBonusStrength = 0;
	this->itemBonusDexterity = 0;
	this->itemBonusIntellect = 0;
}

Item::Item(std::string itemName, itemClass_t itemClass, int itemPrice, int itemBonusStrength, int itemBonusDexterity, int itemBonusIntellect)
	: itemName(std::move(itemName)), itemMinimumLevel(1), itemPrice(itemPrice), itemBonusStrength(itemBonusStrength), itemBonusDexterity(itemBonusDexterity),
	itemBonusIntellect(itemBonusIntellect), isEquipped(false), itemClass(itemClass)
{
}

Item::~Item()
{
}

std::string Item::GetItemName()
{
	return this->itemName;
}

int Item::GetItemMinimumLevel()
{
	return this->itemMinimumLevel;
}

int Item::GetItemPrice()
{
	return this->itemPrice;
}

int Item::GetItemBonusStrength()
{
	return this->itemBonusStrength;
}

int Item::GetItemBonusDexterity()
{
	return this->itemBonusDexterity;
}

int Item::GetItemBonusIntellect()
{
	return this->itemBonusIntellect;
}

bool Item::GetIsEquipped()
{
	return this->isEquipped;
}

itemClass_t Item::GetItemClass()
{
	return this->itemClass;
}

void Item::SetIsEquipped(bool isEquipped)
{
	this->isEquipped = isEquipped;
}

