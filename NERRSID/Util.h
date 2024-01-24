#pragma once

#include <random>

namespace Util
{
	constexpr int GAME_RESOLUTION_WIDTH = 1600;
	constexpr int GAME_RESOLUTION_HEIGHT = 720;// Max base room height
	constexpr int MAX_X = 40; // Max base room width
	constexpr int MAX_Y = (GAME_RESOLUTION_HEIGHT / 16);
	constexpr int PSEUDO_ROOM_SIZE = 4;  // Pseudo max room size

	inline int RandomChangeableIntInRange(const int minNum, const int maxNum)
	{
		static std::random_device randomDevice;
		static std::mt19937 randomNumberGenerator(randomDevice());
		std::uniform_int_distribution<std::mt19937::result_type> uniformDistribution(minNum, maxNum);
		return static_cast<int>(uniformDistribution(randomNumberGenerator));
	}

	inline int RandomIntInRange(const int minNum, const int maxNum)
	{
		static std::random_device randomDevice;
		static std::mt19937 randomNumberGenerator(randomDevice());
		std::uniform_int_distribution<std::mt19937::result_type> uniformDistribution(minNum, maxNum);
		return static_cast<int>(uniformDistribution(randomNumberGenerator));
	}

	typedef struct Point
	{
		int X;
		int Y;

		Point(const int coordX, const int coordY) : X(static_cast<int>(coordX)), Y(static_cast<int>(coordY)) {}
		Point() = default;
	} Point;

	typedef enum Tiles
	{
		WallTile, WalkableTile, PlayerTile, VendorTile, ChestTile, EnemyTile, CorpseTile, StairsTile
	} Tiles;

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
		Room* Child1; // Left/top child
		Room* Child2; // Right/Bottom child
		Point Center;        // Center point of the room
	} Room;
}