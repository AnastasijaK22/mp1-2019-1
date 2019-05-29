#include "Game_field.h"

void Square::draw() const
{
	RECT kletochka;
	kletochka.left = left;
	kletochka.top = top;
	kletochka.right = left + a;
	kletochka.bottom = top + a;
	HBRUSH brush = CreateSolidBrush(colors[state]);
	FillRect(hdc, &kletochka, brush);
	DeleteObject(brush);
}

void Square::change_coordinate(int x1, int y1)
{
	left = left + x1;
	top += y1;
}

Game_field::Game_field(int _N, int _M)
{
	int x0 = 70;
	int y0 = 70;
	vector <Square> temp;
	for (int i = 0; i < _M + 2; i++)
	{
		temp.push_back(Square(x0 + 10 * i, y0, 10, 0));
	}
	field.push_back(temp);
	for (int j = 0; j < _N; j++)
	{
		vector <Square> temp1;
		temp1.push_back(Square(x0, y0 + 10 * (j + 1), 10, 0));
		for (int i = 1; i < _M + 1; i++)
			temp1.push_back(Square(x0 + 10 * i, y0 + 10 * (j + 1), 10, 1));
		temp1.push_back(Square(x0 + 10 * (_M + 1), y0 + 10 * (j + 1), 10, 0));
		field.push_back(temp1);
	}
	vector <Square> temp2;
	for (int i = 0; i < _M + 2; i++)
	{
		temp2.push_back(Square(x0 + 10 * i, y0 + 10 * (_N + 1), 10, 0));
	}
	field.push_back(temp2);
	N = _N + 2;
	M = _M + 2;
	empty_squares = _N * _M;
}

Game_field::Game_field(string s)
{
	ifstream fin(s);
	if (!fin.is_open())
		throw "нет такого файла\n";
	int x = 0, y = 0;
	int _N;
	int temp;
	fin >> temp;
	fin >> temp;
	fin >> _N;
	int _M;
	fin >> _M;
	set_size_field(_N, _M);
	int j;
	fin >> j;
	for (int i = 0; i < j; i++)
	{
		fin >> x;
		fin >> y;
		change_state(x, y, 0);
	}
}

void Game_field::set_size_field(int _N, int _M)
{
	Game_field temp(_N, _M);
	*this = temp;
}

void Game_field::draw_field() const
{
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			draw_square(i, j);
}

void Game_field::clear_field()
{
	int temp = 0;
	if (N >= M)
		temp = N;
	else temp = M;
	Square a(70, 70, (temp) * 10);
	a.draw();
}

void Game_field::change_state(int i, int j, int _state)
{
	if ((field[j][i].get_state() == 1) && (_state != 1))
		empty_squares--;
	if ((field[j][i].get_state() != 1) && (_state == 1))
		empty_squares++;
	field[j][i].change_state(_state);
}

void Game_field::generate_food()
{
	srand(time(NULL));
	int k = 1 + rand() % (empty_squares);
	int x = 1;
	for (int j = 0; j < N; j++)
	{
		int i;
		for (i = 0; i < M; i++)
			if (get_state(i, j) == 1)
				if (x != k)
					x++;
				else
				{
					change_state(i, j, 2);
					x_nom = i;
					y_nom = j;
					break;
				}
		if (i != M)
			break;
	}
}