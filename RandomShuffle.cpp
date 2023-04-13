#include "RandomShuffle.h"

void RandomShuffleClass::fillAllPosotions()
{
	allPositions.resize(15);// vector for 15 puzzle place's
	// define the position's
	allPositions = { {0,160},{160,160}, {320,160}, {480,160} ,
		{0,320},{160,320},{320,320},{480,320},
		{0,480},{160,480},{320,480},{480,480},
		{0,640},{160,640},{320,640} };
	// End of definding.
}

std::vector <position>& RandomShuffleClass::getAllPositions() { return allPositions; }

RandomShuffleClass::RandomShuffleClass()
{
	fillAllPosotions();
	MakeShuffle();
}

void RandomShuffleClass::MakeShuffle()
{
	srand(time(NULL));
	std::random_shuffle(allPositions.begin(),allPositions.end());
}
