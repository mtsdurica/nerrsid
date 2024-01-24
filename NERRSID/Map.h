#pragma once
#include <cstdint>
#include <array>
#include <SDL.h>

#include "Enemy.h"
#include "Corpse.h"
#include "Vendor.h"
#include "Util.h"

class Map
{
private:
	std::array<std::array<Util::Tiles, Util::MAX_Y>, Util::MAX_X> MapTiles{};
	std::array<Vendor, 5> MapVendors;
	std::vector<Chest> MapChests;
	std::vector<Enemy> MapEnemies;
	std::vector<Corpse> MapCorpses;
	int NumberOfVendors;
	int NumberOfChests;
	int NumberOfEnemies;
	int NumberOfCorpses;
	void DrawHorizontalWall(const Util::Wall* newWall);
	void DrawVerticalWall(const Util::Wall* newWall);
	static Util::Point GetChildCenter(const Util::Room* childRoom);
	void GenerateHorizontalSplit(Util::Room* r);
	void GenerateVerticalSplit(Util::Room* r);
	Util::Room InitializeBase();
	bool GenerateVendors();
	bool GenerateChests();
	bool GenerateEnemies();
	void GenerateStairs();

public:
	Map();
	~Map();
	std::array<std::array<Util::Tiles, Util::MAX_Y>, Util::MAX_X>& GetMapTiles();
	void InsertVendor(const Vendor* newVendor);
	void InsertChest(const Chest* newChest);
	void InsertEnemy(const Enemy* newEnemy);
	void InsertCorpse(const Corpse* newCorpse);
	Vendor* FindVendor(int playerPositionXCoordinate, int playerPositionYCoordinate);
	Chest* FindChest(int playerPositionXCoordinate, int playerPositionYCoordinate);
	Enemy* FindEnemy(int playerPositionXCoordinate, int playerPositionYCoordinate);
	void RemoveEnemy(int playerPositionXCoordinate, int playerPositionYCoordinate);
	void RemoveChest(int playerPositionXCoordinate, int playerPositionYCoordinate);
	void RemoveCorpse(int playerPositionXCoordinate, int playerPositionYCoordinate);
	Corpse* FindCorpse(int playerPositionXCoordinate, int playerPositionYCoordinate);
	void MoveEnemies(int playerXCoordinate, int playerYCoordinate);
	void AddCorpse(const Corpse* corpse);
	bool GenerateMap();
};