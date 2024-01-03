#include "Ball.hpp"
#include <SFML/Graphics.hpp>
#include "BallLogic.hpp"
#include "Cue.hpp"
#include "GameMenu.hpp"
#include "PanelInfo.hpp"
#include "WindowAbout.hpp"
using namespace sf;

#define FPS 60

enum phases {menu, about, game_preparing, game_action, game_over};

void resetBalls(Ball *arr1[16], Cue *cue, int *balls1, int *balls2)
{
	for (int i = 0; i < 16; i++)
	{
		if (arr1[i] != nullptr)
		{
			arr1[i]->set_active();
			arr1[i]->set_speed(0, 0);
			setStartPos(arr1[i]);
		}
	}
	cue->update(arr1[0]);
	*balls1 = 0;
	*balls2 = 0;
}

int main() {
	phases phase = menu;
	
	// Объект, который является главным окном приложения
	RenderWindow window(VideoMode(1920, 1080), "Rolling Balls" /*, Style::Fullscreen*/);
	Texture backgr_tx;
	backgr_tx.loadFromFile("..//images//table.png");
	Sprite background(backgr_tx);
	Clock clock;
	Image icon;
	if (!icon.loadFromFile("..//images//icon.png"))
	{
		return 1;
	}
	window.setIcon(32, 32, icon.getPixelsPtr());

	//создание шаров
	Ball white_ball("..//images//white_ball.png",  0, 0, 0);
	Ball red_ball("..//images//white_ball.png", 0, 0, 1, Color::Red);
	Ball green_ball("..//images//white_ball.png", 0, 0, 2, Color::Green);
	Ball blue_ball("..//images//white_ball.png", 0, 0, 3, Color::Blue);
	Ball yellow_ball("..//images//white_ball.png", 0, 0, 4, Color::Yellow);
	Ball cyan_ball("..//images//white_ball.png", 0, 0, 5, Color::Cyan);
	Ball magenta_ball("..//images//white_ball.png", 0, 0, 6, Color::Magenta);
	Ball orange_ball("..//images//white_ball.png", 0, 0, 7, Color(255,165,0));
	Ball purple_ball("..//images//white_ball.png", 0, 0, 8, Color(128,0,128));
	Ball brown_ball("..//images//white_ball.png", 0, 0, 9, Color(165,42,42));
	Ball pink_ball("..//images//white_ball.png", 0, 0, 10, Color(255,192,203));
	Ball lightBlue_ball("..//images//white_ball.png", 0, 0, 11, Color(66,170,255));
	Ball lime_ball("..//images//white_ball.png", 0, 0, 12, Color(191, 255, 0));
	Ball apricot_ball("..//images//white_ball.png", 0, 0, 13, Color(153, 141, 222));
	Ball emerald_ball("..//images//white_ball.png", 0, 0, 14, Color(30, 120, 50));
	Ball black_ball("..//images//white_ball.png", 0, 0, 15, Color(0, 0, 0));
	
	Ball *arr[16] = {&white_ball, &red_ball, &green_ball, &blue_ball, &yellow_ball, &cyan_ball, &magenta_ball, &orange_ball, &purple_ball, &brown_ball, &pink_ball,
		&lightBlue_ball, &lime_ball, &apricot_ball, &emerald_ball, &black_ball};
	
	for (Ball *i : arr)
	{
		if (i != NULL)
		{
			setStartPos(i);
		}
	}

	
	String Name1 = L"Игрок1", Name2 = L"Игрок2", winner = Name1;
	int ballsOfFirst = 0, ballsOfSecond = 0;
	int winnerBalls, *scored = &ballsOfFirst;

	// создание кия
	Vector2i pixelPos;
	Vector2f pos;
	float vecX;
	float vecY;
	Cue cue1("..//images//cue.png", white_ball.get_pos().x, white_ball.get_pos().y);

	// создание меню
	String name_menu[] = { L"Старт", L"Об игре",L"Выход"};
	GameMenu menu(window.getSize().x / 2, window.getSize().y / 3, 3, name_menu, 100, 180);
	PanelInfo pinfo = PanelInfo(Name1, Name2, &ballsOfFirst, &ballsOfSecond);
	WindowAbout win_about = WindowAbout("..//images//rayan_gosling.jpg", "../images/about_background.jpg"); 
	
	// Установка цвета элементов пунктов меню
	menu.setColorTextMenu(Color(237, 147, 0), Color::Red, Color::Black);
	// выравнивание по центру пунктов меню 
	menu.AlignMenu(2);
	
	// Главный цикл приложения
	while (window.isOpen())
	{
		// Обработка очереди событий в цикле
		Event event;
		while (window.pollEvent(event))
		{
			// закрытие приложения
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case Keyboard::Escape:	// открытие меню
					phase = phases::menu;
					break;

				case Keyboard::Up:	// стрелка вверх
					if (phase == phases::menu)
						menu.MoveUp();
					break;

				case Keyboard::Down:	// стрелка вниз
					if (phase == phases::menu)
						menu.MoveDown();
					break;

				case Keyboard::Enter:	// клавиша Enter
					if (phase == phases::game_over)
					{
						phase = phases::menu;
					} else if (phase == phases::menu)
					{
						switch (menu.getSelectedMenuNumber())
						{
						case 0:	// начать игру
							phase = phases::game_preparing;
							resetBalls(arr, &cue1, &ballsOfFirst, &ballsOfSecond);
							if (!pinfo.getTurn())
							{
								pinfo.changeTurn(&scored);
							}
							break;
							
						case 1:	// о программе
							phase = phases::about;
							break;
								
						case 2: // выход из игры
							window.close();
							break;
						
						default:
							break;
						}
					} 
				}
			}
			if (event.type == Event::MouseButtonPressed)
			{
				//Если нажали ПКМ
				if (event.key.code == Mouse::Left && phase == phases::game_preparing) 
				{
					// Удар по шару
					hittingTheBall(pos.x, pos.y, &white_ball); 
					phase = phases::game_action;
				}
			}
		}

		if (phase == phases::game_preparing || phase == phases::game_action)
		{
			window.draw(background);
			pinfo.PanelDraw(&window);
			for (Ball *i : arr)
			{
				if (i != NULL && i->is_active())
				{
					i->draw_ball(&window);
				}
			}
		}
		
		switch (phase){
		case phases::about:
			win_about.Draw(&window);
			break;
		case phases::menu:
			menu.draw(&window);	// Отрисовка меню
			break;
		case game_preparing:
			// обновление кия
			cue1.update(&white_ball);
			pixelPos = Mouse::getPosition(window); // получение позиции курсора
			pos = window.mapPixelToCoords(pixelPos); // получение координат курсора
			vecX = pos.x - white_ball.get_pos().x - 20;
			vecY = pos.y - white_ball.get_pos().y - 20;
			cue1.set_cue_rotation(90 - (atan2(vecX, vecY)) * 180 / 3.14159265);
			cue1.draw_cue(&window);
			break;
		case game_action:
			if (updateBall(arr, scored))
			{
				phase = phases::game_preparing;
				pinfo.changeTurn(&scored);
			}
			break;
		case game_over:
			menu.drawMessage(&window, winner, winnerBalls);
			break;
		}

		if (!white_ball.is_active())
		{
			phase = phases::game_over;
			winner = (pinfo.getTurn()) ? Name2 : Name1;
			winnerBalls = (winner == Name1) ? ballsOfFirst : ballsOfSecond;
			resetBalls(arr, &cue1, &ballsOfFirst, &ballsOfSecond);
			if (!pinfo.getTurn())
				pinfo.changeTurn(&scored);
		}
		if (ballsOfFirst + ballsOfSecond == 15 && white_ball.is_active())
		{
			phase = phases::game_over;
			winner = (ballsOfFirst > ballsOfSecond) ? Name1 : Name2;
			winnerBalls = (winner == Name1) ? ballsOfFirst : ballsOfSecond;
			resetBalls(arr, &cue1, &ballsOfFirst, &ballsOfSecond);
			if (!pinfo.getTurn())
				pinfo.changeTurn(&scored);
		}
		
		// Отрисовка окна
		window.display();

		// Ограничение FPS
		Int32 frame_duration = clock.getElapsedTime().asMilliseconds();
		Int32 time_to_sleep = int(1000.f/FPS) - frame_duration;
		if (time_to_sleep > 0) {
			sleep(milliseconds(time_to_sleep));
		}
		clock.restart();
	}

	return 0;
}