#include "Player.h"
#include "Map.h"
#include "UI.h"

Player::Player(std::string playerName, playerClass_t playerClass)
	: playerName(std::move(playerName)), playerClass(playerClass), playerLevel(1), playerExperience(0), playerGold(0),
	playerItemsInInventory(0), playerMaximumItemsInInventory(50), equippedWeapon(nullptr), equippedHelmet(nullptr), equippedChestplate(nullptr), equippedLeggings(nullptr),
	playerPosX(1), playerPosY(1)
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
	}
}
Player::~Player() = default;
std::string Player::GetPlayerName() const
{
	return this->playerName;
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
int Player::GetPlayerGold() const
{
	return this->playerGold;
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
std::vector<Item>* Player::GetPlayerInventory()
{
	return &this->playerInventory;
}
int Player::GetPlayerItemsInInventory() const
{
	return this->playerItemsInInventory;
}
int Player::GetPlayerMaximumItemsInInventory() const
{
	return this->playerMaximumItemsInInventory;
}
Item* Player::GetEquippedWeapon() const
{
	return this->equippedWeapon;
}
Item* Player::GetEquippedHelmet() const
{
	return this->equippedHelmet;
}
Item* Player::GetEquippedChestplate() const
{
	return this->equippedChestplate;
}
Item* Player::GetEquippedLeggings() const
{
	return this->equippedLeggings;
}
int Player::GetPlayerPosX() const
{
	return this->playerPosX;
}
int Player::GetPlayerPosY() const
{
	return this->playerPosY;
}
void Player::SetPlayerName(const std::string& playerName)
{
	this->playerName = playerName;
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
void Player::SetPlayerGold(int playerGold)
{
	this->playerGold = playerGold;
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
bool Player::InsertIntoPlayerInventory(Item item)
{
	if (this->playerItemsInInventory < this->playerMaximumItemsInInventory)
	{
		this->playerItemsInInventory++;
		this->playerInventory.push_back(item);
		return true;
	}
	return false;
}
void Player::SetPlayerItemsInInventory(int playerItemsInInventory)
{
	this->playerItemsInInventory = playerItemsInInventory;
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
void Player::SetPlayerPosX(int playerPosX)
{
	this->playerPosX = playerPosX;
}
void Player::SetPlayerPosY(int playerPosY)
{
	this->playerPosY = playerPosY;
}