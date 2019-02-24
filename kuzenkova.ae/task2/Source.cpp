
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <string.h>

class Calendar_events
{
	int year[30];
	int month[30];
	int day[30];
	int number;
	char **name;
public:
	Calendar_events()
	{
		number = 1;
		year[0] = 1;
		month[0] = 1;
		day[0] = 1;
		name = new char*[30];
		name[0] = new char[1];
		name[0][0] = '\0';
	}
	Calendar_events(int* _year, int* _month, int* _day, char **_name, int _number)
	{
		number = _number;
		name = new char*[30];
		for (int i = 0; i < number; i++)
		{
			year[i] = _year[i];
			month[i] = _month[i];
			day[i] = _day[i];
			int len = strlen(_name[i]);
			name[i] = new char[len + 1];
			strcpy_s(name[i], 150, _name[i]);
		}
	}
	Calendar_events(const Calendar_events &c)
	{
		number = c.number;
		name = new char*[30];
		for (int i = 0; i < number; i++)
		{
			year[i] = c.year[i];
			month[i] = c.month[i];
			day[i] = c.day[i];
			int len = strlen(c.name[i]);
			name[i] = new char[len + 1];
			strcpy_s(name[i], 150, c.name[i]);
		}
	}
	void set_event(int _year, int _month, int _day, char *_name)
	{
		number++;
		year[number-1] = _year;
		month[number-1] = _month;
		day[number-1] = _day;
		int len = strlen(_name);
		name[number-1] = new char[len + 1];
		strcpy_s(name[number-1], 150, _name);
	}
	void print()
	{
		for (int i = 0; i < number; i++)
		{
			printf("%d год %d месяц %d день \n", year[i], month[i], day[i]);
			puts(name[i]);
		}
	}
};
int main()
{
	setlocale(LC_ALL, "Rus");
	Calendar_events c1;
	int year[3] = { 2, 3, 1 }, month[3] = { 3, 4, 5 }, day[3] = { 27, 25, 24 }, number = 3;
	char *s[3] = { "Пауля", "Вася", "Григорий" };
	c1.print();
	Calendar_events c2(year, month, day, s, number);
	int _year = 1, _month = 2, _day = 3;
	char *s1 = "курочка";
	c1.set_event(_year, _month, _day,s1);
	//Calendar_events c3(c1);
	c1.print();
	_getch();
}