#include "Game_snake.h"

void The_Lord_of_the_Snakes::set_size(int N, int M)
{
	if ((N < 10) || (N > 70) || (M < 10) || (M > 70))
		throw 1;
	sizeN = N;
	sizeM = M;
}

void The_Lord_of_the_Snakes::set_win_length(int l)
{
	if ((l < 6) || (l > sizeN*sizeM / 2))
		throw 2;
	win_length = l;
}

void The_Lord_of_the_Snakes::Campany()
{
	while (1 > 0)
	{
		system("cls");
		int a;
		for (int i = 0; i < 5; i++)
			if (campany[i] == 1)
				cout << "        level " << i + 1 << endl;
		cout << "        назад - 0" << endl;
		cout << "  ";
		while (1 > 0)
		{
			while (1 > 0)
			{
				if (_kbhit())
				{
					char c;
					c = _getch();
					a = c - 48;
					if ((a == 1) || (a == 2) || (a == 0) || (a == 3) || (a == 4) || (a == 5))
						break;
				}
			}
			if (a == 0)
				break;
			if (campany[a - 1] == 1)
				break;
		}
		if (a == 0) break;
		string temp = "level";
		string temp2 = ".txt";
		string number = to_string(a);
		temp = temp + number + temp2;
		system("cls");
		Game_field d(temp);
		Snake h(temp, d);
		win_length = 15 + 5 * a;
		bool flag = Game(d, h);
		system("cls");
		if (flag == false)
			cout << "    Ты проиграл салага!" << endl;
		else
		{
			cout << "    Ты победил салага!" << endl;
			if (a != 5)
				campany[a] = 1;
		}
		cout << "Хотите продолжить кампанию? 1 -да, 0 -нет" << endl;
		while (1 > 0)
		{
			if (_kbhit())
			{
				int c = _getch();
				a = c - 48;
				if ((a == 1) || (a == 0))
					break;
			}
		}
		d.Clear_field();
		if (a == 0) break;
	}
}

void The_Lord_of_the_Snakes::Common()
{
	system("cls");
	cout << " Установите размер игрового окна (от 10 до 70)" << endl;
	int n, m;
	int l;
	bool temp = true;
	do
	{
		temp = true;
		try
		{
			cin >> n >> m;
			set_size(n, m);
			cout << "Введи победную длину" << endl;
			cin >> l;
			set_win_length(l);
		}
		catch (int s)
		{
			cout << "Введены неверно размеры" << endl;;
			temp = false;
		}
	} while (!temp);
	Game_field d(sizeN, sizeM);
	Snake h(d);
	bool flag = Game(d, h);
	system("cls");
	if (flag == false)
		cout << "    Ты проиграл салага!" << endl;
	else
	{
		cout << "    Ты победил салага!" << endl;
	}
	_getch();
	d.Clear_field();
}

bool The_Lord_of_the_Snakes::Game(Game_field &d, Snake &h)
{
	system("cls");
	COORD position = { 0,0 };
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	d.generate_nom_nom();
	int direction = 0;
	char c;
	d.Draw_field();
	cout << "Для начала нажмите любую клавишу" << endl;
	_getch();
	_getch();
	SetConsoleCursorPosition(hConsole, position);
	cout << "                                " << endl;
	SetConsoleCursorPosition(hConsole, position);
	int l = h.snake_length();
	cout << "Текущая длина змейки: " << l << endl;
	cout << "Победная длина: " << win_length << endl;
	while ((h.am_i_alive()) && (h.snake_length() < win_length))
	{
		if (_kbhit())
		{
			c = _getch();
			direction = Control::determine_direction(c);
			if (direction != 0)
				h.change_direction(direction);
		}
		Sleep(175);
		h.Move();
		d.Draw_nom_nom();
		h.Draw_snake();
		if (l != h.snake_length())
		{
			SetConsoleCursorPosition(hConsole, position);
			l++;
			cout << "Текущая длина змейки: " << l << endl;
			cout << "Победная длина: " << win_length << endl;
		}
	}
	if (!h.am_i_alive())
		return false;
	else
		return true;
}

The_Lord_of_the_Snakes::The_Lord_of_the_Snakes()
{
	win_length = 0;
	sizeN = 0;
	sizeM = 0;
	campany[0] = 1;
	for (int i = 1; i < 5; i++)
		campany[i] = 0;
}
void The_Lord_of_the_Snakes::Menu()
{
	while (1 > 0)
	{
		system("cls");
		cout << "      Добро пожаловать!       " << endl;
		cout << endl;
		cout << "      Обычная игра - 1        " << endl;
		cout << "      Кампания     - 2        " << endl;
		cout << "      Выход - 0               " << endl;
		char a;
		cout << "      ";
		while (1 > 0)
		{
			if (_kbhit())
			{
				a = _getch();
				if ((a == '1') || (a == '2') || (a == '0'))
					break;
			}
		}
		if (a == '2')
			Campany();
		if (a == '1')
			Common();
		if (a == '0')
			break;
	}
}