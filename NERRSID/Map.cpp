#include "Map.h"

Map::Map() : NumberOfVendors(0), NumberOfChests(0), NumberOfEnemies(0), NumberOfCorpses(0)
{
	for (int x = 0; x < Util::MAX_X; x++)
		for (int y = 0; y < Util::MAX_Y; y++)
			MapTiles[x][y] = Util::WalkableTile;
}

Map::~Map() = default;

void Map::DrawHorizontalWall(const Util::Wall* newWall)
{
	for (int x = newWall->Start.X; x <= newWall->End.X; x++)
		MapTiles[x][newWall->Start.Y] = Util::WallTile;
}

void Map::DrawVerticalWall(const Util::Wall* newWall)
{
	for (int y = newWall->Start.Y; y <= newWall->End.Y; y++)
		MapTiles[newWall->Start.X][y] = Util::WallTile;
}

Util::Point Map::GetChildCenter(const Util::Room* childRoom)
{
	Util::Point center;
	center.X = childRoom->Top.Start.X + (childRoom->Top.End.X - childRoom->Top.Start.X) / 2;
	center.Y = childRoom->Right.Start.Y + (childRoom->Right.End.Y - childRoom->Right.Start.Y) / 2;
	return center;
}

void Map::GenerateHorizontalSplit(Util::Room* r)
{
	if (r == nullptr)
		return;

	if (r->Left.Start.Y + (Util::PSEUDO_ROOM_SIZE / 2) >= r->Left.End.Y - (Util::PSEUDO_ROOM_SIZE / 2))
		return;

	const int randY = Util::RandomChangeableIntInRange(r->Left.Start.Y + (Util::PSEUDO_ROOM_SIZE / 2), r->Left.End.Y - (Util::PSEUDO_ROOM_SIZE / 2));

	const Util::Wall newSplit = { Util::Point(r->Top.Start.X, randY), Util::Point(r->Top.End.X, randY) };

	Util::Room child1 =
	{ r->Top, newSplit, {r->Top.Start, newSplit.Start}, {r->Top.End, newSplit.End}, nullptr, nullptr, {0, 0} };
	r->Child1 = &child1;

	Util::Room child2 =
	{ newSplit, r->Bot, {newSplit.Start, r->Bot.Start}, {newSplit.End, r->Bot.End}, nullptr, nullptr, {0, 0} };
	r->Child2 = &child2;

	DrawHorizontalWall(&newSplit);

	GenerateVerticalSplit(&child1);
	child1.Center = GetChildCenter(&child1);

	GenerateVerticalSplit(&child2);
	child2.Center = GetChildCenter(&child2);
	// Drawing path between two sister rooms
	for (int i = child2.Center.Y; i > child1.Center.Y; i--)
		MapTiles[child2.Center.X][i] = Util::WalkableTile;
}

void Map::GenerateVerticalSplit(Util::Room* r)
{
	if (r == nullptr)
		return;

	if (r->Top.Start.X + Util::PSEUDO_ROOM_SIZE >= r->Top.End.X - Util::PSEUDO_ROOM_SIZE)
		return;

	const int randX = Util::RandomChangeableIntInRange(r->Top.Start.X + Util::PSEUDO_ROOM_SIZE, r->Top.End.X - Util::PSEUDO_ROOM_SIZE);

	const Util::Wall newSplit = { Util::Point(randX, r->Top.Start.Y), Util::Point(randX, r->Bot.Start.Y) }; // third thingy maybe wrong

	Util::Room child1 =
	{ {r->Top.Start, newSplit.Start}, {r->Bot.Start, newSplit.End}, r->Left, newSplit, nullptr, nullptr, {0, 0} };
	r->Child1 = &child1;

	Util::Room child2 =
	{ {newSplit.Start, r->Top.End}, {newSplit.End, r->Bot.End}, newSplit, r->Right, nullptr, nullptr, {0, 0} };
	r->Child2 = &child2;

	DrawVerticalWall(&newSplit);

	GenerateHorizontalSplit(&child1);
	child1.Center = GetChildCenter(&child1);

	GenerateHorizontalSplit(&child2);
	child2.Center = GetChildCenter(&child2);
	// Drawing path between two sister rooms
	for (int i = child2.Center.X; i > child1.Center.X; i--)
		MapTiles[i][child2.Center.Y] = Util::WalkableTile;
}

Util::Room Map::InitializeBase()
{
	const Util::Room newRoom =
	{
		{Util::Point(0, 0), Util::Point(Util::MAX_X - 1, 0)},
		{Util::Point(0, Util::MAX_Y - 1), Util::Point(Util::MAX_X - 1, Util::MAX_Y - 1)},
		{Util::Point(0, 0), Util::Point(0, Util::MAX_Y - 1)},
		{Util::Point(Util::MAX_X - 1, 0), Util::Point(Util::MAX_X - 1, Util::MAX_Y - 1)},
		nullptr,
		nullptr,
		Util::Point(0, 0)
	};
	DrawHorizontalWall(&newRoom.Top);
	DrawHorizontalWall(&newRoom.Bot);
	DrawVerticalWall(&newRoom.Left);
	DrawVerticalWall(&newRoom.Right);
	return newRoom;
}

bool Map::GenerateVendors()
{
	const int numOfGeneratedVendors = Util::RandomChangeableIntInRange(0, 5);
	for (int i = 0; i < numOfGeneratedVendors; i++)
	{
		Vendor vendor;
		if (!vendor.CreateInventory())
			return false;
		do
		{
			vendor.SetPositionXCoordinate(Util::RandomChangeableIntInRange(1, Util::MAX_X - 1));
			vendor.SetPositionYCoordinate(Util::RandomChangeableIntInRange(1, Util::MAX_Y - 1));
		} while (this->MapTiles[vendor.GetPositionXCoordinate()][vendor.GetPositionYCoordinate()] != Util::WalkableTile);
		vendor.SetName("Joseph"); // TODO: Generating names randomly
		this->InsertVendor(&vendor);
		this->MapVendors.at(this->NumberOfVendors) = vendor;
		this->NumberOfVendors++;
	}
	return true;
}

bool Map::GenerateChests()
{
	const int numOfGeneratedChests = Util::RandomChangeableIntInRange(0, 2);
	for (int i = 0; i < numOfGeneratedChests; i++)
	{
		Chest chest;
		if (!chest.CreateInventory())
			return false;
		do
		{
			chest.SetPositionXCoordinate(Util::RandomChangeableIntInRange(1, Util::MAX_X - 1));
			chest.SetPositionYCoordinate(Util::RandomChangeableIntInRange(1, Util::MAX_Y - 1));
		} while (this->MapTiles[chest.GetPositionXCoordinate()][chest.GetPositionYCoordinate()] != Util::WalkableTile);
		this->InsertChest(&chest);
		this->MapChests.push_back(chest);
		this->NumberOfChests++;
	}
	return true;
}

bool Map::GenerateEnemies()
{
	const int numOfGeneratedEnemies = Util::RandomChangeableIntInRange(0, 5);
	for (int i = 0; i < numOfGeneratedEnemies; i++)
	{
		Enemy enemy;
		do
		{
			enemy.SetPositionXCoordinate(Util::RandomChangeableIntInRange(1, Util::MAX_X - 1));
			enemy.SetPositionYCoordinate(Util::RandomChangeableIntInRange(1, Util::MAX_Y - 1));
		} while (this->MapTiles[enemy.GetPositionXCoordinate()][enemy.GetPositionYCoordinate()] != Util::WalkableTile);
		this->InsertEnemy(&enemy);
		this->MapEnemies.push_back(enemy);
		this->NumberOfEnemies++;
	}
	return true;
}

void Map::AddCorpse(const Corpse* corpse)
{
	this->MapCorpses.push_back(*corpse);
	this->NumberOfCorpses = this->NumberOfCorpses + 1;
}

void Map::GenerateStairs()
{
	int stairsXCoordinate;
	int stairsYCoordinate;
	do
	{
		stairsXCoordinate = Util::RandomChangeableIntInRange(1, Util::MAX_X - 1);
		stairsYCoordinate = Util::RandomChangeableIntInRange(1, Util::MAX_Y - 1);
	} while (this->MapTiles[stairsXCoordinate][stairsYCoordinate] != Util::WalkableTile);

	this->MapTiles[stairsXCoordinate][stairsYCoordinate] = Util::StairsTile;
}

bool Map::GenerateMap()
{
	Util::Room base = InitializeBase();

	if (Util::RandomChangeableIntInRange(0, 1))
		GenerateVerticalSplit(&base);
	else
		GenerateHorizontalSplit(&base);
	GenerateStairs();
	if (!this->GenerateVendors())
		return false;
	if (!this->GenerateChests())
		return false;
	if (!this->GenerateEnemies())
		return false;

	return true;
}

std::array<std::array<Util::Tiles, Util::MAX_Y>, Util::MAX_X>& Map::GetMapTiles()
{
	return this->MapTiles;
}

void Map::InsertChest(const Chest* newChest)
{
	this->MapTiles[newChest->GetPositionXCoordinate()][newChest->GetPositionYCoordinate()] = Util::ChestTile;
}

void Map::InsertVendor(const Vendor* newVendor)
{
	this->MapTiles[newVendor->GetPositionXCoordinate()][newVendor->GetPositionYCoordinate()] = Util::VendorTile;
}

void Map::InsertEnemy(const Enemy* newEnemy)
{
	this->MapTiles[newEnemy->GetPositionXCoordinate()][newEnemy->GetPositionYCoordinate()] = Util::EnemyTile;
}

void Map::InsertCorpse(const Corpse* newCorpse)
{
	this->MapTiles[newCorpse->GetPositionXCoordinate()][newCorpse->GetPositionYCoordinate()] = Util::CorpseTile;
}

Vendor* Map::FindVendor(const int playerPositionXCoordinate, const int playerPositionYCoordinate)
{
	for (int i = 0; i < this->NumberOfVendors; i++)
		if (this->MapVendors.at(i).GetPositionXCoordinate() == playerPositionXCoordinate && this->MapVendors.at(i).GetPositionYCoordinate() == playerPositionYCoordinate)
			return &(this->MapVendors.at(i));
	return nullptr;
}

Chest* Map::FindChest(const int playerPositionXCoordinate, const int playerPositionYCoordinate)
{
	for (int i = 0; i < this->NumberOfChests; i++)
		if (this->MapChests.at(i).GetPositionXCoordinate() == playerPositionXCoordinate && this->MapChests.at(i).GetPositionYCoordinate() == playerPositionYCoordinate)
			return &(this->MapChests.at(i));
	return nullptr;
}

Enemy* Map::FindEnemy(const int playerPositionXCoordinate, const int playerPositionYCoordinate)
{
	for (int i = 0; i < this->NumberOfEnemies; i++)
		if (this->MapEnemies.at(i).GetPositionXCoordinate() == playerPositionXCoordinate && this->MapEnemies.at(i).GetPositionYCoordinate() == playerPositionYCoordinate)
			return &(this->MapEnemies.at(i));
	return nullptr;
}

void Map::RemoveEnemy(const int playerPositionXCoordinate, const int playerPositionYCoordinate)
{
	for (int i = 0; i < this->NumberOfEnemies; i++)
		if (this->MapEnemies.at(i).GetPositionXCoordinate() == playerPositionXCoordinate && this->MapEnemies.at(i).GetPositionYCoordinate() == playerPositionYCoordinate)
		{
			this->MapEnemies.erase(this->MapEnemies.begin() + i);
			this->NumberOfEnemies = this->NumberOfEnemies - 1;
		}
}

void Map::RemoveChest(const int playerPositionXCoordinate, const int playerPositionYCoordinate)
{
	for (int i = 0; i < this->NumberOfChests; i++)
		if (this->MapChests.at(i).GetPositionXCoordinate() == playerPositionXCoordinate && this->MapChests.at(i).GetPositionYCoordinate() == playerPositionYCoordinate)
		{
			this->MapChests.erase(this->MapChests.begin() + i);
			this->NumberOfChests = this->NumberOfChests - 1;
			this->MapTiles[playerPositionXCoordinate][playerPositionYCoordinate] = Util::WalkableTile;
		}
}

void Map::RemoveCorpse(const int playerPositionXCoordinate, const int playerPositionYCoordinate)
{
	for (int i = 0; i < this->NumberOfCorpses; i++)
		if (this->MapCorpses.at(i).GetPositionXCoordinate() == playerPositionXCoordinate && this->MapCorpses.at(i).GetPositionYCoordinate() == playerPositionYCoordinate)
		{
			this->MapTiles[playerPositionXCoordinate][playerPositionYCoordinate] = this->MapCorpses.at(i).GetStandingOnTile();
			this->MapCorpses.erase(this->MapCorpses.begin() + i);
			this->NumberOfCorpses = this->NumberOfCorpses - 1;
		}
}

Corpse* Map::FindCorpse(const int playerPositionXCoordinate, const int playerPositionYCoordinate)
{
	for (int i = 0; i < this->NumberOfCorpses; i++)
		if (this->MapCorpses.at(i).GetPositionXCoordinate() == playerPositionXCoordinate && this->MapCorpses.at(i).GetPositionYCoordinate() == playerPositionYCoordinate)
			return &(this->MapCorpses.at(i));
	return nullptr;
}

void Map::MoveEnemies(const int playerXCoordinate, const int playerYCoordinate)
{
	for (int i = 0; i < this->NumberOfEnemies; i++)
	{
		this->MapEnemies[i].Move(this, playerXCoordinate, playerYCoordinate);
	}
}
