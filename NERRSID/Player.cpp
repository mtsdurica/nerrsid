#include "Player.h"
#include "Map.h"
#include "UI.h"

Player::Player(std::string playerName, playerClass_t playerClass)
	: playerName(std::move(playerName)), playerClass(playerClass), playerLevel(1), playerExperience(0), playerGold(0),
	playerItemsInInventory(0), playerPosX(1), playerPosY(1)
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
	return playerName;
}
playerClass_t Player::GetPlayerClass() const
{
	return playerClass;
}
int Player::GetPlayerLevel() const
{
	return playerLevel;
}
int Player::GetPlayerExperience() const
{
	return playerExperience;
}
int Player::GetPlayerGold() const
{
	return playerGold;
}
int Player::GetPlayerStrength() const
{
	return playerStrength;
}
int Player::GetPlayerDexterity() const
{
	return playerDexterity;
}
int Player::GetPlayerIntellect() const
{
	return playerIntellect;
}
int Player::GetPlayerItemsInInventory() const
{
	return playerItemsInInventory;
}
int Player::GetPlayerPosX() const
{
	return playerPosX;
}
int Player::GetPlayerPosY() const
{
	return playerPosY;
}
void Player::SetPlayerName(const std::string& playerName)
{
	Player::playerName = playerName;
}
void Player::SetPlayerClass(playerClass_t playerClass)
{
	Player::playerClass = playerClass;
}
void Player::SetPlayerLevel(int playerLevel)
{
	Player::playerLevel = playerLevel;
}
void Player::SetPlayerExperience(int playerExperience)
{
	Player::playerExperience = playerExperience;
}
void Player::SetPlayerGold(int playerGold)
{
	Player::playerGold = playerGold;
}
void Player::SetPlayerStrength(int playerStrength)
{
	Player::playerStrength = playerStrength;
}
void Player::SetPlayerDexterity(int playerDexterity)
{
	Player::playerDexterity = playerDexterity;
}
void Player::SetPlayerIntellect(int playerIntellect)
{
	Player::playerIntellect = playerIntellect;
}
void Player::SetPlayerItemsInInventory(int playerItemsInInventory)
{
	Player::playerItemsInInventory = playerItemsInInventory;
}
void Player::SetPlayerPosX(int playerPosX)
{
	Player::playerPosX = playerPosX;
}
void Player::SetPlayerPosY(int playerPosY)
{
	Player::playerPosY = playerPosY;
}