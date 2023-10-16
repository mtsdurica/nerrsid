#include "Player.h"
#include "Map.h"
#include "UI.h"


Player::Player() : Entity(), playerClass(UndefinedPlayerClass), playerLevel(1),
playerExperience(-1), playerStrength(-1), playerDexterity(-1), playerIntellect(-1), equippedWeapon(nullptr),
equippedHelmet(nullptr), equippedChestplate(nullptr), equippedLeggings(nullptr)
{
}

Player::Player(std::string playerName, playerClass_t playerClass, int positionXCoordinate, int positionYCoordinate)
	: Entity(playerName, 0, 0, 50, positionXCoordinate, positionYCoordinate), playerClass(playerClass), playerLevel(1),
	playerExperience(0), playerStrength(0), playerDexterity(0), playerIntellect(0), equippedWeapon(nullptr),
	equippedHelmet(nullptr), equippedChestplate(nullptr), equippedLeggings(nullptr)
{
	switch (playerClass)
	{
	case Warrior:
		playerStrength = 10;
		playerDexterity = 5;
		playerIntellect = 0;
		break;
	case Wizard:
		playerStrength = 0;
		playerDexterity = 5;
		playerIntellect = 10;
		break;
	case Assassin:
		playerStrength = 5;
		playerDexterity = 10;
		playerIntellect = 0;
		break;
	default:
		playerStrength = -1;
		playerDexterity = -1;
		playerIntellect = -1;
		break;
	}
}

Player::~Player()
{
}

playerClass_t Player::GetPlayerClass() const
{
	return this->playerClass;
}

int Player::GetPlayerLevel() const
{
	return this->playerLevel;
}

int Player::GetPlayerExperience() const
{
	return this->playerExperience;
}

int Player::GetPlayerStrength() const
{
	return this->playerStrength;
}

int Player::GetPlayerDexterity() const
{
	return this->playerDexterity;
}

int Player::GetPlayerIntellect() const
{
	return this->playerIntellect;
}

Item* Player::GetEquippedWeapon()
{
	return this->equippedWeapon;
}

Item* Player::GetEquippedHelmet()
{
	return this->equippedHelmet;
}

Item* Player::GetEquippedChestplate()
{
	return this->equippedChestplate;
}

Item* Player::GetEquippedLeggings()
{
	return this->equippedLeggings;
}

void Player::SetPlayerClass(playerClass_t playerClass)
{
	this->playerClass = playerClass;
}

void Player::SetPlayerLevel(int playerLevel)
{
	this->playerLevel = playerLevel;
}

void Player::SetPlayerExperience(int playerExperience)
{
	this->playerExperience = playerExperience;
}

void Player::SetPlayerStrength(int playerStrength)
{
	this->playerStrength = playerStrength;
}

void Player::SetPlayerDexterity(int playerDexterity)
{
	this->playerDexterity = playerDexterity;
}

void Player::SetPlayerIntellect(int playerIntellect)
{
	this->playerIntellect = playerIntellect;
}

void Player::SetEquippedWeapon(Item* equippedWeapon)
{
	this->equippedWeapon = equippedWeapon;
}

void Player::SetEquippedHelmet(Item* equippedHelmet)
{
	this->equippedHelmet = equippedHelmet;
}

void Player::SetEquippedChestplate(Item* equippedChestplate)
{
	this->equippedChestplate = equippedChestplate;
}

void Player::SetEquippedLeggings(Item* equippedLeggings)
{
	this->equippedLeggings = equippedLeggings;
}

void Player::SetPositionXCoordinate(int positionXCoordinate)
{
	this->positionXCoordinate = positionXCoordinate;
}

void Player::SetPositionYCoordinate(int positionYCoordinate)
{
	this->positionYCoordinate = positionYCoordinate;
}

std::string Player::EquipItem(Item* item)
{
	switch (item->GetItemClass())
	{
	case Weapon:
		if (this->GetEquippedWeapon())
			this->UnequipItem(Weapon);
		this->equippedWeapon = item;
		this->SetPlayerStrength(this->GetPlayerStrength() + this->equippedWeapon->GetItemBonusStrength());
		this->SetPlayerDexterity(this->GetPlayerDexterity() + this->equippedWeapon->GetItemBonusDexterity());
		this->SetPlayerIntellect(this->GetPlayerIntellect() + this->equippedWeapon->GetItemBonusIntellect());
		break;
	case Helmet:
		if (this->GetEquippedHelmet())
			this->UnequipItem(Helmet);
		this->equippedHelmet = item;
		this->SetPlayerStrength(this->GetPlayerStrength() + this->equippedHelmet->GetItemBonusStrength());
		this->SetPlayerDexterity(this->GetPlayerDexterity() + this->equippedHelmet->GetItemBonusDexterity());
		this->SetPlayerIntellect(this->GetPlayerIntellect() + this->equippedHelmet->GetItemBonusIntellect());
		break;
	case Chestplate:
		if (this->GetEquippedChestplate())
			this->UnequipItem(Chestplate);
		this->equippedChestplate = item;
		this->SetPlayerStrength(this->GetPlayerStrength() + this->equippedChestplate->GetItemBonusStrength());
		this->SetPlayerDexterity(this->GetPlayerDexterity() + this->equippedChestplate->GetItemBonusDexterity());
		this->SetPlayerIntellect(this->GetPlayerIntellect() + this->equippedChestplate->GetItemBonusIntellect());
		break;
	case Leggings:
		if (this->GetEquippedLeggings())
			this->UnequipItem(Leggings);
		this->equippedLeggings = item;
		this->SetPlayerStrength(this->GetPlayerStrength() + this->equippedLeggings->GetItemBonusStrength());
		this->SetPlayerDexterity(this->GetPlayerDexterity() + this->equippedLeggings->GetItemBonusDexterity());
		this->SetPlayerIntellect(this->GetPlayerIntellect() + this->equippedLeggings->GetItemBonusIntellect());
		break;
	}
	item->SetIsEquipped(true);

	return "You equipped " + item->GetItemName();
}

std::string Player::UnequipItem(itemClass_t itemClass)
{
	std::string unequippedItemName = "";
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
	}
	return "You unequipped " + unequippedItemName;
}

std::tuple<std::string, bool> Player::PurchaseItem(Item item)
{
	if (item.GetItemPrice() > this->gold)
		return { "Not enough money", false };
	this->InsertIntoInventory(item);
	return { item.GetItemName() + " purchased", true };
}