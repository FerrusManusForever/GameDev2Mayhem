#pragma once
enum Direction
{
	North,
	East,
	South,
	West
};

enum MoveResult
{
	OK = 0,
	Blocked = 1,
	Combat = 2,
	NewRoom = 3
};

