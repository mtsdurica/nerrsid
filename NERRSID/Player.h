#pragma once
#include <string>
#include <SDL.h>
#include "Map.h"

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
	virtual ~Player();
	const std::string& GetPlayerName() const;
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
	void SetPlayerName(const std::string& newPlayerName);
	void SetPlayerClass(playerClass_t newPlayerClass);
	void SetPlayerLevel(int newPlayerLevel);
	void SetPlayerExperience(int newPlayerExperience);
	void SetPlayerGold(int newPlayerGold);
	void SetPlayerStrength(int newPlayerStrength);
	void SetPlayerDexterity(int newPlayerDexterity);
	void SetPlayerIntellect(int newPlayerIntellect);
	void SetPlayerItemsInInventory(int newPlayerItemsInInventory);
	void SetPlayerPosX(int newPlayerPosX);
	void SetPlayerPosY(int newPlayerPosY);
	void KeyPressHandler(SDL_Event, Map map);

};

