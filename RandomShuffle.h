#pragma once
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include <ctime>

struct position
{
	int xCoord;
	int yCoord;
};

// class for random generation of puzzles positions
class RandomShuffleClass 
{
private:
	std::vector<position> allPositions;// contains all position's
	void fillAllPosotions();

public:
	std::vector<position>& getAllPositions();// return all shuffling position's
	RandomShuffleClass();// constructor
	void MakeShuffle(std::vector<sf::Sprite>& allPuzzles);// finish shuffle func
};