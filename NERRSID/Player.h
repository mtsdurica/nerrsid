#pragma once

#include <string>

#include "Item.h"
#include "Entity.h"

typedef enum playerClass
{
	Wizard, Warrior, Assassin
} playerClass_t;

class Player : public Entity
{
private:
	playerClass_t playerClass;
	int playerLevel;
	int playerExperience;
	int playerStrength;
	int playerDexterity;
	int playerIntellect;
	Item* equippedWeapon;
	Item* equippedHelmet;
	Item* equippedChestplate;
	Item* equippedLeggings;

public:
	Player(std::string playerName, playerClass_t playerClass, int positionXCoordinate, int positionYCoordinate);
	~Player();
	playerClass_t GetPlayerClass() const;
	int GetPlayerLevel() const;
	int GetPlayerExperience() const;
	int GetPlayerStrength() const;
	int GetPlayerDexterity() const;
	int GetPlayerIntellect() const;
	Item* GetEquippedWeapon() const;
	Item* GetEquippedHelmet() const;
	Item* GetEquippedChestplate() const;
	Item* GetEquippedLeggings() const;
	void SetPlayerClass(playerClass_t playerClass);
	void SetPlayerLevel(int playerLevel);
	void SetPlayerExperience(int playerExperience);
	void SetPlayerStrength(int playerStrength);
	void SetPlayerDexterity(int playerDexterity);
	void SetPlayerIntellect(int playerIntellect);
	void SetEquippedWeapon(Item* equippedWeapon);
	void SetEquippedHelmet(Item* equippedHelmet);
	void SetEquippedChestplate(Item* equippedChestplate);
	void SetEquippedLeggings(Item* equippedLeggings);
	void SetPositionXCoordinate(int positionXCoordinate);
	void SetPositionYCoordinate(int positionYCoordinate);
};

