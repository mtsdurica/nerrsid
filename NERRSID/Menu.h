#pragma once
class Menu
{
private:
	int displayedItems;
	int allItems;
	int selectedItem;
	int startingItem;
	int endingItem;
public:
	Menu(int allItems);
	~Menu();
	void ScrollDown();
	void ScrollUp();
	int GetSelectedItem() const;
	int GetStartingItem() const;
	int GetEndingItem() const;
	void SetSelectedItem(int selectedItem);
	void SetAllItems();
};

