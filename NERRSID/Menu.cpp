#include "Menu.h"

Menu::Menu(const int allItems) : DisplayedItems(10), AllItems(allItems), SelectedItem(0), StartingItem(0),
EndingItem(DisplayedItems)
{
}

Menu::~Menu() = default;

void Menu::ScrollDown()
{
	if (this->SelectedItem < this->AllItems - 1)
		this->SelectedItem++;
	if (this->SelectedItem == this->EndingItem)
	{
		this->StartingItem += this->DisplayedItems;
		if ((this->AllItems - this->StartingItem) < this->DisplayedItems)
			this->EndingItem = AllItems;
		else
			this->EndingItem += this->DisplayedItems;
	}
}

void Menu::ScrollUp()
{
	if (this->SelectedItem > 0)
		this->SelectedItem--;
	if ((this->SelectedItem == this->StartingItem - 1) && (this->SelectedItem != 0))
	{
		this->EndingItem -= this->EndingItem - this->StartingItem;
		this->StartingItem -= this->DisplayedItems;
	}
}

int Menu::GetSelectedItem() const
{
	return this->SelectedItem;
}

int Menu::GetStartingItem() const
{
	return this->StartingItem;
}

int Menu::GetEndingItem() const
{
	return this->EndingItem;
}

void Menu::SetSelectedItem(const int selectedItem)
{
	this->SelectedItem = selectedItem;
}

void Menu::SetAllItems()
{
	this->AllItems--;
}
