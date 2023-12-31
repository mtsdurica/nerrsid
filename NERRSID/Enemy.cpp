#include "Enemy.h"
#include "Map.h"

#include <iostream>
#include <queue>
#include <stack>
#include <cmath>

Enemy::Enemy() : Entity(), AggroFlag(false)
{
}

Enemy::Enemy(std::string name, const int gold, const int itemsInInventory, const int maximumItemsInInventory, const int positionXCoordinate, const int positionYCoordinate) : Entity(name, gold, itemsInInventory, maximumItemsInInventory, positionXCoordinate, positionYCoordinate), AggroFlag(false)
{
}

std::vector<std::vector<int>> Enemy::TileToInt(Map* map)
{
	std::vector<std::vector<int>> intMap(MaxY, std::vector<int>(MaxX, 0));

	for (int x = 0; x < MaxX; x++)
	{
		for (int y = 0; y < MaxY; y++)
		{
			if (map->GetMapTiles()[x][y] == WalkableTile
				|| map->GetMapTiles()[x][y] == ChestTile
				|| map->GetMapTiles()[x][y] == VendorTile
				|| map->GetMapTiles()[x][y] == CorpseTile
				|| map->GetMapTiles()[x][y] == StairsTile)
			{
				intMap[y][x] = 1;
			}
		}
	}
	return intMap;
}

bool Enemy::IsValidMove(const std::vector<std::vector<int>>& map, const int row, const int col)
{
	return row >= 0 && row < MaxX && col >= 0 && col < MaxY && map[row][col] == 1;
}

bool Enemy::GetAggroFlag() const
{
	return this->AggroFlag;
}

void Enemy::SetAggroFlag(const bool aggroFlag)
{
	this->AggroFlag = aggroFlag;
}

std::vector<PointBFS> Enemy::FindShortestPath(const std::vector<std::vector<int>>& map, const PointBFS start, const PointBFS end) const
{
	const std::vector<int> dr = { 1, -1, 0, 0 };
	const std::vector<int> dc = { 0, 0, 1, -1 };

	std::vector<std::vector<bool>> visited(map.size(), std::vector<bool>(map[0].size(), false));
	std::vector<std::vector<PointBFS>> previous(map.size(), std::vector<PointBFS>(map[0].size(), PointBFS(-1, -1)));

	std::queue<PointBFS> q;
	q.push(start);
	visited[start.row][start.col] = true;

	while (!q.empty()) {
		PointBFS current = q.front();
		q.pop();

		if (current.row == end.row && current.col == end.col) {
			// Reconstruct the path from 'end' to 'start'
			std::stack<PointBFS> path;
			while (current.row != -1 && current.col != -1) {
				path.push(current);
				current = previous[current.row][current.col];
			}

			std::vector<PointBFS> result;
			while (!path.empty()) {
				result.push_back(path.top());
				path.pop();
			}
			result.erase(result.begin());

			return result;
		}

		for (int i = 0; i < 4; ++i) {
			int newRow = current.row + dr[i];
			int newCol = current.col + dc[i];

			if (this->IsValidMove(map, newRow, newCol) && !visited[newRow][newCol]) {
				visited[newRow][newCol] = true;
				previous[newRow][newCol] = current;
				q.emplace(newRow, newCol);
			}
		}
	}

	// No path found, return an empty path
	return {};
}

void Enemy::Move(Map* map, int playerXCoordinate, int playerYCoordinate)
{
	const int deltaX = this->PositionXCoordinate - playerXCoordinate;
	const int deltaY = this->PositionYCoordinate - playerYCoordinate;

	const int distance = static_cast<int>(std::floor(sqrt(pow(deltaX, 2) + pow(deltaY, 2))));
	std::cerr << "Distance to player: " << distance << std::endl;

	if (distance <= 10)
		this->AggroFlag = true;

	if (!this->AggroFlag)
		return;

	std::vector<std::vector<int>> intMap(MaxX, std::vector<int>(MaxY, 0));
	intMap = this->TileToInt(map);

	const std::vector<PointBFS> result = FindShortestPath(
		intMap, { this->PositionYCoordinate,this->PositionXCoordinate, }, { playerYCoordinate, playerXCoordinate });
	if (!result.empty()) {
		const PointBFS move = result.at(0);
		if (map->GetMapTiles()[move.col][move.row] == WalkableTile)
		{
			map->GetMapTiles()[this->PositionXCoordinate][this->PositionYCoordinate] = WalkableTile;
			this->PositionXCoordinate = move.col;
			this->PositionYCoordinate = move.row;
			map->GetMapTiles()[this->PositionXCoordinate][this->PositionYCoordinate] = EnemyTile;
			std::cerr << move.col << " " << move.row << std::endl;
		}
	}
}
