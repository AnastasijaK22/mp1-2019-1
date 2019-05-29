#pragma once
#include "Game_field.h"

// класс змейка
class Snake
{
	vector <int> x;
	vector <int> y;
	int length;
	bool life;
	int direction;
	int x_tail;
	int y_tail;
	Game_field &snake_field;
	Snake& operator=(const Snake &s) {};
	// метод - покушать
	bool food_ahead();
	// метод - будет ли змейка жива если продолжит двигаться в заданном направлении
	bool obstacle_ahead();
public:
	// конструктор инициализатор
	Snake(string s, Game_field &_snake_field);
	// конструктор инициализатор
	Snake(Game_field &_snake_field);
	// метод - изменить направление движения
	void change_direction(int _direction)
	{
		if (direction * (-1) != _direction)
			direction = _direction;
	}
	// метод - переместиться
	void move();
	// метод - жива ли змейка
	bool am_i_alive() const { return life; }
	// метод - узнать длину змейки
	int snake_length() const { return length; }
	// метод - нарисовать змейку
	void redraw_snake();
};