#include <iostream>
#include <vector>
#include "RandomShuffle.h"
#include <SFML/Graphics.hpp>
#include "LoadFromFile.h"
#include <map>
#include "Constants.h"
#include "TestSolutonFunc.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pyatnashki", sf::Style::Close);
    sf::Mouse mouse;// for mouse
    sf::Clock clock;// starts the clock
    LoadFromFile files;// class for loading files

    sf::Sprite pyatnaskaSprite;// for pyatnashka 
    sf::Sprite emptyPuzzleSprite;// special serialized sprite for empty symbol
    sf::Sprite backgroundSprite;// for background
    sf::Sprite reloadButtonSprite;// for reloadButton

    pyatnaskaSprite = files.loadPyatnashkiSprite();// load sprite from file
    backgroundSprite = files.loadBackgroundSprite();// load background sprite
    reloadButtonSprite = files.loadReloadButtonSprite();

    sf::Font myFont;// for arial.ttf font 
    sf::Text stepCounter;// showing counter of game steps
    sf::Text winnerMessage;// message for winner
    sf::Text timeMessage;// showing time 

    int steps = 0;// steps counter

    myFont = files.loadFont();// load font
    stepCounter.setFont(myFont);
    stepCounter.setCharacterSize(FONT_SIZE);// set font size
    stepCounter.setPosition(STEP_COUNTER_XCOORD, STEP_COUNTER_YCOORD);
    stepCounter.setString("STEPS: " + std::to_string(steps));// when game start counter = 0

    timeMessage.setFont(myFont);
    timeMessage.setCharacterSize(FONT_SIZE);
    timeMessage.setPosition(TIME_MESSAGE_XCOORD, TIME_MESSAGE_YCOORD);

    sf::Time elapsedTime = clock.getElapsedTime();// lounch time;

    std::vector<sf::Sprite> allPuzzles;// will contains all pyatnashki sprite's
    // key - number of puzzle in puzzle vector,value - true coord 
    std::map<int, position> truePositionMap = { {0, {480,160}},{1,{320,160}},{2,{0,320}},
        {3,{160,160}},{4,{320,640}},{5,{160,320}},{6,{160,480}},{7,{160,640}},{8,{0,160}},
        {9,{0,640}},{10,{320,320}},{11,{320,480}},{12,{480,480}},{13,{0,480}},{14,{480,320}} };

    for (int i = 0, yCoord = 0; i < 4; i++, yCoord += PUZZLE_WIDTH)
    {
        for (int j = 0, xCoord = 0; j < 4; j++, xCoord += PUZZLE_WIDTH)
        {
            pyatnaskaSprite.setTextureRect(sf::IntRect(yCoord, xCoord, PUZZLE_WIDTH, PUZZLE_HEIGHT));// makes sprites for pyatnashki
            pyatnaskaSprite.setPosition(xCoord, yCoord + PUZZLE_WIDTH);
            allPuzzles.push_back(pyatnaskaSprite);// add pyatnashki to container
        }
    }

    emptyPuzzleSprite = allPuzzles[allPuzzles.size() - 1];// get emptyPuzzle
    allPuzzles.pop_back();// delete this puzzle, after getting him

    // set random position's
    RandomShuffleClass shuffle;
    shuffle.MakeShuffle(allPuzzles);

    // checking can solve or not, if not - we will swap 2 last elements
    int* puzzleSequecne = CreateMatrixView(allPuzzles);
    if (!IsPuzzleCanBeSolved(puzzleSequecne))// swaping puzzles to make puzzle solvable   
        MakePermutate(allPuzzles);

    // end of checking 
    int uniqId = 0;
    int idCounter = 0;
    bool isMove = false;
    // GAME CICLE 
    while (window.isOpen())// run the program as long as the window is open
    {
        sf::Event event;// check all the window's events that were triggered since the last iteration of the loop
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)// "close requested" event: we close the window
                window.close();

            idCounter = 0;
            if (event.type == sf::Event::MouseButtonPressed)// if mouse button pressed 
            {
                if (event.key.code == sf::Mouse::Left)// if it's left button
                {
                    for (sf::Sprite pyatnaska : allPuzzles)// check all puzzles of containing mouse cursor
                    {
                        if (pyatnaska.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y))
                        {
                            if (abs(emptyPuzzleSprite.getPosition().x - pyatnaska.getPosition().x) <= PUZZLE_WIDTH &&
                                abs(emptyPuzzleSprite.getPosition().y - pyatnaska.getPosition().y) <= PUZZLE_HEIGHT)
                            {
                                if ((pyatnaska.getPosition().x == emptyPuzzleSprite.getPosition().x) ||
                                    pyatnaska.getPosition().y == emptyPuzzleSprite.getPosition().y)
                                {
                                    steps++;// inc steps counter
                                    stepCounter.setString("STEPS: " + std::to_string(steps));// update stepCounter message
                                    uniqId = idCounter;// memorize uniqid
                                    isMove = true;// now we can move this puzzle
                                }
                            }
                        }
                        idCounter++;// inc uniq id counter
                    }
                    if (reloadButtonSprite.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y))
                    {
                        steps = 0;
                        emptyPuzzleSprite.setPosition(EMPTY_PUZZLE_XCOORD, EMPTY_PUZZLE_YCOORD);
                        shuffle.MakeShuffle(allPuzzles);// make shuffle 
                        stepCounter.setString("STEPS: " + std::to_string(0));
                        clock.restart();// reset game time

                        int* puzzleSequecneReload = CreateMatrixView(allPuzzles);// meta data 
                        if (!IsPuzzleCanBeSolved(puzzleSequecneReload))// swaping puzzles to make puzzle solvable   
                            MakePermutate(allPuzzles);// do this if pazzle can't solve
                    }
                }
            }
        }

        if (isMove)// if we can move 
        {
            // swapping position of empty puzzle and puzzle that we have known before
            int swapX = emptyPuzzleSprite.getPosition().x, swapY = emptyPuzzleSprite.getPosition().y;
            emptyPuzzleSprite.setPosition(allPuzzles[uniqId].getPosition().x, allPuzzles[uniqId].getPosition().y);
            allPuzzles[uniqId].setPosition(swapX, swapY);
            isMove = false;
        }

        elapsedTime = clock.getElapsedTime();// get updated time value
        timeMessage.setString(std::to_string(int(elapsedTime.asSeconds())) + " Sec");// update time;

        window.clear();
        // drawing on the screen
        window.draw(backgroundSprite);// drawing background
        window.draw(reloadButtonSprite);// drawing reloadButton sprite
        window.draw(stepCounter);// drawing steps
        window.draw(timeMessage);// drawing timer
        window.draw(emptyPuzzleSprite);// draw empty puzzle sprite

        for (int i = 0; i < allPuzzles.size(); i++)// drawing all pyatnashka puzzle's 
        {
            position currentPos(int(allPuzzles[i].getPosition().x), int(allPuzzles[i].getPosition().y));// get current position;
            // check green or not?
            if (currentPos.xCoord == truePositionMap[i].xCoord && currentPos.yCoord == truePositionMap[i].yCoord)
                allPuzzles[i].setColor(sf::Color::Green);// make puzzle green
            else
                allPuzzles[i].setColor(sf::Color::White);// set default color

            window.draw(allPuzzles[i]);// draw 
        }
        // stop drawing on the screen

        // cheking is player win
        int greenPuzzlesCount = 0;// for calculate green puzzles
        for (auto puzzle : allPuzzles)
            if (puzzle.getColor() == sf::Color::Green)
                greenPuzzlesCount++;

        // if all puzzles are green
        if (greenPuzzlesCount == 15)
        {

            // make someting
        }
        greenPuzzlesCount = 0;// reset variable

        window.display();
    }
}