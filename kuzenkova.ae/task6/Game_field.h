#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <time.h>

using namespace std;

enum Colors { BLACK = 0, BLUE = 16711680, GREEN = 65280, RED = 255, YELLOW = 65535, WHITE = 16777215 };
enum Directions { UP = -2, RIGHT = 1, DOWN = 2, LEFT = -1 };

extern HWND hwnd; 
extern HDC hdc; 

// ����� - �������
class Square
{
	COLORREF colors[5] = { BLACK, WHITE, BLUE, GREEN, RED };
	int left;
	int top;
	int a;
	int state;

public:
	// ����������� �������������
	Square(int x1, int y1, int _a = 10, int _state = 1) : left(x1), top(y1), a(_a), state(_state)
	{
		if (a <= 0)
			throw "������� ������ ������";
		if ((state < 0) || (state > 4))
			throw "������� ������� ���������";
	}
	// ����� - ���������� �������
	void draw() const;
	// ����� - �������� ����������
	void change_coordinate(int x1, int y1);
	// ����� - �������� ���������
	void change_state(int _state)
	{
		if ((state < 0) || (state > 4))
			throw "������� ������� ���������";
		state = _state;
	}
	// ����� - �������� ���������
	int get_state() const { return state; }
};

// ����� - ������� ����
class Game_field
{
	vector <vector <Square>> field;
	int N, M;
	int empty_squares;
	int x_nom;
	int y_nom;
	// ����� - ���������� ������ ����
	void set_size_field(int _N, int _M);
public:
	// ����������� �� ���������
	Game_field() : N(0), M(0), empty_squares(0), x_nom(-1), y_nom(-1) {}
	// ����������� �������������
	Game_field(int _N, int _M);
	// ����������� �������������
	Game_field(string s);
	// ����� - ������� ����� ����� � ����
	int get_sizeN() const { return N - 2; }
	// ����� - ������� ����� �������� � ����
	int get_sizeM() const { return M - 2; }
	// ����� - ���������� ��������� ������� ����
	void draw_square(int i, int j) const { field[j][i].draw(); }
	// ����� - ���������� ���� ���������
	void draw_field() const;
	// ����� - ���������� ���
	void draw_food() const { field[y_nom][x_nom].draw(); }
	// ����� - ��������� ���� 
	void clear_field();
	// ����� - �������� ��������� ���������� ��������
	void change_state(int i, int j, int _state);
	// ����� - �������� ��������� ���������� ��������
	int get_state(int i, int j) const { return field[j][i].get_state(); }
	// ����� - ������������� ���
	void generate_food();
};