#pragma once
#include <string>

struct position
{
	int xCoord = 0;
	int yCoord = 0;

	position() {  };

	position(int x, int y)
	{
		xCoord = x;
		yCoord = y;
	}
};