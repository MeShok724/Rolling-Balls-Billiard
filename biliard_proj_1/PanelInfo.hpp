#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>

#define TEXT_SPACE1 50
#define X_START 10
#define Y_TOP 10
#define WINDOW_WIDTH 1920
#define CHAR_SIZE 50
#define THICKNESS 3

using namespace sf;
class PanelInfo
{
private:
    String name1, name2;
    Text arr[4];
    Font font;
    Color text_color_default = Color::White;    // Цвет игрока который не ходит
    Color text_color_choose = Color::Yellow;    // Цвет игрока который ходит
    Color border_color = Color::Black;          // Цвет обводки текста пунктов меню
    int *ballsFirst, *ballsSecond;
    bool isFirstTurn = true;

    void SetTextPos()
    {
        arr[0].setString(name1);
        arr[2].setString(name2);
        arr[1].setString(std::to_string(*ballsFirst));
        arr[3].setString(std::to_string(*ballsSecond));
        arr[0].setPosition(X_START, Y_TOP);
        int x = arr[0].getPosition().x + arr[0].getLocalBounds().width + TEXT_SPACE1;
        arr[1].setPosition(x, Y_TOP);
        x = WINDOW_WIDTH - X_START - arr[3].getLocalBounds().width;
        arr[3].setPosition(x, Y_TOP);
        x = arr[3].getPosition().x - TEXT_SPACE1 - arr[2].getLocalBounds().width;
        arr[2].setPosition(x, Y_TOP);
    }
    
public:  
    PanelInfo(String nameFirst, String nameSecond, int *first, int *second) //инициализация панели
    {
        name1 = nameFirst;
        name2 = nameSecond;
        ballsFirst = first;
        ballsSecond = second;
        SetTextPos();
        font.loadFromFile("..//fonts//better-vcr5.1.ttf");
        for(int i = 0; i < 4;i++)
        {
            arr[i].setFont(font);
            arr[i].setCharacterSize(CHAR_SIZE);
            arr[i].setOutlineThickness(THICKNESS);
            arr[i].setOutlineColor(border_color);
        }
    }
    
    void PanelDraw(RenderWindow *window)   //отрисовка панели
    {
        SetTextPos();
        for(int i = 0; i < 2;i++)
        {
            arr[i].setFillColor((isFirstTurn) ? text_color_choose : text_color_default);
            window->draw(arr[i]);
        }
        for(int i = 2; i < 4;i++)
        {
            arr[i].setFillColor((isFirstTurn) ? text_color_default : text_color_choose);
            window->draw(arr[i]);
        }
    }
    
    bool getTurn()
    {
        return isFirstTurn;
    }
    
    void changeTurn(int **scored)
    {
        if (isFirstTurn)
        {
            isFirstTurn = false;
            *scored = ballsSecond;
        } else
        {
            isFirstTurn = true;
            *scored = ballsFirst;
        }
    }    
};
