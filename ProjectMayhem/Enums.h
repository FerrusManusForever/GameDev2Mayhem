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
	OK,
	Blocked,
	Combat,
	NewRoom,
};

