#pragma once
#include <vector>

#include "Entity.h"
#include "Util.h"

class Map;

class Enemy final : public Entity
{
private:
	// TODO: Add detectable range
	bool AggroFlag;
	static bool IsValidMove(const std::vector<std::vector<int>>& map, int row, int col);
	static std::vector<std::vector<int>> TileToInt(Map* map);
	std::vector<Util::Point> FindShortestPath(const std::vector<std::vector<int>>& map, Util::Point start, Util::Point end) const;
public:
	Enemy();
	Enemy(std::string name, int gold, int itemsInInventory, int maximumItemsInInventory, int positionXCoordinate, int positionYCoordinate);
	bool GetAggroFlag() const;
	void SetAggroFlag(bool aggroFlag);
	void Move(Map* map, int playerXCoordinate, int playerYCoordinate);
};

