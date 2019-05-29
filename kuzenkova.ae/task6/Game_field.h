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

// класс - Квадрат
class Square
{
	COLORREF colors[5] = { BLACK, WHITE, BLUE, GREEN, RED };
	int left;
	int top;
	int a;
	int state;

public:
	// конструктор инициализатор
	Square(int x1, int y1, int _a = 10, int _state = 1) : left(x1), top(y1), a(_a), state(_state)
	{
		if (a <= 0)
			throw "Неверно введен размер";
		if ((state < 0) || (state > 4))
			throw "Неверно введено состояние";
	}
	// метод - нарисовать квадрат
	void draw() const;
	// метод - изменить координаты
	void change_coordinate(int x1, int y1);
	// метод - изменить состояние
	void change_state(int _state)
	{
		if ((state < 0) || (state > 4))
			throw "Неверно введено состояние";
		state = _state;
	}
	// метод - получить состояние
	int get_state() const { return state; }
};

// класс - игровое поле
class Game_field
{
	vector <vector <Square>> field;
	int N, M;
	int empty_squares;
	int x_nom;
	int y_nom;
	// метод - установить размер поля
	void set_size_field(int _N, int _M);
public:
	// конструктор по умолчанию
	Game_field() : N(0), M(0), empty_squares(0), x_nom(-1), y_nom(-1) {}
	// конструктор инициализатор
	Game_field(int _N, int _M);
	// конструктор инициализатор
	Game_field(string s);
	// метод - вернуть число строк в поле
	int get_sizeN() const { return N - 2; }
	// метод - вернуть число столбцов в поле
	int get_sizeM() const { return M - 2; }
	// метод - нарисовать выбранный квадрат поля
	void draw_square(int i, int j) const { field[j][i].draw(); }
	// метод - нарисовать поле полностью
	void draw_field() const;
	// метод - нарисовать еду
	void draw_food() const { field[y_nom][x_nom].draw(); }
	// метод - закрасить поле 
	void clear_field();
	// метод - изменить состояние выбранного квадрата
	void change_state(int i, int j, int _state);
	// метод - получить состояние выбранного квадрата
	int get_state(int i, int j) const { return field[j][i].get_state(); }
	// метод - сгенерировать еду
	void generate_food();
};