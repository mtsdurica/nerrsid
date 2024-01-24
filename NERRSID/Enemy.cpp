#include "Enemy.h"
#include "Map.h"

#include <iostream>
#include <queue>
#include <stack>
#include <cmath>
#include <utility>

Enemy::Enemy() : Entity(), AggroFlag(false)
{
}

Enemy::Enemy(std::string name, const int gold, const int itemsInInventory, const int maximumItemsInInventory, const int positionXCoordinate, const int positionYCoordinate) : Entity(
	std::move(name), gold, itemsInInventory, maximumItemsInInventory, positionXCoordinate, positionYCoordinate), AggroFlag(false)
{
}

std::vector<std::vector<int>> Enemy::TileToInt(Map* map)
{
	std::vector<std::vector<int>> intMap(Util::MAX_X, std::vector<int>(Util::MAX_Y, 0));

	for (int x = 0; x < Util::MAX_X; x++)
	{
		for (int y = 0; y < Util::MAX_Y; y++)
		{
			if (map->GetMapTiles()[x][y] == WalkableTile
				|| map->GetMapTiles()[x][y] == ChestTile
				|| map->GetMapTiles()[x][y] == VendorTile
				|| map->GetMapTiles()[x][y] == CorpseTile
				|| map->GetMapTiles()[x][y] == StairsTile)
			{
				intMap[x][y] = 1;
			}
		}
	}
	return intMap;
}

bool Enemy::IsValidMove(const std::vector<std::vector<int>>& map, const int row, const int col)
{
	return row >= 0 && row < Util::MAX_X && col >= 0 && col < Util::MAX_Y && map[col][row] == 1;
}

bool Enemy::GetAggroFlag() const
{
	return this->AggroFlag;
}

void Enemy::SetAggroFlag(const bool aggroFlag)
{
	this->AggroFlag = aggroFlag;
}

// TODO: Needs rework big time
std::vector<Util::Point> Enemy::FindShortestPath(const std::vector<std::vector<int>>& map, const Util::Point start, const Util::Point end) const
{
	const std::vector<int> dr = { 1, -1, 0, 0 };
	const std::vector<int> dc = { 0, 0, 1, -1 };

	std::vector<std::vector<bool>> visited(map.size(), std::vector<bool>(map[0].size(), false));
	std::vector<std::vector<Util::Point>> previous(map.size(), std::vector<Util::Point>(map[0].size(), Util::Point(-1, -1)));

	std::queue<Util::Point> q;
	q.push(start);
	visited[start.X][start.Y] = true;

	while (!q.empty()) {
		Util::Point current = q.front();
		q.pop();

		if (current.X == end.X && current.Y == end.Y) {
			// Reconstruct the path from 'end' to 'start'
			std::stack<Util::Point> path;
			while (current.X != -1 && current.Y != -1) {
				path.push(current);
				current = previous[current.X][current.Y];
			}

			std::vector<Util::Point> result;
			while (!path.empty()) {
				result.push_back(path.top());
				path.pop();
			}
			result.erase(result.begin());

			return result;
		}

		for (int i = 0; i < 4; ++i) {
			int newRow = current.Y + dr[i];
			int newCol = current.X + dc[i];

			if (this->IsValidMove(map, newRow, newCol) && !visited[newCol][newRow]) {
				visited[newCol][newRow] = true;
				previous[newCol][newRow] = current;
				q.emplace(newCol, newRow);
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

	std::vector<std::vector<int>> intMap(Util::MAX_X, std::vector<int>(Util::MAX_Y, 0));
	intMap = this->TileToInt(map);

	const std::vector<Util::Point> result = FindShortestPath(
		intMap, Util::Point(this->PositionXCoordinate, this->PositionYCoordinate), Util::Point(playerXCoordinate, playerYCoordinate));
	if (!result.empty()) {
		const Util::Point move = result.at(0);
		if (map->GetMapTiles()[move.X][move.Y] == WalkableTile)
		{
			map->GetMapTiles()[this->PositionXCoordinate][this->PositionYCoordinate] = WalkableTile;
			this->PositionXCoordinate = move.X;
			this->PositionYCoordinate = move.Y;
			map->GetMapTiles()[this->PositionXCoordinate][this->PositionYCoordinate] = EnemyTile;
			std::cerr << move.X << " " << move.Y << std::endl;
		}
	}
}
