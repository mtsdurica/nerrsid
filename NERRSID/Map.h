#pragma once
#include <cstdint>
#include <array>
#include <SDL.h>

#include "Enemy.h"
#include "Corpse.h"
#include "Vendor.h"
#include "Util.h"

typedef enum Tiles
{
	WallTile, WalkableTile, PlayerTile, VendorTile, ChestTile, EnemyTile, CorpseTile, StairsTile
} Tiles;

typedef struct Wall
{
	Util::Point Start; // Start point of the wall
	Util::Point End;   // End point of the wall
} Wall;

typedef struct Room
{
	Wall Top;            // Top wall
	Wall Bot;            // Bottom wall
	Wall Left;           // Left wall
	Wall Right;          // Right wall
	struct Room* Child1; // Left/top child
	struct Room* Child2; // Right/Bottom child
	Util::Point Center;        // Center point of the room
} Room;

class Map
{
private:
	std::array<std::array<Tiles, Util::MAX_Y>, Util::MAX_X> MapTiles{};
	std::array<Vendor, 5> MapVendors;
	std::vector<Chest> MapChests;
	std::vector<Enemy> MapEnemies;
	std::vector<Corpse> MapCorpses;
	int NumberOfVendors;
	int NumberOfChests;
	int NumberOfEnemies;
	int NumberOfCorpses;
	void DrawHorizontalWall(const Wall* newWall);
	void DrawVerticalWall(const Wall* newWall);
	static Util::Point GetChildCenter(const Room* childRoom);
	void GenerateHorizontalSplit(Room* r);
	void GenerateVerticalSplit(Room* r);
	Room InitializeBase();
	bool GenerateVendors();
	bool GenerateChests();
	bool GenerateEnemies();
	void GenerateStairs();

public:
	Map();
	~Map();
	std::array<std::array<Tiles, Util::MAX_Y>, Util::MAX_X>& GetMapTiles();
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