#pragma once
#include <string>
#include <SDL.h>

#include "Map.h"
#include "Event.h"

typedef enum playerClass
{
	Wizard, Warrior, Assassin
} playerClass_t;

class Player
{
private:
	std::string playerName;
	playerClass_t playerClass;
	int playerLevel;
	int playerExperience;
	int playerGold;
	int playerStrength;
	int playerDexterity;
	int playerIntellect;
	// TODO: inventory stuff
	int playerItemsInInventory;
	int playerPosX;
	int playerPosY;

public:
	Player(std::string playerName, playerClass_t playerClass);
	~Player();
	std::string GetPlayerName() const;
	playerClass_t GetPlayerClass() const;
	int GetPlayerLevel() const;
	int GetPlayerExperience() const;
	int GetPlayerGold() const;
	int GetPlayerStrength() const;
	int GetPlayerDexterity() const;
	int GetPlayerIntellect() const;
	int GetPlayerItemsInInventory() const;
	int GetPlayerPosX() const;
	int GetPlayerPosY() const;
	void SetPlayerName(const std::string& playerName);
	void SetPlayerClass(playerClass_t playerClass);
	void SetPlayerLevel(int playerLevel);
	void SetPlayerExperience(int playerExperience);
	void SetPlayerGold(int playerGold);
	void SetPlayerStrength(int playerStrength);
	void SetPlayerDexterity(int playerDexterity);
	void SetPlayerIntellect(int playerIntellect);
	void SetPlayerItemsInInventory(int playerItemsInInventory);
	void SetPlayerPosX(int playerPosX);
	void SetPlayerPosY(int playerPosY);
};

