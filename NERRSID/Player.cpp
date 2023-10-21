#include "Player.h"
#include "Map.h"
#include "UserInterface.h"


Player::Player() : Entity(), PlayerClass(UndefinedPlayerClass), PlayerLevel(1),
PlayerExperience(-1), PlayerStrength(-1), PlayerDexterity(-1), PlayerIntellect(-1), EquippedWeapon(nullptr),
EquippedHelmet(nullptr), EquippedChestplate(nullptr), EquippedLeggings(nullptr)
{
}

Player::Player(const std::string& playerName, const PlayerClassT playerClass, const int positionXCoordinate, const int positionYCoordinate)
	: Entity(playerName, 0, 0, 50, positionXCoordinate, positionYCoordinate), PlayerClass(playerClass), PlayerLevel(1),
	PlayerExperience(0), PlayerStrength(0), PlayerDexterity(0), PlayerIntellect(0), PlayerTurn(1), PlayerMovesLeft(1), EquippedWeapon(nullptr),
	EquippedHelmet(nullptr), EquippedChestplate(nullptr), EquippedLeggings(nullptr)
{
	switch (playerClass)
	{
	case Warrior:
		PlayerStrength = 10;
		PlayerDexterity = 5;
		PlayerIntellect = 0;
		break;
	case Wizard:
		PlayerStrength = 0;
		PlayerDexterity = 5;
		PlayerIntellect = 10;
		break;
	case Assassin:
		PlayerStrength = 5;
		PlayerDexterity = 10;
		PlayerIntellect = 0;
		break;
	case UndefinedPlayerClass:
		PlayerStrength = -1;
		PlayerDexterity = -1;
		PlayerIntellect = -1;
		break;
	}
}

PlayerClassT Player::GetPlayerClass() const
{
	return this->PlayerClass;
}

int Player::GetPlayerLevel() const
{
	return this->PlayerLevel;
}

int Player::GetPlayerExperience() const
{
	return this->PlayerExperience;
}

int Player::GetPlayerStrength() const
{
	return this->PlayerStrength;
}

int Player::GetPlayerDexterity() const
{
	return this->PlayerDexterity;
}

int Player::GetPlayerIntellect() const
{
	return this->PlayerIntellect;
}

int Player::GetPlayerTurn() const
{
	return this->PlayerTurn;
}

int Player::GetPlayerMovesLeft() const
{
	return this->PlayerMovesLeft;
}

Item* Player::GetEquippedWeapon() const
{
	return this->EquippedWeapon;
}

Item* Player::GetEquippedHelmet() const
{
	return this->EquippedHelmet;
}

Item* Player::GetEquippedChestplate() const
{
	return this->EquippedChestplate;
}

Item* Player::GetEquippedLeggings() const
{
	return this->EquippedLeggings;
}

void Player::SetPlayerClass(const PlayerClassT playerClass)
{
	this->PlayerClass = playerClass;
}

void Player::SetPlayerLevel(const int playerLevel)
{
	this->PlayerLevel = playerLevel;
}

void Player::SetPlayerExperience(const int playerExperience)
{
	this->PlayerExperience = playerExperience;
}

void Player::SetPlayerStrength(const int playerStrength)
{
	this->PlayerStrength = playerStrength;
}

void Player::SetPlayerDexterity(const int playerDexterity)
{
	this->PlayerDexterity = playerDexterity;
}

void Player::SetPlayerIntellect(const int playerIntellect)
{
	this->PlayerIntellect = playerIntellect;
}

void Player::SetPlayerTurn(const int playerTurn)
{
	this->PlayerTurn = playerTurn;
}

void Player::SetPlayerMovesLeft(const int playerMovesLeft)
{
	this->PlayerMovesLeft = playerMovesLeft;
}

void Player::SetEquippedWeapon(Item* equippedWeapon)
{
	this->EquippedWeapon = equippedWeapon;
}

void Player::SetEquippedHelmet(Item* equippedHelmet)
{
	this->EquippedHelmet = equippedHelmet;
}

void Player::SetEquippedChestplate(Item* equippedChestplate)
{
	this->EquippedChestplate = equippedChestplate;
}

void Player::SetEquippedLeggings(Item* equippedLeggings)
{
	this->EquippedLeggings = equippedLeggings;
}

std::string Player::EquipItem(Item* item)
{
	switch (item->GetItemClass())
	{
	case Weapon:
		if (this->GetEquippedWeapon())
			this->UnequipItem(Weapon);
		this->EquippedWeapon = item;
		this->SetPlayerStrength(this->GetPlayerStrength() + this->EquippedWeapon->GetItemBonusStrength());
		this->SetPlayerDexterity(this->GetPlayerDexterity() + this->EquippedWeapon->GetItemBonusDexterity());
		this->SetPlayerIntellect(this->GetPlayerIntellect() + this->EquippedWeapon->GetItemBonusIntellect());
		break;
	case Helmet:
		if (this->GetEquippedHelmet())
			this->UnequipItem(Helmet);
		this->EquippedHelmet = item;
		this->SetPlayerStrength(this->GetPlayerStrength() + this->EquippedHelmet->GetItemBonusStrength());
		this->SetPlayerDexterity(this->GetPlayerDexterity() + this->EquippedHelmet->GetItemBonusDexterity());
		this->SetPlayerIntellect(this->GetPlayerIntellect() + this->EquippedHelmet->GetItemBonusIntellect());
		break;
	case Chestplate:
		if (this->GetEquippedChestplate())
			this->UnequipItem(Chestplate);
		this->EquippedChestplate = item;
		this->SetPlayerStrength(this->GetPlayerStrength() + this->EquippedChestplate->GetItemBonusStrength());
		this->SetPlayerDexterity(this->GetPlayerDexterity() + this->EquippedChestplate->GetItemBonusDexterity());
		this->SetPlayerIntellect(this->GetPlayerIntellect() + this->EquippedChestplate->GetItemBonusIntellect());
		break;
	case Leggings:
		if (this->GetEquippedLeggings())
			this->UnequipItem(Leggings);
		this->EquippedLeggings = item;
		this->SetPlayerStrength(this->GetPlayerStrength() + this->EquippedLeggings->GetItemBonusStrength());
		this->SetPlayerDexterity(this->GetPlayerDexterity() + this->EquippedLeggings->GetItemBonusDexterity());
		this->SetPlayerIntellect(this->GetPlayerIntellect() + this->EquippedLeggings->GetItemBonusIntellect());
		break;
	case UndefinedItemClass:
		break;
	}
	item->SetIsEquipped(true);

	return "You equipped " + item->GetItemName();
}

std::string Player::UnequipItem(const ItemClassT itemClass)
{
	std::string unequippedItemName;
	switch (itemClass)
	{
	case Weapon:
		this->SetPlayerStrength(this->GetPlayerStrength() - this->GetEquippedWeapon()->GetItemBonusStrength());
		this->SetPlayerDexterity(this->GetPlayerDexterity() - this->GetEquippedWeapon()->GetItemBonusDexterity());
		this->SetPlayerIntellect(this->GetPlayerIntellect() - this->GetEquippedWeapon()->GetItemBonusIntellect());
		this->GetEquippedWeapon()->SetIsEquipped(false);
		unequippedItemName = this->GetEquippedWeapon()->GetItemName();
		this->SetEquippedWeapon(nullptr);
		break;
	case Helmet:
		this->SetPlayerStrength(this->GetPlayerStrength() - this->GetEquippedHelmet()->GetItemBonusStrength());
		this->SetPlayerDexterity(this->GetPlayerDexterity() - this->GetEquippedHelmet()->GetItemBonusDexterity());
		this->SetPlayerIntellect(this->GetPlayerIntellect() - this->GetEquippedHelmet()->GetItemBonusIntellect());
		this->GetEquippedHelmet()->SetIsEquipped(false);
		unequippedItemName = this->GetEquippedHelmet()->GetItemName();
		this->SetEquippedHelmet(nullptr);
		break;
	case Chestplate:
		this->SetPlayerStrength(this->GetPlayerStrength() - this->GetEquippedChestplate()->GetItemBonusStrength());
		this->SetPlayerDexterity(this->GetPlayerDexterity() - this->GetEquippedChestplate()->GetItemBonusDexterity());
		this->SetPlayerIntellect(this->GetPlayerIntellect() - this->GetEquippedChestplate()->GetItemBonusIntellect());
		this->GetEquippedChestplate()->SetIsEquipped(false);
		unequippedItemName = this->GetEquippedChestplate()->GetItemName();
		this->SetEquippedChestplate(nullptr);
		break;
	case Leggings:
		this->SetPlayerStrength(this->GetPlayerStrength() - this->GetEquippedLeggings()->GetItemBonusStrength());
		this->SetPlayerDexterity(this->GetPlayerDexterity() - this->GetEquippedLeggings()->GetItemBonusDexterity());
		this->SetPlayerIntellect(this->GetPlayerIntellect() - this->GetEquippedLeggings()->GetItemBonusIntellect());
		this->GetEquippedLeggings()->SetIsEquipped(false);
		unequippedItemName = this->GetEquippedLeggings()->GetItemName();
		this->SetEquippedLeggings(nullptr);
		break;
	case UndefinedItemClass:
		break;
	}
	return "You unequipped " + unequippedItemName;
}

std::tuple<std::string, bool> Player::PurchaseItem(Item item)
{
	if (item.GetItemPrice() > this->Gold)
		return { "Not enough money", false };
	this->InsertIntoInventory(item);
	return { item.GetItemName() + " purchased", true };
}

std::string Player::LootItem(Item item)
{
	this->InsertIntoInventory(item);
	return item.GetItemName() + " looted";
}