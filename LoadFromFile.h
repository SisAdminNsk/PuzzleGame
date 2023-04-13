#pragma once
#include <SFML/Graphics.hpp>

const int RELOAD_BUTTON_XCOORD = 10, RELOAD_BUTTON_YCOORD = 65;

class LoadFromFile
{
private:
    sf::Image pyatnaskiImage;
    sf::Texture pyatnaskiTexure;
    sf::Sprite pyatnaskaSprite;// for puzzle

    sf::Image backgroundImage;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;// for background

    sf::Image reloadButtonImage;
    sf::Texture reloadButtonTexture;
    sf::Sprite reloadButtonSprite;// for reloadButton

    sf::Font myFont;// for arial.ttf font 
     
public:
    sf::Sprite loadPyatnashkiSprite();
    sf::Sprite loadReloadButtonSprite();
    sf::Sprite loadBackgroundSprite();
    sf::Font loadFont();
};

