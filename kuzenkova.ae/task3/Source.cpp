#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <math.h>

class Function_tab
{
	double left_bound;
	double right_bound;
	int points;
	double (*function)(double x);
	bool func_set;
public:
	/*Function_tab()
	{
		left_bound = 0;
		right_bound = 1;
		points = 1;
		function = nullptr;
		func_set = false;
	}*/
	Function_tab(double right = 1, double left = 0, int _points = 1, double (*func)(double x) = nullptr):
		left_bound(left), right_bound(right), points(_points), function(func), func_set(false)
	{
	}
	void set_function(double(*func)(double x))
	{
		function = func;
		func_set = true;
	}
	void set_points(int _points)
	{
		points = _points;
	}
	void print_points()
	{
		printf("Текущее число точек табулирования: %d\n", points);
	}
	void set_bounds(int left, int right)
	{

	}
	void print()
	{
		printf("%lf\n", function(left_bound));
	}
};
int main()
{
	setlocale(LC_ALL, "Rus");
	Function_tab a;
	a.set_points(10);
	a.set_function(sin);
	a.print();
	_getch();
}