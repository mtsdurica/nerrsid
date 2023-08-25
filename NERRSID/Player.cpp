#include "Player.h"
#include "Map.h"

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
const std::string& Player::GetPlayerName() const
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
void Player::SetPlayerName(const std::string& newPlayerName)
{
	Player::playerName = newPlayerName;
}
void Player::SetPlayerClass(playerClass_t newPlayerClass)
{
	Player::playerClass = newPlayerClass;
}
void Player::SetPlayerLevel(int newPlayerLevel)
{
	Player::playerLevel = newPlayerLevel;
}
void Player::SetPlayerExperience(int newPlayerExperience)
{
	Player::playerExperience = newPlayerExperience;
}
void Player::SetPlayerGold(int newPlayerGold)
{
	Player::playerGold = newPlayerGold;
}
void Player::SetPlayerStrength(int newPlayerStrength)
{
	Player::playerStrength = newPlayerStrength;
}
void Player::SetPlayerDexterity(int newPlayerDexterity)
{
	Player::playerDexterity = newPlayerDexterity;
}
void Player::SetPlayerIntellect(int newPlayerIntellect)
{
	Player::playerIntellect = newPlayerIntellect;
}
void Player::SetPlayerItemsInInventory(int newPlayerItemsInInventory)
{
	Player::playerItemsInInventory = newPlayerItemsInInventory;
}
void Player::SetPlayerPosX(int newPlayerPosX)
{
	Player::playerPosX = newPlayerPosX;
}
void Player::SetPlayerPosY(int newPlayerPosY)
{
	Player::playerPosY = newPlayerPosY;
}

void Player::KeyPressHandler(SDL_Event eventToBeHandled, Map map)
{
	auto mapTiles = map.getMapTiles();

	switch (eventToBeHandled.key.keysym.sym)
	{
	case SDLK_UP:
		if (mapTiles[playerPosX][playerPosY - 1] == Walkable)
			playerPosY--;
		break;
	case SDLK_DOWN:
		if (mapTiles[playerPosX][playerPosY + 1] == Walkable)
			playerPosY++;
		break;
	case SDLK_LEFT:
		if (mapTiles[playerPosX - 1][playerPosY] == Walkable)
			playerPosX--;
		break;
	case SDLK_RIGHT:
		if (mapTiles[playerPosX + 1][playerPosY] == Walkable)
			playerPosX++;
		break;
	}
}



