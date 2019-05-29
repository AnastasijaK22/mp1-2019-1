#pragma once
#include "Snake.h"
#include <conio.h>

class Control
{
	Control() {}
	static bool isDown(char c)
	{
		if ((c == 235) || (c == 115) || (c == 80) || (c == -21) || (c == -101) || (c == 83))
			return true;
		return false;
	}
	static bool isUp(char c)
	{
		if ((c == 230) || (c == 119) || (c == 72) || (c == -26) || (c == -106) || (c == 87))
			return true;
		return false;
	}
	static bool isRight(char c)
	{
		if ((c == 162) || (c == 100) || (c == 77) || (c == -94) || (c == -126) || (c == 68))
			return true;
		return false;
	}
	static bool isLeft(char c)
	{
		if ((c == 228) || (c == 97) || (c == 75) || (c == -28) || (c == -108) || (c == 65))
			return true;
		return false;
	}
public:
	static int determine_direction(char c)
	{
		if (isDown(c)) return DOWN;
		if (isRight(c)) return RIGHT;
		if (isLeft(c)) return LEFT;
		if (isUp(c)) return UP;
		return 0;
	}
};

// класс игра
class The_Lord_of_the_Snakes
{
	int sizeN, sizeM;
	int win_length;
	int levels_campany[5];
	// метод - установить размер
	void set_size(int N, int M);
	// метод - установить победную длину
	void set_win_length(int l);
	// метод - запустить кампанию
	void campany();
	// метод - запустить обычную игру
	void common();
	// метод - игра
	bool game(Game_field &d, Snake &h);
public:
	// конструктор по умолчанию
	The_Lord_of_the_Snakes();
	// метод - запустить меню
	void menu();
};