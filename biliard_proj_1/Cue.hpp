#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.hpp"
using namespace sf;

class Cue
{
private:
    Texture tx;
    Sprite spr;
public:
    void set_cue_rotation(float angle)
    {
        spr.setRotation(angle);
    }

    Cue(std::string image, float x_start, float y_start)
    {
        tx.loadFromFile(image);
        spr.setTexture(tx);
        spr.setOrigin(spr.getTextureRect().width + 60, spr.getTextureRect().height / 2);
        spr.setPosition(x_start + 20, y_start + 20);     //(x_start - (spr.getTextureRect().width + 20), y_start - spr.getTextureRect().height / 2);
    }

    void update(Ball *ball)
    {
        spr.setPosition(ball->get_pos().x + 20, ball->get_pos().y + 20);
        spr.setRotation(0);
    }
    
    // Отрисовка кия
    void draw_cue(RenderWindow* wind)
    {
        wind->draw(spr);
    }
};
