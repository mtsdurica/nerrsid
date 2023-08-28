#pragma once
#include <cstdint>
#include <array>
#include <list>
#include <SDL.h>

#include "Tilemap.h"
#include "Vendor.h"

#define GAME_RESOLUTION_WIDTH 1600
#define GAME_RESOLUTION_HEIGHT 720
#define MAX_X 40                // Max base room width
#define MAX_Y GAME_RESOLUTION_HEIGHT / 16           // Max base room height
#define UINT_CHANGEABLE uint8_t // Changeable data type if needed to generate larger maps than 0-255
#define PSEUDO_ROOM_SIZE 4      // Pseudo max room size

typedef enum tiles
{
	Wall, Walkable, PlayerTile, VendorTile
} tiles;

typedef struct point
{
	UINT_CHANGEABLE x;
	UINT_CHANGEABLE y;
} point;

typedef struct wall
{
	point start; // Start point of the wall
	point end;   // End point of the wall
} wall;

typedef struct room
{
	wall top;            // Top wall
	wall bot;            // Bottom wall
	wall left;           // Left wall
	wall right;          // Right wall
	struct room* child1; // Left/top child
	struct room* child2; // Right/Bottom child
	point center;        // Center point of the room
} room;

class Map
{
private:
	std::array<std::array<tiles, MAX_Y>, MAX_X> mapTiles{};
	std::array<Vendor, 5> mapVendors;
	int numberOfVendors;
	void DrawHorizontalWall(wall* newWall);
	void DrawVerticalWall(wall* newWall);
	static point GetChildCenter(room* childRoom);
	static UINT_CHANGEABLE RandomInRange(UINT_CHANGEABLE min, UINT_CHANGEABLE max);
	void GenerateHorizontalSplit(room* r);
	void GenerateVerticalSplit(room* r);
	room InitializeBase();
	void GenerateVendors();
	void GenerateMap();

public:
	Map();
	~Map();
	std::array<std::array<tiles, MAX_Y>, MAX_X>& GetMapTiles();
	std::array<Vendor, 5>& GetMapVendors();
	void InsertVendor(Vendor* newVendor);
	static Vendor* FindVendor(std::array<Vendor, 5>* mapVendors, int numberOfVendors, int playerPositionXCoordinate, int playerPositionYCoordinate);
	int GetNumberOfVendors();
};

