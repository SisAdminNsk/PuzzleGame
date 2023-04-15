#include "TestSolutonFunc.h"

int* CreateMatrixView(const std::vector<sf::Sprite>& allPuzzles)
{
	// META DATE
	//1 - "4" , 2 - "3" , 3 - "5" , 4 - "2" 
	// 5 - "15", 6 - "6" 7 - "10" , 8 - "14"
	// 9 - "1" , 10 - "13", 11 - "7" , 12 - "11"
	// 13 - "12", 14 - "9", 15 - "8"
	// END OF META DATE

	int metaDate[] = { 4,3,5,2,15,6,10,14,1,13,7,11,12,9,8 };// ���� ������ � ����� ������� ����� ������� � ����������

	// ��� ������������� ��������� �������� � ������� � ��������� ������� ���������� ������-���� �������� X � Y
	std::map<std::string, int> decipherNumbers = { { "0_160",0 },{"160_160",1},{"320_160",2},{"480_160",3},
	{"0_320",4},{"160_320",5},{"320_320",6},{"480_320",7},{"0_480",8},{"160_480",9},{"320_480",10},{"480_480",11},
	{"0_640",12},{"160_640",13},{"320_640",14} };

	int *puzzleSquence = new int[PUZZLE_COUNT];// �� ��� �� ��������� � ��������� ������� ��� ���������
	int number = 0;
	for (const auto puzzle : allPuzzles) 
	{
		std::string decipherStr = std::to_string(int(puzzle.getPosition().x)) + "_" + std::to_string(int(puzzle.getPosition().y));
 		puzzleSquence[decipherNumbers[decipherStr]] = metaDate[number];
		number++;
	}
	return puzzleSquence;
}

//����������� ����������
//����� ��������� ��������, ��� ������� ��� ����� ����� ������ ��������,
//������� ������� �����.������� �������� � �������� �������� �����
//����� ������ - ������ ���������� ����������� ��� ���.���� ����� �����
//����������� �� ���� ���� - ������, �� ��� ����� �������� � ���������� ������������, 
//���� �� �������� - �� ����� ����� ������ ������� �������� �������� ����.
// � ������� ����, �� ����� ��������� ��� 

bool IsPuzzleCanBeSolved(const int* puzzleSquence)
{
	int tab = 0;
	for (int i = 0; i < PUZZLE_COUNT;i++)
	{
		tab++;
		std::cout << puzzleSquence[i] << " ";
		if (tab % 4 == 0)
			std::cout << "\n";
	}

	int chaos = 0; //���������� ����������� �� ����
	int puzzleCurrNum; //��������, ��� ������� �� ������������� ����������
	for (int i = 0; i < PUZZLE_COUNT-1; i++)
	{
		puzzleCurrNum = puzzleSquence[i];
		for (int j = 0; j < PUZZLE_COUNT; j++) 
		{
			if (puzzleCurrNum > puzzleSquence[j])
				chaos++;
		}
	}

	if (chaos % 2 == 1) 
	{
		std::cout << "CANT!\nSwapping...\n\n";
		return false;// ������������� � ��� ��� ���� ������� ������
	}
		
	std::cout << "OK!\n\n";
	return true;// ���� ����� ������ �� OK
}

void MakePermutate(std::vector<sf::Sprite>& allPuzzles)
{
	auto objOne = std::find_if(allPuzzles.begin(), allPuzzles.end(),
		[&allPuzzles](sf::Sprite& puzzle) { return(puzzle.getPosition().x == 160 && puzzle.getPosition().y == 640); });

	auto objTwo = std::find_if(allPuzzles.begin(), allPuzzles.end(),
		[&allPuzzles](sf::Sprite& puzzle) { return(puzzle.getPosition().x == 320 && puzzle.getPosition().y == 640); });

	int firstPuzzleIndex = objOne - allPuzzles.begin();
	int secondPuzzleIndex = objTwo - allPuzzles.begin();

	allPuzzles[firstPuzzleIndex].setPosition(320, 640);
	allPuzzles[secondPuzzleIndex].setPosition(160, 640);
}