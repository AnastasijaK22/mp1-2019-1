#include "Snake.h"

Snake::Snake(string s, Game_field &_snake_field) : snake_field(_snake_field)
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
	snake_field.change_state(x1, y1, 4);
	for (int i = 1; i < 5; i++)
	{
		x.push_back(x1 + i);
		y.push_back(y1);
		snake_field.change_state(x1 + i, y1, 3);
	}
	x_tail = x1 + 5;
	y_tail = y1;
}

Snake::Snake(Game_field &_snake_field) : snake_field(_snake_field)
{
	srand(time(NULL));
	life = true;
	length = 5;
	direction = LEFT;
	int N = snake_field.get_sizeN();
	int M = snake_field.get_sizeM();
	int temp_x = 2 + rand() % (M - 6);
	int temp_y = 2 + rand() % (N - 2);
	x.push_back(temp_x);
	y.push_back(temp_y);
	snake_field.change_state(temp_x, temp_y, 4);
	for (int i = 1; i < 5; i++)
	{
		x.push_back(temp_x + i);
		y.push_back(temp_y);
		snake_field.change_state(temp_x + i, temp_y, 3);
	}
	x_tail = temp_x + 5;
	y_tail = temp_y;
}

bool Snake::food_ahead()
{
	if (snake_field.get_state(x[0] + direction % 2, y[0] + direction / 2) == 2)
		return true;
	return false;
}

bool Snake::obstacle_ahead()
{
	if (snake_field.get_state(x[0] + direction % 2, y[0] + direction / 2) == 0)
		return false;
	if ((snake_field.get_state(x[0] + direction % 2, y[0] + direction / 2) == 3) && ((x[0] + direction % 2 != x[length - 1]) || (y[0] + direction / 2 != y[length - 1])))
		return false;
	return true;
}

void Snake::move()
{
	if (obstacle_ahead() == true)
	{
		x_tail = x[length - 1];
		y_tail = y[length - 1];
		bool flag = food_ahead();
		snake_field.change_state(x[0], y[0], 3);
		for (int i = length - 1; i > 0; i--)
		{
			x[i] = x[i - 1];
			y[i] = y[i - 1];
		}
		x[0] += direction % 2;
		y[0] += direction / 2;
		snake_field.change_state(x[0], y[0], 4);
		if (flag == true)
		{
			x.push_back(x_tail);
			y.push_back(y_tail);
			length++;
			snake_field.generate_food();
		}
		else
			snake_field.change_state(x_tail, y_tail, 1);
	}
	else
		life = false;
}

void Snake::redraw_snake()
{
	snake_field.draw_square(x_tail, y_tail);
	snake_field.draw_square(x[0], y[0]);
	snake_field.draw_square(x[1], y[1]);
}
