#include <conio.h>
#include <locale.h>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

class Function_tab
{
	double left_bound;
	double right_bound;
	int points;
	double (*function)(double);
	double **values;
	bool func_set;
	bool it_count;
public:
	// конструктор по умолчанию
	Function_tab(); 
	// конструктор копирования
	Function_tab(const Function_tab &c);
	// оператор присваивания
	Function_tab& operator=(const Function_tab &c);
	// метод - установить функцию
	void set_function(double(*func)(double));
	// метод - установить число точек
	void set_points(int _points);
	// метод - вывести число точек
	void print_points();
	// метод - установить границы отрезка
	void set_bounds(double left, double right);
	// метод - вывод границ отрезка
	void print_bounds();
	// метод - табулирование
	void tabulation();
	// метод - вывести результаты табулирования
	void print_tab();
	// метод - вывести результаты табулирования в файл
	void filePrint_tab(char *name = "task3.txt");
	// деструктор
	~Function_tab();
};
// реализации методов класса
Function_tab::Function_tab()
{
	left_bound = 0;
	right_bound = 1;
	points = 2;
	function = nullptr;
	func_set = false;
	it_count = false;
	values = new double *[2];
	for (int i = 0; i < 2; i++)
		values[i] = new double[points];
}
Function_tab::Function_tab(const Function_tab &c)
{
	left_bound = c.left_bound;
	right_bound = c.right_bound;
	points = c.points;
	function = c.function;
	func_set = c.func_set;
	it_count = c.it_count;
	values = new double*[2];
	for (int i = 0; i < 2; i++)
	{
		values[i] = new double[points];
		if (it_count)
			for (int j = 0; j < points; j++)
				values[i][j] = c.values[i][j];
	}
}
Function_tab& Function_tab::operator=(const Function_tab &c)
{
	left_bound = c.left_bound;
	right_bound = c.right_bound;
	points = c.points;
	function = c.function;
	func_set = c.func_set;
	it_count = c.it_count;
	for (int i = 0; i < 2; i++)
		delete[] values[i];
	for (int i = 0; i < 2; i++)
	{
		values[i] = new double[points];
		if (it_count)
		{
			for (int j = 0; j < points; j++)
				values[i][j] = c.values[i][j];
		}
	}
	return *this;
}
void Function_tab::set_function(double(*func)(double))
{
	function = func;
	func_set = true;
	it_count = false;
}
void Function_tab::set_points(int _points)
{
	if (_points < 2)
		throw "Неправильно введено число точек\n";
	points = _points;
	for (int i = 0; i < 2; i++)
	{
		delete[] values[i];
		values[i] = new double[points];
	}
	it_count = false;
}
void Function_tab::print_points()
{
	printf("Текущее число точек табулирования: %d\n", points);
}
void Function_tab::set_bounds(double left, double right)
{
	if (left >= right)
		throw  "Неправильно введены границы\n";
	left_bound = left;
	right_bound = right;
	it_count = false;
}
void Function_tab::print_bounds()
{
	cout << "Левая граница: " << left_bound << endl << "Правая граница: " << right_bound << endl;
}
void Function_tab::tabulation()
{
	if (!func_set)
		throw "Не задана функция\n";
	double step = (right_bound - left_bound) / (points - 1);
	double start = left_bound;
	for (int i = 0; i < points - 1; i++)
	{
		values[0][i] = start;
		values[1][i] = function(start);
		start += step;
	}
	values[0][points - 1] = right_bound;
	values[1][points - 1] = function(right_bound);
	it_count = true;
}
void Function_tab::print_tab()
{
	if (!it_count)
		tabulation();
	cout << setw(6) << "  №  |" << setw(10) << "x" << setw(11) << "|y" << endl;
	cout << "----------------------------------------------" << endl;
	for (int i = 0; i < points; i++)
		cout << setw(5) << i + 1 << "|" << setw(10) << values[0][i] << setw(10) << "|" << values[1][i] << endl;
}
void Function_tab::filePrint_tab(char *name)
{
	if (!it_count)
		tabulation();
	ofstream f;
	f.open(name);
	f << setw(6) << "  №  |" << setw(10) << "x" << setw(11) << "|y" << endl;
	f << "----------------------------------------------" << endl;
	for (int i = 0; i < points; i++)
		f << setw(5) << i + 1 << "|" << setw(10) << values[0][i] << setw(10) << "|" << values[1][i] << endl;
	f.close();
}
Function_tab::~Function_tab()
{
	for (int i = 0; i < 2; i++)
	{
		delete[] values[i];
	}
	delete[] values;
}
int main()
{
	setlocale(LC_ALL, "Rus");
	double(*function_list[10])(double);
	function_list[0] = exp;
	function_list[1] = sin;
	function_list[2] = cos;
	function_list[3] = sqrt;
	Function_tab a;
	bool flag = true;
	int z, point;
	double left, right;
	cout << "Выберите функцию:" << endl;
	cout << "0 - exp" << endl
		 << "1 - sin" << endl
		 << "2 - cos" << endl
		 << "3 - sqrt" << endl;
	do
	{
		cout << "Введите номер от 0 до 3" << endl;
		cin >> z;
		if (z > 3 || z < 0)
			cout << "Неправильно ввден номер" << endl;
	} 
	while (z > 3 || z < 0);
	a.set_function(function_list[z]);
	do {
		flag = true;
		cout << "Введите число точек" << endl;
		cin >> point;
		try
		{
			a.set_points(point);
		}
		catch (char *s)
		{
			cout << s;
			flag = false;
		}
	} 
	while (!flag);
	do {
		flag = true;
		cout << "Введите границы отрезка" << endl;
		cin >> left >> right;
		try
		{
			a.set_bounds(left,right);
		}
		catch (char *s)
		{
			cout << s;
			flag = false;
		}
	} 
	while (!flag);
	a.print_bounds();
	a.print_points();
	a.tabulation();
	a.print_tab();
	do
	{
		cout << "Хотите вывести результаты в файл" << endl << "1 - да, 0 - нет" << endl;
		cin >> z;
		if (z > 1 || z < 0)
			cout << "Неправильно ввден номер" << endl;
	} 
	while (z > 1 || z < 0);
	if (z == 1)
		a.filePrint_tab();
	Function_tab b;
	b.print_bounds();
	b.print_points();
	do
	{
		cout << "Хотите провести табуляцию" << endl << "1 - да, 0 - нет" << endl;
		cin >> z;
		if (z > 1 || z < 0)
			cout << "Неправильно ввден номер" << endl;
	} 
	while (z > 1 || z < 0);
	if (z == 1)
	{
		try 
		{
			b.tabulation();
		}
		catch (char *s)
		{
			cout << s;
		}
	}
	cout << "Надо задать функцию" << endl;
	cout << "Выберите функцию:" << endl;
	cout << "0 - exp" << endl
		<< "1 - sin" << endl
		<< "2 - cos" << endl
		<< "3 - sqrt" << endl;
	do
	{
		cout << "Введите номер от 0 до 3" << endl;
		cin >> z;
		if (z > 3 || z < 0)
			cout << "Неправильно ввден номер" << endl;
	} 
	while (z > 3 || z < 0);
	b.set_function(function_list[z]);
	b.print_tab();
	_getch();
}