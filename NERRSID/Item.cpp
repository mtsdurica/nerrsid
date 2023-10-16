#include "Item.h"
#include "Player.h"


Item::Item()
	: ItemMinimumLevel(-1), ItemPrice(-1), ItemBonusStrength(-1), ItemBonusDexterity(-1), ItemBonusIntellect(-1),
	IsEquipped(false),
	ItemClass(UndefinedItemClass)
{
}

Item::Item(std::string itemName, const ItemClassT itemClass, const int itemPrice, const int itemBonusStrength, const int itemBonusDexterity, const int itemBonusIntellect)
	: ItemName(std::move(itemName)), ItemMinimumLevel(1), ItemPrice(itemPrice), ItemBonusStrength(itemBonusStrength), ItemBonusDexterity(itemBonusDexterity),
	ItemBonusIntellect(itemBonusIntellect), IsEquipped(false), ItemClass(itemClass)
{
}

Item::~Item() = default;

std::string Item::GetItemName()
{
	return this->ItemName;
}

int Item::GetItemMinimumLevel() const
{
	return this->ItemMinimumLevel;
}

int Item::GetItemPrice() const
{
	return this->ItemPrice;
}

int Item::GetItemBonusStrength() const
{
	return this->ItemBonusStrength;
}

int Item::GetItemBonusDexterity() const
{
	return this->ItemBonusDexterity;
}

int Item::GetItemBonusIntellect() const
{
	return this->ItemBonusIntellect;
}

bool Item::GetIsEquipped() const
{
	return this->IsEquipped;
}

ItemClassT Item::GetItemClass() const
{
	return this->ItemClass;
}

void Item::SetIsEquipped(const bool isEquipped)
{
	this->IsEquipped = isEquipped;
}

