#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class GameMenu
{
private:
    const String filename_tx = "..//images//menu_background.jpg";
    const String filename_font = "..//fonts//better-vcr5.1.ttf";
    float menu_X;                   // Координаты меню по X
    float menu_Y;				    // Координаты меню по Y
    int menu_Step;                  // Расстояние между пунктами меню
    int max_menu;                   // Количество пунктов меню
    int size_font;                  // Размер шрифта
    int mainMenuSelected;           // Номер текущего пункта меню
    Font font;                      // Шрифт меню
    Text *mainMenu;
    Text game_name;
    Color menu_text_color = Color::White;    // Цвет пунктов меню
    Color chose_text_color = Color::Yellow;  // Цвет выбора пункта меню
    Color border_color = Color::Black;       // Цвет обводки текста пунктов меню
    Texture menuTx;                 // Фон меню 
    Sprite menuBacground;
    
public:
    void setInitText(Text& text, String str, float xpos, float ypos)
    {
        text.setFont(font);                 // шрифт
        text.setFillColor(menu_text_color); // цвет 
        text.setString(str);                // текст
        text.setCharacterSize(size_font);   // размер шрифта
        text.setPosition(xpos, ypos);       // координаты текстового объекта
        text.setOutlineThickness(3);        // толщина контура обводки текста
        text.setOutlineColor(border_color); // цвет контура обводки текста
    }
   
    GameMenu(float menux, float menuy, int index, String name[], int sizeFont = 60, int step = 80)
    {
        menu_X = menux;
        menu_Y = menuy;
        size_font = sizeFont;
        menu_Step = step;
        
        menuTx.loadFromFile(filename_tx); // Загрузка фона
        menuBacground.setTexture(menuTx);
        font.loadFromFile(filename_font);      // Загрузка шрифта
        max_menu = index;   // Количество єлементов меню

        game_name.setFont(font);
        game_name.setString("Rolling Balls");
        game_name.setFillColor(Color::Magenta);
        game_name.setCharacterSize(120);
        game_name.setPosition(1920/2 - game_name.getLocalBounds().width / 2, 40);
        game_name.setOutlineThickness(5);        // толщина контура обводки текста
        game_name.setOutlineColor(border_color); // цвет контура обводки текста
        
        mainMenu = new Text[max_menu];     // Динамический массив пунктов меню
        for (int i = 0, ypos = menu_Y; i < max_menu; i++, ypos += menu_Step)    // Выстраивание элементов меню
            setInitText(mainMenu[i], name[i], menu_X, ypos);
        
        mainMenuSelected = 0;   // Задание начального выбраного пункта меню
        mainMenu[mainMenuSelected].setFillColor(chose_text_color);  // цвет выбраного пункта меню
    }

    void MoveUp()   // Перемещение выбора меню вверх
    {
        mainMenuSelected--;  
        // подсвечиваем выбранный пункт меню
        if (mainMenuSelected >= 0) {
            mainMenu[mainMenuSelected].setFillColor(chose_text_color);
            mainMenu[mainMenuSelected + 1].setFillColor(menu_text_color);
        }
        else
        {
            mainMenu[0].setFillColor(menu_text_color);
            mainMenuSelected = max_menu - 1;
            mainMenu[mainMenuSelected].setFillColor(chose_text_color);
        }
    }

    void MoveDown()   // Перемещение выбора меню вниз
    {
        mainMenuSelected++;
        // подсвечиваем выбранный пункт меню
        if (mainMenuSelected < max_menu) {
            mainMenu[mainMenuSelected - 1].setFillColor(menu_text_color);
            mainMenu[mainMenuSelected].setFillColor(chose_text_color);
        }
        else
        {
            mainMenu[max_menu - 1].setFillColor(menu_text_color);
            mainMenuSelected = 0;
            mainMenu[mainMenuSelected].setFillColor(chose_text_color);
        }
    }
        
    // Цвет элементов игрового меню
    void setColorTextMenu(Color menColor, Color ChoColor, 
                          Color BordColor)
    {
        menu_text_color = menColor;   // цвет пунктов меню
        chose_text_color = ChoColor; // цвет выбраного пункта меню
        border_color = BordColor;    // цвет контура пунктов меню

        for (int i = 0; i < max_menu; i++) {
            mainMenu[i].setFillColor(menu_text_color);
            mainMenu[i].setOutlineColor(border_color);
        }

        mainMenu[mainMenuSelected].setFillColor(chose_text_color);
    }
    
    // Выравнивание пунктов меню по левому по правому по центру 
    void AlignMenu(int posx)
    {
        float nullx = 0;
        for (int i = 0; i < max_menu; i++) {
            switch (posx)
            {
            case 0:
                nullx = 0; // выравнивание по правому краю от установленных координат
                break;
            case 1:
                nullx = mainMenu[i].getLocalBounds().width;  // по левому краю
                break;
            case 2:
                nullx = mainMenu[i].getLocalBounds().width / 2;  // по центру
                break;
            }
            mainMenu[i].setPosition(mainMenu[i].getPosition().x - nullx, mainMenu[i].getPosition().y);
        }

    }

    void draw(RenderWindow *window)
    {
    window->draw(menuBacground);
    window->draw(game_name);        
    // перебираем для отрисовки существующие текстовые объекты пунктов меню 	
    for (int i = 0; i < max_menu; i++)
        window->draw(mainMenu[i]);
    }

    void drawMessage(RenderWindow *window, String winnerName, int balls)
    {
        Sprite spr(menuBacground);
        window->draw(spr);
        Text text;
        text.setString(L"Победил " + winnerName + L", забивший " + std::to_string(balls) + L" шаров,\nдля продолжения нажмите Enter");
        text.setCharacterSize(60);
        text.setFont(font);
        text.setFillColor(Color(237, 147, 0));
        int xPos, yPos;
        xPos = window->getSize().x/2 - text.getLocalBounds().width / 2;
        yPos = window->getSize().y/2 - text.getLocalBounds().height / 2;
        text.setPosition(xPos, yPos);
        window->draw(text);
    }

    int getSelectedMenuNumber() // Возвращает номер выбранного элемента меню
    {
        return mainMenuSelected;
    }
};
