#pragma once
#include <vector>

#include "Entity.h"

class Map;

struct PointBFS
{
	int row, col;
	PointBFS(int r, int c) : row(r), col(c) {}
};

class Enemy final : public Entity
{
private:
	// TODO: Add detectable range
	bool AggroFlag;
	static bool IsValidMove(const std::vector<std::vector<int>>& map, int row, int col);
	static std::vector<std::vector<int>> TileToInt(Map* map);
	std::vector<PointBFS> FindShortestPath(const std::vector<std::vector<int>>& map, PointBFS start, PointBFS end) const;
public:
	Enemy();
	Enemy(std::string name, int gold, int itemsInInventory, int maximumItemsInInventory, int positionXCoordinate, int positionYCoordinate);
	bool GetAggroFlag() const;
	void SetAggroFlag(bool aggroFlag);
	void Move(Map* map, int playerXCoordinate, int playerYCoordinate);
};

