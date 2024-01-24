#pragma once

#include <string>
#include <tuple>

#include "Item.h"
#include "Entity.h"

typedef enum PlayerClass
{
	UndefinedPlayerClass = -1,
	Wizard,
	Warrior,
	Assassin
} PlayerClassT;

class Player final : public Entity
{
private:
	PlayerClassT PlayerClass;
	int PlayerLevel;
	int PlayerExperience;
	int PlayerStrength;
	int PlayerDexterity;
	int PlayerIntellect;
	int PlayerTurn;
	int PlayerMovesLeft;
	int PlayerVisibilityRange;
	Item* EquippedWeapon;
	Item* EquippedHelmet;
	Item* EquippedChestplate;
	Item* EquippedLeggings;

public:
	Player();
	Player(const std::string& playerName, PlayerClassT playerClass, int positionXCoordinate, int positionYCoordinate);
	PlayerClassT GetPlayerClass() const;
	int GetPlayerLevel() const;
	int GetPlayerExperience() const;
	int GetPlayerStrength() const;
	int GetPlayerDexterity() const;
	int GetPlayerIntellect() const;
	int GetPlayerTurn() const;
	int GetPlayerMovesLeft() const;
	int GetPlayerVisibilityRange() const;
	Item* GetEquippedWeapon() const;
	Item* GetEquippedHelmet() const;
	Item* GetEquippedChestplate() const;
	Item* GetEquippedLeggings() const;
	void SetPlayerClass(PlayerClassT playerClass);
	void SetPlayerLevel(int playerLevel);
	void SetPlayerExperience(int playerExperience);
	void SetPlayerStrength(int playerStrength);
	void SetPlayerDexterity(int playerDexterity);
	void SetPlayerIntellect(int playerIntellect);
	void SetPlayerTurn(int playerTurn);
	void SetPlayerMovesLeft(int playerMovesLeft);
	void SetPlayerVisibilityRange(int playerVisibilityRange);
	void SetEquippedWeapon(Item* equippedWeapon);
	void SetEquippedHelmet(Item* equippedHelmet);
	void SetEquippedChestplate(Item* equippedChestplate);
	void SetEquippedLeggings(Item* equippedLeggings);
	std::string EquipItem(Item* item);
	std::string UnequipItem(ItemClassT itemClass);
	std::tuple<std::string, bool> PurchaseItem(Item item);
	std::string LootItem(Item item);

};

