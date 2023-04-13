#include <iostream>
#include <vector>
#include "RandomShuffle.h"
#include <SFML/Graphics.hpp>
#include "LoadFromFile.h"
#include "Constants.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Pyatnashki");
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
    for (int i = 0, yCoord = 0; i < 4; i++, yCoord += PUZZLE_WIDTH)
    {
        for (int j = 0, xCoord = 0; j < 4; j++, xCoord += PUZZLE_WIDTH)
        {
            pyatnaskaSprite.setTextureRect(sf::IntRect(yCoord, xCoord, PUZZLE_WIDTH, PUZZLE_HEIGHT));// makes sprites for pyatnashki
            pyatnaskaSprite.setPosition(xCoord, yCoord + PUZZLE_WIDTH);
            allPuzzles.push_back(pyatnaskaSprite);// add pyatnashki to container
        }
    }
    emptyPuzzleSprite = allPuzzles[allPuzzles.size()-1];// get emptyPuzzle
    allPuzzles.pop_back();// delete this puzzle, after getting him
    RandomShuffleClass shuffle;
    std::vector<position> shuffledPosition = shuffle.getAllPositions();// unpackage random positons to shuffledPosition's
    // set random position's
    shuffle.MakeShuffle(allPuzzles);
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
            for (sf::Sprite pyatnaska : allPuzzles)// check all puzzles of containing mouse cursor
            {
                if (event.type == sf::Event::MouseButtonPressed)// if mouse button pressed 
                {
                    if (event.key.code == sf::Mouse::Left) // if it's left button
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

                        if (reloadButtonSprite.getGlobalBounds().contains(mouse.getPosition(window).x, mouse.getPosition(window).y)) \
                        {
                            steps = 0;
                            emptyPuzzleSprite.setPosition(EMPTY_PUZZLE_XCOORD, EMPTY_PUZZLE_YCOORD);
                            shuffle.MakeShuffle(allPuzzles);// make shuffle 
                            stepCounter.setString("STEPS: " + std::to_string(0));
                            clock.restart();// reset game time
                        }
                    }
                }
                idCounter++;// inc uniq id counter
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

        for (int i = 0; i < allPuzzles.size(); i++) // drawing all pyatnashka puzzle's
            window.draw(allPuzzles[i]);
        // stop drawing on the screen
        window.display();
    }
}