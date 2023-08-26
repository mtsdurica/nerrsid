#include "Item.h"

Item::Item(std::string itemName, int itemBonusStrength, int itemBonusDexterity, int itemBonusIntellect)
	: itemName(std::move(itemName)), itemMinimumLevel(1), itemPrice(23), itemBonusStrength(itemBonusStrength), itemBonusDexterity(itemBonusDexterity),
	itemBonusIntellect(itemBonusIntellect), isEquipped(false), itemClass(Weapon)
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