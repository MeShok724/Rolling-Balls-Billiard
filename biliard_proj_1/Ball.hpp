#pragma once
#include <functional>
#include <string.h>
#include <SFML/Graphics.hpp>
using namespace sf;
class Ball
{
private:
	int number;
	float dx, dy;
	Texture tx;
	Sprite spr;
	bool IsActive;
public:
	
	 //Инициализация шара
	 Ball(std::string image, float x_start, float y_start, int numb, Color color = Color::White)
	 {
	 	tx.loadFromFile(image);
	 	spr.setTexture(tx);
	 	spr.setColor(color);
	 	dx = 0;
	 	dy = 0;
	 	spr.setPosition(x_start, y_start);
	 	spr.setScale((float)0.1, (float)0.1);
	 	number = numb;
	 	IsActive = true;
	 }	

	// Отрисовка шара
	void draw_ball(RenderWindow* wind)	{	wind->draw(spr);}
	
	Vector2f get_pos()	{
		 return spr.getPosition();
	 }
	
	Vector2f get_speed()	{
	 	Vector2f vec(dx, dy);
	 	return vec;
	 }

	float get_diag_speed()
	 {
	 	float speed = dx*dx + dy*dy;
	 	return sqrt(speed);
	 }
	
	void set_pos(float x, float y)	{	spr.setPosition(x, y);}
	
	void set_speed(float x, float y) {
	 	dx = x;
	 	dy = y;
	 }
	
	bool is_active()	{	return IsActive;}
	
	void set_active()	{	IsActive = true;}
	
	void set_not_active()	{	IsActive = false;}
	
	int get_number()	{	return number;}

	void move_ball(float x, float y)	{	spr.move(x, y);}

	void invert_dx()	{	dx = -dx;}
	void invert_dy()	{	dy = -dy;}
	
	void set_friction(float fric)
	 {
	 	dx *= fric;
	 	dy *= fric;
	 }

	void stop()	{	dx = 0; dy = 0;}
};


