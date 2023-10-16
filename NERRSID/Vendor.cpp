#include <rapidjson/filereadstream.h>
#include <rapidjson/document.h>
#include <iostream>

#include "Vendor.h"
#include "Map.h"

Vendor::Vendor() : Entity("", 0, 0, 0, 0, 0)
{
}

Vendor::Vendor(std::string vendorName, int positionXCoordinate, int positionYCoordinate)
	: Entity(vendorName, 0, 0, 5, positionXCoordinate, positionYCoordinate)
{
}

Vendor::~Vendor() = default;

/// TODO: Move to separate inventory class so it could be used for player as well
void Vendor::RemoveItemFromInventory(int selectedItem)
{
	for (int i = selectedItem; i < this->itemsInInventory; i++)
	{
		this->inventory.at(i) = this->inventory.at(i + 1);
	}
	this->itemsInInventory--;
}

int Vendor::RandomInRange(int min, int max)
{
	return (rand() % (max + 1 - min) + min);
}

bool Vendor::CreateInventory()
{
	std::array<Item, 5> itemShuffleBag;

	FILE* fp;
	fopen_s(&fp, "./itemset.json", "rb");

	char readBuffer[65536];
	rapidjson::FileReadStream inputStream(fp, readBuffer, sizeof(readBuffer));
	rapidjson::Document document;

	document.ParseStream(inputStream);
	if (document.HasParseError())
	{
		std::cerr << "Error: JSON parsing failure" << std::endl;
		fclose(fp);
		return false;
	}
	fclose(fp);

	if (document.HasMember("itemList") && document["itemList"].IsArray())
	{
		const rapidjson::Value& itemList = document["itemList"];
		for (rapidjson::SizeType i = 0; i < itemList.Size(); i++)
		{
			std::string itemName = "";
			int itemPrice = 0, itemBonusStrength = 0, itemBonusDexterity = 0, itemBonusIntellect = 0;
			itemClass_t itemClass = Weapon;
			if (itemList[i].HasMember("itemName")
				&& itemList[i].HasMember("itemType")
				&& itemList[i].HasMember("itemPrice")
				&& itemList[i].HasMember("itemBonusStrength")
				&& itemList[i].HasMember("itemBonusDexterity")
				&& itemList[i].HasMember("itemBonusIntellect"))
			{

				itemName = itemList[i]["itemName"].GetString();
				switch (itemList[i]["itemType"].GetInt())
				{
				case 0:
					itemClass = Weapon;
					break;
				case 1:
					itemClass = Helmet;
					break;
				case 2:
					itemClass = Chestplate;
					break;
				case 3:
					itemClass = Leggings;
					break;
				}
				itemPrice = itemList[i]["itemPrice"].GetInt();
				itemBonusStrength = itemList[i]["itemBonusStrength"].GetInt();
				itemBonusDexterity = itemList[i]["itemBonusDexterity"].GetInt();
				itemBonusIntellect = itemList[i]["itemBonusIntellect"].GetInt();
			}
			else return false;
			Item item(itemName, itemClass, itemPrice, itemBonusStrength, itemBonusDexterity, itemBonusIntellect);
			itemShuffleBag[i] = item;
		}
	}

	this->itemsInInventory = Vendor::RandomInRange(1, 5);
	for (int i = 0; i < this->itemsInInventory; i++)
	{
		int selectedItem = Vendor::RandomInRange(0, 4);
		this->inventory.at(i) = itemShuffleBag.at(selectedItem);
	}

	return true;
}
