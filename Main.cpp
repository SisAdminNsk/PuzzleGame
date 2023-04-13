#include <iostream>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 800), "Pyatnashki");
    sf::Mouse mouse;// for mouse
    sf::Clock clock; // starts the clock

    sf::Image pyatnaskiImage;
    sf::Texture pyatnaskiTexure;
    sf::Sprite pyatnaskaSprite;// for pyatnashka 
    sf::Sprite emptyPuzzleSprite;// special serialized sprite for empty symbol

    sf::Image backgroundImage;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;// for background

    sf::Font myFont;// for arial.ttf font 
    sf::Text stepCounter;// showing counter of game steps
    sf::Text winnerMessage;// message for winner
    sf::Text timeMessage;// showing time 

    int steps = 0;// steps counter

    // Loading files for game //
    pyatnaskiImage.loadFromFile("Images/pyatnashki.png"); // load image from file
    pyatnaskiTexure.loadFromImage(pyatnaskiImage);// load texture from loaded before image
    pyatnaskaSprite.setTexture(pyatnaskiTexure);// set spirte from texture 

    backgroundImage.loadFromFile("Images/background.png");
    backgroundTexture.loadFromImage(backgroundImage);
    backgroundSprite.setTexture(backgroundTexture);

    myFont.loadFromFile("Fonts/arial.ttf");
    stepCounter.setFont(myFont);
    stepCounter.setCharacterSize(50);// set font size
    stepCounter.setPosition(10, 25);
    stepCounter.setString("STEPS: " + std::to_string(steps));// when game start counter = 0

    timeMessage.setFont(myFont);
    timeMessage.setCharacterSize(50);
    timeMessage.setPosition(450, 25);
    // End of loading game's files //
  
    sf::Time elapsedTime = clock.getElapsedTime();// lounch time;

    std::vector<sf::Sprite> allPuzzles;// will contains all pyatnashki sprite's
    for (int i = 0, yCoord = 0; i < 4; i++, yCoord += 160) 
    {
        for (int j = 0, xCoord = 0; j < 4; j++, xCoord += 160)
        {
            pyatnaskaSprite.setTextureRect(sf::IntRect(yCoord, xCoord, 160, 160));// makes sprites for pyatnashki
            pyatnaskaSprite.setPosition(xCoord, yCoord + 160);
            allPuzzles.push_back(pyatnaskaSprite);// add pyatnashki to container
        }
    }
    emptyPuzzleSprite = allPuzzles[allPuzzles.size()-1];// get emptyPuzzle
    allPuzzles.pop_back();// delete this puzzle, after getting him
    std::random_shuffle(allPuzzles.begin(),allPuzzles.end());// shake our pazzles
    // GAME CICLE 
    int uniqId = 0;
    int idCounter = 0;
    bool isMove = false;
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
                            if (abs(emptyPuzzleSprite.getPosition().x - pyatnaska.getPosition().x) <= 160 &&
                                abs(emptyPuzzleSprite.getPosition().y - pyatnaska.getPosition().y) <= 160)
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
        window.draw(backgroundSprite);// drawing background
        window.draw(stepCounter);// drawing steps
        window.draw(timeMessage);// drawing timer
        window.draw(emptyPuzzleSprite);// draw empty puzzle sprite

        for (int i = 0; i < allPuzzles.size(); i++) // drawing all pyatnashka puzzle's
            window.draw(allPuzzles[i]);
   
        window.display();
    }
}