#include "LoadFromFile.h"

sf::Sprite LoadFromFile::loadPyatnashkiSprite()
{
    pyatnaskiImage.loadFromFile("Images/pyatnashki.png"); // load image from file
    pyatnaskiTexure.loadFromImage(pyatnaskiImage);// load texture from loaded before image
    pyatnaskaSprite.setTexture(pyatnaskiTexure);// set spirte from texture 

    return pyatnaskaSprite;
}

sf::Sprite LoadFromFile::loadReloadButtonSprite()
{
    reloadButtonImage.loadFromFile("Images/reloadButton.png");
    reloadButtonTexture.loadFromImage(reloadButtonImage);
    reloadButtonSprite.setTexture(reloadButtonTexture);
    reloadButtonSprite.setPosition(RELOAD_BUTTON_XCOORD, RELOAD_BUTTON_YCOORD);// position of reloadButton

    return reloadButtonSprite;
}

sf::Sprite LoadFromFile::loadBackgroundSprite()
{
    backgroundImage.loadFromFile("Images/background.png");
    backgroundTexture.loadFromImage(backgroundImage);
    backgroundSprite.setTexture(backgroundTexture);

    return backgroundSprite;
}

sf::Font LoadFromFile::loadFont()
{
    myFont.loadFromFile("Fonts/arial.ttf");
    return myFont;
}
