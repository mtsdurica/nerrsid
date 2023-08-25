#include <cstdlib>

#include "Map.h"

Map::Map()
{
	for (int x = 0; x < MAX_X; x++)
		for (int y = 0; y < MAX_Y; y++)
			mapTiles[x][y] = Walkable;
	generateMap();
}
Map::~Map() = default;
void Map::drawHorizontalWall(wall* newWall)
{
	for (UINT_CHANGEABLE x = newWall->start.x; x <= newWall->end.x; x++)
		mapTiles[x][newWall->start.y] = Wall;
}
void Map::drawVerticalWall(wall* newWall)
{
	for (UINT_CHANGEABLE y = newWall->start.y; y <= newWall->end.y; y++)
		mapTiles[newWall->start.x][y] = Wall;
}
point Map::getChildCenter(room* childRoom)
{
	point center;
	center.x = childRoom->top.start.x + (childRoom->top.end.x - childRoom->top.start.x) / 2;
	center.y = childRoom->right.start.y + (childRoom->right.end.y - childRoom->right.start.y) / 2;
	return center;
}
UINT_CHANGEABLE Map::randomInRange(UINT_CHANGEABLE min, UINT_CHANGEABLE max)
{
	// Calculate the middle of the range
	UINT_CHANGEABLE middle = (min + max) / 2;
	// Calculate the allowable deviation from the middle
	UINT_CHANGEABLE deviation = (max - min) / 3;
	return (rand() % (deviation * 2 + 1)) + (middle - deviation);
}
void Map::generateHorizontalSplit(room* r)
{
	if (r == nullptr)
		return;

	if (r->left.start.y + (PSEUDO_ROOM_SIZE / 2) >= r->left.end.y - (PSEUDO_ROOM_SIZE / 2))
		return;

	UINT_CHANGEABLE
		rand_y = randomInRange(r->left.start.y + (PSEUDO_ROOM_SIZE / 2), r->left.end.y - (PSEUDO_ROOM_SIZE / 2));

	wall new_split = { { r->top.start.x, rand_y }, { r->top.end.x, rand_y } };

	room child1 =
	{ r->top, new_split, { r->top.start, new_split.start }, { r->top.end, new_split.end }, nullptr, nullptr,
	  { 0, 0 } };
	r->child1 = &child1;

	room child2 =
	{ new_split, r->bot, { new_split.start, r->bot.start }, { new_split.end, r->bot.end }, nullptr, nullptr,
	  { 0, 0 } };
	r->child2 = &child2;

	drawHorizontalWall(&new_split);

	generateVerticalSplit(&child1);
	child1.center = getChildCenter(&child1);

	generateVerticalSplit(&child2);
	child2.center = getChildCenter(&child2);
	// Drawing path between two sister rooms
	for (int i = child2.center.y; i > child1.center.y; i--)
		mapTiles[child2.center.x][i] = Walkable;
}
void Map::generateVerticalSplit(room* r)
{
	if (r == nullptr)
		return;

	if (r->top.start.x + PSEUDO_ROOM_SIZE >= r->top.end.x - PSEUDO_ROOM_SIZE)
		return;

	UINT_CHANGEABLE rand_x = randomInRange(r->top.start.x + PSEUDO_ROOM_SIZE, r->top.end.x - PSEUDO_ROOM_SIZE);

	wall new_split = { { rand_x, r->top.start.y }, { rand_x, r->bot.start.y } }; // third thingy maybe wrong

	room child1 =
	{ { r->top.start, new_split.start }, { r->bot.start, new_split.end }, r->left, new_split, nullptr, nullptr,
	 { 0, 0 } };
	r->child1 = &child1;

	room child2 =
	{ { new_split.start, r->top.end }, { new_split.end, r->bot.end }, new_split, r->right, nullptr, nullptr,
	 { 0, 0 } };
	r->child2 = &child2;

	drawVerticalWall(&new_split);

	generateHorizontalSplit(&child1);
	child1.center = getChildCenter(&child1);

	generateHorizontalSplit(&child2);
	child2.center = getChildCenter(&child2);
	// Drawing path between two sister rooms
	for (int i = child2.center.x; i > child1.center.x; i--)
		mapTiles[i][child2.center.y] = Walkable;
}
room Map::initializeBase()
{
	room newRoom =
	{ {{ 0, 0 }, { MAX_X - 1, 0 }}, {{ 0, MAX_Y - 1 }, { MAX_X - 1, MAX_Y - 1 }}, {{ 0, 0 }, { 0, MAX_Y - 1 }},
	 {{ MAX_X - 1, 0 }, { MAX_X - 1, MAX_Y - 1 }}, nullptr, nullptr, { 0, 0 } };
	drawHorizontalWall(&newRoom.top);
	drawHorizontalWall(&newRoom.bot);
	drawVerticalWall(&newRoom.left);
	drawVerticalWall(&newRoom.right);
	return newRoom;
}

void Map::generateMap()
{
	room base = initializeBase();

	if (rand() % 2)
		(void)generateVerticalSplit(&base);
	else
		(void)generateHorizontalSplit(&base);

}

std::array<std::array<tiles, MAX_Y>, MAX_X>& Map::getMapTiles()
{
	return mapTiles;
}
