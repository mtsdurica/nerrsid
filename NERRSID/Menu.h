#pragma once
class Menu
{
private:
	int DisplayedItems;
	int AllItems;
	int SelectedItem;
	int StartingItem;
	int EndingItem;
public:
	explicit Menu(int allItems);
	~Menu();
	void ScrollDown();
	void ScrollUp();
	int GetSelectedItem() const;
	int GetStartingItem() const;
	int GetEndingItem() const;
	void SetSelectedItem(int selectedItem);
	void SetAllItems();
};

