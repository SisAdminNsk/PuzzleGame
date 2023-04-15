#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <iostream>
#include <unordered_map>
#include "PointStruct.h"


const int PUZZLE_COUNT = 15;
// creates a matrix image of the playing field to calculate whether the puzzle can be solved
int* CreateMatrixView(const std::vector<sf::Sprite>& allPuzzles);
// check can puzzle be solved or not
bool IsPuzzleCanBeSolved(const int* puzzles);
// swaping 2 elements to make puzzle can be solved
void MakePermutate(std::vector<sf::Sprite>& allPuzzles);