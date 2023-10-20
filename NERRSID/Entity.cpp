#include "Entity.h"

Entity::Entity() : Gold(-1), ItemsInInventory(-1), MaximumItemsInInventory(-1), PositionXCoordinate(-1), PositionYCoordinate(-1), IdleStatus(false)
{
}

Entity::Entity(std::string name, const int gold, const int itemsInInventory, const int maximumItemsInInventory, const int positionXCoordinate, const int positionYCoordinate)
	: Name(std::move(name)), Gold(gold), ItemsInInventory(itemsInInventory), MaximumItemsInInventory(maximumItemsInInventory), PositionXCoordinate(positionXCoordinate),
	PositionYCoordinate(positionYCoordinate), IdleStatus(true)
{
}

Entity::~Entity() = default;

std::string Entity::GetName() const
{
	return this->Name;
}

int Entity::GetGold() const
{
	return this->Gold;
}

std::array<Item, 50>* Entity::GetInventory()
{
	return &this->Inventory;
}

int Entity::GetItemsInInventory() const
{
	return this->ItemsInInventory;
}

int Entity::GetMaximumItemsInInventory() const
{
	return this->MaximumItemsInInventory;
}

int Entity::GetPositionXCoordinate() const
{
	return this->PositionXCoordinate;
}

int Entity::GetPositionYCoordinate() const
{
	return this->PositionYCoordinate;
}

bool Entity::GetIdleStatus() const
{
	return this->IdleStatus;
}

void Entity::SetName(const std::string& name)
{
	this->Name = name;
}

void Entity::SetGold(const int gold)
{
	this->Gold = gold;
}

bool Entity::InsertIntoInventory(const Item& item)
{
	if (this->ItemsInInventory < this->MaximumItemsInInventory)
	{
		this->Inventory.at(this->ItemsInInventory) = item;
		this->ItemsInInventory++;
		return true;
	}
	return false;
}

void Entity::SetItemsInInventory(const int itemsInInventory)
{
	this->ItemsInInventory = itemsInInventory;
}

void Entity::SetPositionXCoordinate(const int positionXCoordinate)
{
	this->PositionXCoordinate = positionXCoordinate;
}

void Entity::SetPositionYCoordinate(const int positionYCoordinate)
{
	this->PositionYCoordinate = positionYCoordinate;
}

void Entity::SetIdleStatus(const bool idleStatus)
{
	this->IdleStatus = idleStatus;
}
