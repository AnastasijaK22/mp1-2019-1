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
	Game_field &d;
	Snake& operator=(const Snake &s) {};
	// ����� - ��������
	bool nom_nom();
	// ����� - ����� �� ������ ���� ���� ��������� ��������� � �������� �����������
	bool to_be_or_not_to_be();
public:
	// ����������� �������������
	Snake(string s, Game_field &d1);
	// ����������� �������������
	Snake(Game_field &d1);
	// ����� - �������� ����������� ��������
	void change_direction(int _direction)
	{
		if (direction * (-1) != _direction)
			direction = _direction;
	}
	// ����� - �������������
	void Move();
	// ����� - ���� �� ������
	bool am_i_alive() const { return life; }
	// ����� - ������ ����� ������
	int snake_length() const { return length; }
	// ����� - ���������� ������
	void Draw_snake();
};