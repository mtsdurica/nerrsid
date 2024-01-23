#pragma once
#include <string>
#include <array>

#include "Item.h"

class Entity abstract
{
protected:
	std::string Name;
	int Gold;
	std::array<Item, 50> Inventory;
	int ItemsInInventory;
	int MaximumItemsInInventory;
	int PositionXCoordinate;
	int PositionYCoordinate;
	bool IdleStatus;
public:
	Entity();
	Entity(std::string name, int gold, int itemsInInventory, int maximumItemsInInventory, int positionXCoordinate, int positionYCoordinate);
	Entity(int gold, int itemsInInventory, int maximumItemsInInventory, int positionXCoordinate, int positionYCoordinate);
	virtual ~Entity();
	/// <summary>
	/// Get entity name
	/// </summary>
	/// <returns>Entity name</returns>
	std::string GetName() const;
	/// <summary>
	/// Get entity gold
	/// </summary>
	/// <returns>Entity gold</returns>
	int GetGold() const;
	/// <summary>
	/// Get entity inventory
	/// </summary>
	/// <returns>Pointer to entity inventory</returns>
	std::array<Item, 50>* GetInventory();
	/// <summary>
	/// Get current number of items in entity inventory
	/// </summary>
	/// <returns>Current number of items in entity inventory</returns>
	int GetItemsInInventory() const;
	/// <summary>
	/// Get maximum number of items in entity inventory
	/// </summary>
	/// <returns>Maximum number of items in entity inventory</returns>
	int GetMaximumItemsInInventory() const;
	/// <summary>
	/// Get entity position X axis coordinate
	/// </summary>
	/// <returns>Entity position on X axis</returns>
	int GetPositionXCoordinate() const;
	/// <summary>
	/// Get entity position Y axis coordinate
	/// </summary>
	/// <returns>Entity position on Y axis</returns>
	int GetPositionYCoordinate() const;
	/// <summary>
	///	Get idle status of entity
	/// </summary>
	///<returns>Idle status of entity</returns>
	bool GetIdleStatus() const;
	/// <summary>
	/// Set name of entity 
	/// </summary>
	/// <param name="name">New name</param>
	void SetName(const std::string& name);
	/// <summary>
	/// Set entity gold
	/// </summary>
	/// <param name="gold">New gold value</param>
	void SetGold(const int gold);
	/// <summary>
	/// Set number of items in entity inventory
	/// </summary>
	/// <param name="itemsInInventory">New number of items in inventory</param>
	void SetItemsInInventory(const int itemsInInventory);
	/// <summary>
	/// Set entity position X axis coordinate
	/// </summary>
	/// <param name="positionXCoordinate">New X axis coordinate</param>
	void SetPositionXCoordinate(const int positionXCoordinate);
	/// <summary>
	/// Set entity position Y axis coordinate
	/// </summary>
	/// <param name="positionYCoordinate">New Y axis coordinate</param>
	void SetPositionYCoordinate(const int positionYCoordinate);
	void SetIdleStatus(const bool idleStatus);
	/// <summary>
	/// Insert item into entity inventory
	/// </summary>
	/// <param name="item">Inserted item</param>
	/// <returns>
	/// true if item was inserted; false if item was not inserted, due to inventory being full
	/// </returns>
	bool InsertIntoInventory(const Item& item);
};