#include "Player.h"
#include "Map.h"
#include "UI.h"

Player::Player(std::string playerName, playerClass_t playerClass, int positionXCoordinate, int positionYCoordinate)
	: Entity(playerName, 0, 0, 50, positionXCoordinate, positionYCoordinate), playerClass(playerClass), playerLevel(1), playerExperience(0),
	equippedWeapon(nullptr), equippedHelmet(nullptr), equippedChestplate(nullptr), equippedLeggings(nullptr)
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