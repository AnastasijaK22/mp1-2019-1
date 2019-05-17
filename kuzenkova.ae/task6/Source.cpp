#include <windows.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <vector>
#include <string>
#include <locale.h>
#include <time.h>

using namespace std;

enum Colors { BLACK = 0, BLUE = 16711680, GREEN = 65280, RED = 255, YELLOW = 65535, WHITE = 16777215 };
enum Directions { UP = -2, RIGHT = 1, DOWN = 2, LEFT = -1 };

HWND hwnd = GetConsoleWindow();
HDC hdc = GetDC(hwnd);

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
	void Draw() const;
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
	void Draw_square(int i, int j) const { field[j][i].Draw(); }
	// метод - нарисовать поле полностью
	void Draw_field() const;
	// метод - нарисовать еду
	void Draw_nom_nom() const { field[y_nom][x_nom].Draw(); }
	// метод - закрасить поле 
	void Clear_field();
	// метод - изменить состояние выбранного квадрата
	void change_state(int i, int j, int _state);
	// метод - получить состояние выбранного квадрата
	int get_state(int i, int j) const { return field[j][i].get_state(); }
	// метод - сгенерировать еду
	void generate_nom_nom();
};

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
	Game_field &d;
	Snake& operator=(const Snake &s){};
	// метод - покушать
	bool nom_nom();
	// метод - будет ли змейка жива если продолжит двигаться в заданном направлении
	bool to_be_or_not_to_be();
public:
	// конструктор инициализатор
	Snake(string s, Game_field &d1) : d(d1)
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
	// конструктор инициализатор
	Snake(Game_field &d1) : d(d1)
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
	// метод - изменить направление движения
	void change_direction(int _direction)
	{
		if (direction * (-1) != _direction)
			direction = _direction;
	}
	// метод - переместиться
	void Move();
	// метод - жива ли змейка
	bool am_i_alive() const { return life; }
	// метод - узнать длину змейки
	int snake_length() const { return length; }
	// метод - нарисовать змейку
	void Draw_snake();
};

class Upravlenie
{
	Upravlenie() {}
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
	static int napravlenie(char c)
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
	int campany[5];
	bool game_is_set;
	// метод - установить размер
	void set_size(int N, int M);
	// метод - установить победную длину
	void set_win_length(int l);
	// метод - запустить кампанию
	void Campany();
	// метод - запустить обычную игру
	void Common();
	// метод - игра
	bool Game(Game_field &d, Snake &h);
public:
	// конструктор по умолчанию
	The_Lord_of_the_Snakes();
	// метод - запустить меню
	void Menu();
};

void Square::Draw() const
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

void Game_field::Draw_field() const
{
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			Draw_square(i, j);
}

void Game_field::Clear_field()
{
	int temp = 0;
	if (N >= M)
		temp = N;
	else temp = M;
	Square a(70, 70, (temp) * 10);
	a.Draw();
}

void Game_field::change_state(int i, int j, int _state)
{
	if ((field[j][i].get_state() == 1) && (_state != 1))
		empty_squares--;
	if ((field[j][i].get_state() != 1) && (_state == 1))
		empty_squares++;
	field[j][i].change_state(_state);
}

void Game_field::generate_nom_nom()
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
	for (int i = 0; i < length - 1; i++)
		if ((d.get_state(x[0] + direction % 2, y[0] + direction / 2) == 3) && (x[0] + direction % 2 == x[i]) && (y[0] + direction / 2 == y[i]))
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
	d.Draw_nom_nom();
	d.Draw_square(x[0], y[0]);
	d.Draw_square(x[1], y[1]);
	d.Draw_square(x_tail, y_tail);
}

void The_Lord_of_the_Snakes::set_size(int N, int M)
{
	if ((N < 10) || (N > 200) || (M < 10) || (M > 200))
		throw 1;
	sizeN = N;
	sizeM = M;
}

void The_Lord_of_the_Snakes::set_win_length(int l)
{
	if ((l < 6) || (l > sizeN*sizeM/2))
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
	cout << " Установите размер игрового окна (от 10 до 200)" << endl;
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
	SetConsoleCursorPosition(hConsole, position);
	cout << "                                " << endl;
	SetConsoleCursorPosition(hConsole, position);
	int l = h.snake_length();
	cout << "Текущая длина змейки: " << l << endl;
	cout << "Победная длина: " << win_length << endl;
	while ((h.am_i_alive()) && (h.snake_length() < win_length))
	{

		int direction;
		if (_kbhit())
		{
			c = _getch();
			direction = Upravlenie::napravlenie(c);
			if (direction != 0)
				h.change_direction(direction);
		}
		Sleep(175);
		h.Move();
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
	game_is_set = false;
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

int main()
{
	setlocale(LC_ALL, "Rus");
	HANDLE hWnd = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD bufferSize = { 80, 50 };
	SetConsoleScreenBufferSize(hwnd, bufferSize);
	MoveWindow(hwnd, 50, 50, 1000, 1000, FALSE);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("color F0");
	The_Lord_of_the_Snakes o;
	o.Menu();
	Sleep(100);
	std::cin.ignore();
	return 0;
}