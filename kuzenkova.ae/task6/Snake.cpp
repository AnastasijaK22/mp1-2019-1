#include "Snake.h"

Snake::Snake(string s, Game_field &d1) : d(d1)
{
	ifstream fin(s);
	if (!fin.is_open())
		throw "нет такого файла\n";
	int x1;
	int y1;
	fin >> x1;
	fin >> y1;
	life = true;
	length = 5;
	direction = LEFT;
	x.push_back(x1);
	y.push_back(y1);
	d.change_state(x1, y1, 4);
	for (int i = 1; i < 5; i++)
	{
		x.push_back(x1 + i);
		y.push_back(y1);
		d.change_state(x1 + i, y1, 3);
	}
	x_tail = x1 + 5;
	y_tail = y1;
}

Snake::Snake(Game_field &d1) : d(d1)
{
	srand(time(NULL));
	life = true;
	length = 5;
	direction = LEFT;
	int N = d.get_sizeN();
	int M = d.get_sizeM();
	int temp_x = 2 + rand() % (M - 6);
	int temp_y = 2 + rand() % (N - 2);
	x.push_back(temp_x);
	y.push_back(temp_y);
	d.change_state(temp_x, temp_y, 4);
	for (int i = 1; i < 5; i++)
	{
		x.push_back(temp_x + i);
		y.push_back(temp_y);
		d.change_state(temp_x + i, temp_y, 3);
	}
	x_tail = temp_x + 5;
	y_tail = temp_y;
}

bool Snake::nom_nom()
{
	if (d.get_state(x[0] + direction % 2, y[0] + direction / 2) == 2)
		return true;
	return false;
}

bool Snake::to_be_or_not_to_be()
{
	if (d.get_state(x[0] + direction % 2, y[0] + direction / 2) == 0)
		return false;
	if ((d.get_state(x[0] + direction % 2, y[0] + direction / 2) == 3) && ((x[0] + direction % 2 != x[length - 1]) || (y[0] + direction / 2 != y[length - 1])))
		return false;
	return true;
}

void Snake::Move()
{
	if (to_be_or_not_to_be() == true)
	{
		x_tail = x[length - 1];
		y_tail = y[length - 1];
		bool flag = nom_nom();
		d.change_state(x[0], y[0], 3);
		for (int i = length - 1; i > 0; i--)
		{
			x[i] = x[i - 1];
			y[i] = y[i - 1];
		}
		x[0] += direction % 2;
		y[0] += direction / 2;
		d.change_state(x[0], y[0], 4);
		if (flag == true)
		{
			x.push_back(x_tail);
			y.push_back(y_tail);
			length++;
			d.generate_nom_nom();
		}
		else
			d.change_state(x_tail, y_tail, 1);
	}
	else
		life = false;
}

void Snake::Draw_snake()
{
	//d.Draw_nom_nom();
	d.Draw_square(x_tail, y_tail);
	d.Draw_square(x[0], y[0]);
	d.Draw_square(x[1], y[1]);
}
