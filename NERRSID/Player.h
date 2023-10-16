#pragma once

#include <string>
#include <tuple>

#include "Item.h"
#include "Entity.h"

typedef enum playerClass
{
	UndefinedPlayerClass = -1,
	Wizard,
	Warrior,
	Assassin
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
	Player();
	Player(std::string playerName, playerClass_t playerClass, int positionXCoordinate, int positionYCoordinate);
	~Player();
	playerClass_t GetPlayerClass() const;
	int GetPlayerLevel() const;
	int GetPlayerExperience() const;
	int GetPlayerStrength() const;
	int GetPlayerDexterity() const;
	int GetPlayerIntellect() const;
	Item* GetEquippedWeapon();
	Item* GetEquippedHelmet();
	Item* GetEquippedChestplate();
	Item* GetEquippedLeggings();
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
	std::string EquipItem(Item* item);
	std::string UnequipItem(itemClass_t itemClass);
	std::tuple<std::string, bool> PurchaseItem(Item item);
};

