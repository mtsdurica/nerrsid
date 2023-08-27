#include "Menu.h"

Menu::Menu(int allItems) : allItems(allItems), selectedItem(0), displayedItems(3), endingItem(displayedItems), startingItem(0)
{
}

Menu::~Menu() = default;

void Menu::ScrollDown()
{
	if (this->selectedItem < this->allItems - 1)
		this->selectedItem++;
	if (this->selectedItem == this->endingItem)
	{
		this->startingItem += this->displayedItems;
		if ((this->allItems - this->startingItem) < this->displayedItems)
			this->endingItem = allItems;
		else
			this->endingItem += this->displayedItems;
	}
}

void Menu::ScrollUp()
{
	if (this->selectedItem > 0)
		this->selectedItem--;
	if ((this->selectedItem == this->startingItem - 1) && (this->selectedItem != 0))
	{
		this->endingItem -= this->endingItem - this->startingItem;
		this->startingItem -= this->displayedItems;
	}
}

int Menu::GetSelectedItem() const
{
	return this->selectedItem;
}

int Menu::GetStartingItem() const
{
	return this->startingItem;
}

int Menu::GetEndingItem() const
{
	return this->endingItem;
}
