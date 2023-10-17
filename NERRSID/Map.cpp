#include <cstdlib>

#include "Map.h"

Map::Map() : NumberOfVendors(0), NumberOfChests(0)
{
	for (int x = 0; x < MaxX; x++)
		for (int y = 0; y < MaxY; y++)
			MapTiles[x][y] = WalkableTile;
}

Map::~Map() = default;

void Map::DrawHorizontalWall(const Wall* newWall)
{
	for (UINT_CHANGEABLE x = newWall->Start.X; x <= newWall->End.X; x++)
		MapTiles[x][newWall->Start.Y] = WallTile;
}

void Map::DrawVerticalWall(const Wall* newWall)
{
	for (UINT_CHANGEABLE y = newWall->Start.Y; y <= newWall->End.Y; y++)
		MapTiles[newWall->Start.X][y] = WallTile;
}

Point Map::GetChildCenter(const Room* childRoom)
{
	Point center;
	center.X = childRoom->Top.Start.X + (childRoom->Top.End.X - childRoom->Top.Start.X) / 2;
	center.Y = childRoom->Right.Start.Y + (childRoom->Right.End.Y - childRoom->Right.Start.Y) / 2;
	return center;
}

UINT_CHANGEABLE Map::RandomInRange(const UINT_CHANGEABLE min, const UINT_CHANGEABLE max)
{
	/// Calculate the middle of the range
	const UINT_CHANGEABLE middle = (min + max) / 2;
	/// Calculate the allowable deviation from the middle
	const UINT_CHANGEABLE deviation = (max - min) / 3;
	return static_cast<uint8_t>(rand() % (deviation * 2 + 1)) + (middle - deviation);
}

void Map::GenerateHorizontalSplit(Room* r)
{
	if (r == nullptr)
		return;

	if (r->Left.Start.Y + (PseudoRoomSize / 2) >= r->Left.End.Y - (PseudoRoomSize / 2))
		return;

	const UINT_CHANGEABLE randY = RandomInRange(r->Left.Start.Y + (PseudoRoomSize / 2), r->Left.End.Y - (PseudoRoomSize / 2));

	const Wall newSplit = { { r->Top.Start.X, randY }, { r->Top.End.X, randY } };

	Room child1 =
	{ r->Top, newSplit, { r->Top.Start, newSplit.Start }, { r->Top.End, newSplit.End }, nullptr, nullptr,
	  { 0, 0 } };
	r->Child1 = &child1;

	Room child2 =
	{ newSplit, r->Bot, { newSplit.Start, r->Bot.Start }, { newSplit.End, r->Bot.End }, nullptr, nullptr,
	  { 0, 0 } };
	r->Child2 = &child2;

	DrawHorizontalWall(&newSplit);

	GenerateVerticalSplit(&child1);
	child1.Center = GetChildCenter(&child1);

	GenerateVerticalSplit(&child2);
	child2.Center = GetChildCenter(&child2);
	// Drawing path between two sister rooms
	for (int i = child2.Center.Y; i > child1.Center.Y; i--)
		MapTiles[child2.Center.X][i] = WalkableTile;
}

void Map::GenerateVerticalSplit(Room* r)
{
	if (r == nullptr)
		return;

	if (r->Top.Start.X + PseudoRoomSize >= r->Top.End.X - PseudoRoomSize)
		return;

	const UINT_CHANGEABLE randX = RandomInRange(r->Top.Start.X + PseudoRoomSize, r->Top.End.X - PseudoRoomSize);

	const Wall newSplit = { { randX, r->Top.Start.Y }, { randX, r->Bot.Start.Y } }; // third thingy maybe wrong

	Room child1 =
	{ { r->Top.Start, newSplit.Start }, { r->Bot.Start, newSplit.End }, r->Left, newSplit, nullptr, nullptr,
	 { 0, 0 } };
	r->Child1 = &child1;

	Room child2 =
	{ { newSplit.Start, r->Top.End }, { newSplit.End, r->Bot.End }, newSplit, r->Right, nullptr, nullptr,
	 { 0, 0 } };
	r->Child2 = &child2;

	DrawVerticalWall(&newSplit);

	GenerateHorizontalSplit(&child1);
	child1.Center = GetChildCenter(&child1);

	GenerateHorizontalSplit(&child2);
	child2.Center = GetChildCenter(&child2);
	// Drawing path between two sister rooms
	for (int i = child2.Center.X; i > child1.Center.X; i--)
		MapTiles[i][child2.Center.Y] = WalkableTile;
}

Room Map::InitializeBase()
{
	constexpr Room newRoom =
	{ {{ 0, 0 }, { MaxX - 1, 0 }}, {{ 0, MaxY - 1 }, { MaxX - 1, MaxY - 1 }}, {{ 0, 0 }, { 0, MaxY - 1 }},
	 {{ MaxX - 1, 0 }, { MaxX - 1, MaxY - 1 }}, nullptr, nullptr, { 0, 0 } };
	DrawHorizontalWall(&newRoom.Top);
	DrawHorizontalWall(&newRoom.Bot);
	DrawVerticalWall(&newRoom.Left);
	DrawVerticalWall(&newRoom.Right);
	return newRoom;
}

bool Map::GenerateVendors()
{
	const int numOfGeneratedVendors = Map::RandomInRange(0, 5);
	for (int i = 0; i < numOfGeneratedVendors; i++)
	{
		Vendor vendor;
		if (!vendor.CreateInventory())
			return false;
		do
		{
			vendor.SetPositionXCoordinate(Map::RandomInRange(1, MaxX - 1));
			vendor.SetPositionYCoordinate(Map::RandomInRange(1, MaxY - 1));
		} while (this->MapTiles[vendor.GetPositionXCoordinate()][vendor.GetPositionYCoordinate()] != WalkableTile);
		this->InsertVendor(&vendor);
		this->MapVendors.at(this->NumberOfVendors) = vendor;
		this->NumberOfVendors++;
	}
	return true;
}

bool Map::GenerateChests()
{
	const int numOfGeneratedChests = Map::RandomInRange(0, 2);
	for (int i = 0; i < numOfGeneratedChests; i++)
	{
		Chest chest;
		if (!chest.CreateInventory())
			return false;
		do
		{
			chest.SetPositionXCoordinate(Map::RandomInRange(1, MaxX - 1));
			chest.SetPositionYCoordinate(Map::RandomInRange(1, MaxY - 1));
		} while (this->MapTiles[chest.GetPositionXCoordinate()][chest.GetPositionYCoordinate()] != WalkableTile);
		this->InsertChest(&chest);
		this->MapChests.at(this->NumberOfChests) = chest;
		this->NumberOfChests++;
	}
}

bool Map::GenerateMap()
{
	Room base = InitializeBase();

	if (rand() % 2)
		GenerateVerticalSplit(&base);
	else
		GenerateHorizontalSplit(&base);
	if (!this->GenerateVendors())
		return false;
	if (!this->GenerateChests())
		return false;

	return true;
}

std::array<std::array<Tiles, MaxY>, MaxX>& Map::GetMapTiles()
{
	return this->MapTiles;
}

std::array<Vendor, 5>& Map::GetMapVendors()
{
	return this->MapVendors;
}

std::array<Chest, 2>& Map::GetMapChests()
{
	return this->MapChests;
}

void Map::InsertVendor(const Vendor* newVendor)
{
	this->MapTiles[newVendor->GetPositionXCoordinate()][newVendor->GetPositionYCoordinate()] = VendorTile;
}

void Map::InsertChest(const Chest* newChest)
{
	this->MapTiles[newChest->GetPositionXCoordinate()][newChest->GetPositionYCoordinate()] = ChestTile;
}

Vendor* Map::FindVendor(std::array<Vendor, 5>* mapVendors, const int numberOfVendors, const int playerPositionXCoordinate, const int playerPositionYCoordinate)
{
	for (int i = 0; i < numberOfVendors; i++)
		if (mapVendors->at(i).GetPositionXCoordinate() == playerPositionXCoordinate && mapVendors->at(i).GetPositionYCoordinate() == playerPositionYCoordinate)
			return &(mapVendors->at(i));
	return nullptr;
}

Chest* Map::FindChest(std::array<Chest, 2>* mapChests, const int numberOfChests, const int playerPositionXCoordinate, const int playerPositionYCoordinate)
{
	for (int i = 0; i < numberOfChests; i++)
		if (mapChests->at(i).GetPositionXCoordinate() == playerPositionXCoordinate && mapChests->at(i).GetPositionYCoordinate() == playerPositionYCoordinate)
			return &(mapChests->at(i));
	return nullptr;
}

int Map::GetNumberOfVendors() const
{
	return this->NumberOfVendors;
}
