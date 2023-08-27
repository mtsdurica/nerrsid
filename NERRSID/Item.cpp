#include "Item.h"
#include "Player.h"

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

std::string Item::EquipItem(Player* player)
{
	switch (this->itemClass)
	{
	case Weapon:
		if (player->GetEquippedWeapon())
			player->GetEquippedWeapon()->UnequipItem(player);
		player->SetEquippedWeapon(this);
		break;
	case Helmet:
		if (player->GetEquippedHelmet())
			player->GetEquippedHelmet()->UnequipItem(player);
		player->SetEquippedHelmet(this);
		break;
	case Chestplate:
		if (player->GetEquippedChestplate())
			player->GetEquippedChestplate()->UnequipItem(player);
		player->SetEquippedChestplate(this);
		break;
	case Leggings:
		if (player->GetEquippedLeggings())
			player->GetEquippedLeggings()->UnequipItem(player);
		player->SetEquippedLeggings(this);
		break;
	}
	player->SetPlayerStrength(player->GetPlayerStrength() + this->itemBonusStrength);
	player->SetPlayerDexterity(player->GetPlayerDexterity() + this->itemBonusDexterity);
	player->SetPlayerIntellect(player->GetPlayerIntellect() + this->itemBonusIntellect);
	this->isEquipped = true;
	return "You equipped " + this->itemName;
}

std::string Item::UnequipItem(Player* player)
{
	switch (this->itemClass)
	{
	case Weapon:
		player->SetEquippedWeapon(nullptr);
		break;
	case Helmet:
		player->SetEquippedHelmet(nullptr);
		break;
	case Chestplate:
		player->SetEquippedChestplate(nullptr);
		break;
	case Leggings:
		player->SetEquippedLeggings(nullptr);
		break;
	}
	player->SetPlayerStrength(player->GetPlayerStrength() - this->itemBonusStrength);
	player->SetPlayerDexterity(player->GetPlayerDexterity() - this->itemBonusDexterity);
	player->SetPlayerIntellect(player->GetPlayerIntellect() - this->itemBonusIntellect);
	this->isEquipped = false;
	return "You unequipped " + this->itemName;
}