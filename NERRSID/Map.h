#pragma once
#include <cstdint>
#include <array>
#include <SDL.h>

#include "Vendor.h"

#define UINT_CHANGEABLE uint8_t // Changeable data type if needed to generate larger maps than 0-255

enum
{
	GameResolutionWidth = 1600,
	GameResolutionHeight = 720,
	MaxX = 40,            // Max base room width
	MaxY = (GameResolutionHeight / 16),    // Max base room height
	PseudoRoomSize = 4      // Pseudo max room size
};

typedef enum Tiles
{
	WallTile, WalkableTile, PlayerTile, VendorTile
} Tiles;

typedef struct Point
{
	UINT_CHANGEABLE X;
	UINT_CHANGEABLE Y;
} Point;

typedef struct Wall
{
	Point Start; // Start point of the wall
	Point End;   // End point of the wall
} Wall;

typedef struct Room
{
	Wall Top;            // Top wall
	Wall Bot;            // Bottom wall
	Wall Left;           // Left wall
	Wall Right;          // Right wall
	struct Room* Child1; // Left/top child
	struct Room* Child2; // Right/Bottom child
	Point Center;        // Center point of the room
} Room;

class Map
{
private:
	std::array<std::array<Tiles, MaxY>, MaxX> MapTiles{};
	std::array<Vendor, 5> MapVendors;
	int NumberOfVendors;
	void DrawHorizontalWall(const Wall* newWall);
	void DrawVerticalWall(const Wall* newWall);
	static Point GetChildCenter(const Room* childRoom);
	static UINT_CHANGEABLE RandomInRange(const UINT_CHANGEABLE min, const UINT_CHANGEABLE max);
	void GenerateHorizontalSplit(Room* r);
	void GenerateVerticalSplit(Room* r);
	Room InitializeBase();
	bool GenerateVendors();

public:
	Map();
	~Map();
	std::array<std::array<Tiles, MaxY>, MaxX>& GetMapTiles();
	std::array<Vendor, 5>& GetMapVendors();
	void InsertVendor(const Vendor* newVendor);
	static Vendor* FindVendor(std::array<Vendor, 5>* mapVendors, int numberOfVendors, int playerPositionXCoordinate, int playerPositionYCoordinate);
	int GetNumberOfVendors() const;
	bool GenerateMap();
};