#pragma once
#include <codecvt>
#include <fstream>
#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <locale>

#define TOP 20
#define CENTER 1920/2
#define INDENT 20

using namespace sf;

class WindowAbout
{
private:
    Sprite background, image;
    Texture tx, tx1;

    
public:
    WindowAbout(String file_image_name, String file_back_name)
    {
      
        tx.loadFromFile(file_image_name);
        image.setTexture(tx);
        tx1.loadFromFile(file_back_name);
        background.setTexture(tx1);
        setImage();
    }

    int setImage()
    {
        background.setPosition(0,0);
        image.setPosition(CENTER - image.getLocalBounds().width/2, 454);
        return 0;
    }

    void Draw(RenderWindow *window)
    {
        window->draw(background);
        window->draw(image);
    }
    
};
