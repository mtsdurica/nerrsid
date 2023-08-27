#include "Entity.h"

Entity::Entity(std::string name, int gold, int itemsInInventory, int maximumItemsInInventory, int positionXCoordinate, int positionYCoordinate)
	: name(std::move(name)), gold(gold), itemsInInventory(itemsInInventory), maximumItemsInInventory(maximumItemsInInventory), positionXCoordinate(positionXCoordinate), positionYCoordinate(positionYCoordinate)
{
}

Entity::~Entity() = default;

std::string Entity::GetName() const
{
	return this->name;
}

int Entity::GetGold() const
{
	return this->gold;
}

std::vector<Item>* Entity::GetInventory()
{
	return &this->inventory;
}

int Entity::GetItemsInInventory() const
{
	return this->itemsInInventory;
}

int Entity::GetMaximumItemsInInventory() const
{
	return this->maximumItemsInInventory;
}

int Entity::GetPositionXCoordinate() const
{
	return this->positionXCoordinate;
}

int Entity::GetPositionYCoordinate() const
{
	return this->positionYCoordinate;
}

void Entity::SetName(const std::string& name)
{
	this->name = name;
}

void Entity::SetGold(int gold)
{
	this->gold = gold;
}

bool Entity::InsertIntoInventory(Item item)
{
	if (this->itemsInInventory < this->maximumItemsInInventory)
	{
		this->itemsInInventory++;
		this->inventory.push_back(item);
		return true;
	}
	return false;
}

void Entity::SetItemsInInventory(int itemsInInventory)
{
	this->itemsInInventory = itemsInInventory;
}

void Entity::SetPositionXCoordinate(int positionXCoordinate)
{
	this->positionXCoordinate = positionXCoordinate;
}

void Entity::SetPositionYCoordinate(int positionYCoordinate)
{
	this->positionYCoordinate = positionYCoordinate;
}