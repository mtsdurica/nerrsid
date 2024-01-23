#pragma once
#include "Entity.h"
class Chest : public Entity
{
public:
	/// <summary>
	/// Construct chest object
	/// </summary>
	Chest();
	/// <summary>
	///	Construct chest object
	/// </summary>
	/// <param name="name">Chest entity name</param>
	/// <param name="positionXCoordinate">Chest entity position X coordinate</param>
	///	<param name="positionYCoordinate">Chest entity position X coordinate</param>
	Chest(const std::string& name, int positionXCoordinate, int positionYCoordinate);
	/// <summary>
	///	Construct chest object
	/// </summary>
	/// <param name="positionXCoordinate">Chest entity position X coordinate</param>
	///	<param name="positionYCoordinate">Chest entity position X coordinate</param>
	Chest(int positionXCoordinate, int positionYCoordinate);
	/// <summary>
	///	Removes item from entity inventory
	/// </summary>
	/// <param name="selectedItem">Index of the wanted item to be deleted</param>
	void RemoveItemFromInventory(int selectedItem);
	/// <summary>
	///	Create entity inventory
	/// </summary>
	/// <returns>True if inventory was created successfully, otherwise false</returns>
	bool CreateInventory();
};

