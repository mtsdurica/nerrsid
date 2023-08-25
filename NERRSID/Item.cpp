#include "Item.h"

Item::Item()
	: itemName("foo"), itemMinimumLevel(1), itemPrice(23), itemBonusStrength(1), itemBonusDexterity(1),
	itemBonusIntellect(1), isEquipped(false), itemClass(Weapon)
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
