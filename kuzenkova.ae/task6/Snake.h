#pragma once
#include "Game_field.h"

// ����� ������
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
	// ����� - ��������
	bool food_ahead();
	// ����� - ����� �� ������ ���� ���� ��������� ��������� � �������� �����������
	bool obstacle_ahead();
public:
	// ����������� �������������
	Snake(string s, Game_field &_snake_field);
	// ����������� �������������
	Snake(Game_field &_snake_field);
	// ����� - �������� ����������� ��������
	void change_direction(int _direction)
	{
		if (direction * (-1) != _direction)
			direction = _direction;
	}
	// ����� - �������������
	void move();
	// ����� - ���� �� ������
	bool am_i_alive() const { return life; }
	// ����� - ������ ����� ������
	int snake_length() const { return length; }
	// ����� - ���������� ������
	void redraw_snake();
};