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
	int max_values[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
public:
	Calendar_events()//конструктор по умолчанию
	{
		number = 1;
		year[0] = 1;
		month[0] = 1;
		day[0] = 1;
		name = new char*[30];
		name[0] = new char[1];
		name[0][0] = '\0';
	}
	//конструктор инициализатор
	Calendar_events(int _number, int* _year, int* _month, int* _day, char **_name)
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
			strcpy_s(name[i], 15, _name[i]);
		}
	}
	//конструктор копирования
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
			strcpy_s(name[i], 15, c.name[i]);
		}
	}
	// метод - устоновить событие
	void set_event(int _year, int _month, int _day, char *_name)
	{
		number++;
		year[number-1] = _year;
		month[number-1] = _month;
		day[number-1] = _day;
		int len = strlen(_name);
		name[number-1] = new char[len + 1];
		strcpy_s(name[number-1], 15, _name);
	}
	int difference(int _year, int _month, int _day, int index, int *a)
	{
		int temp_year, temp_month, temp_day;
		int flag = _month;
		if (index >= number)
			return -1;
		temp_year = _year - year[index];
		temp_month = _month - month[index];
		temp_day = _day - day[index];
		if (temp_year < 0)
		{
			temp_year *= (-1);
			temp_month *= (-1);
			temp_day *= (-1);
			flag = month[index];
		}
		if (temp_year != 0)
		{
			if (temp_month < 0)
			{
				if (temp_day < 0)
				{
					temp_year = temp_year - 1;
					temp_month = temp_month + 11;
					temp_day = temp_day + max_values[flag - 1];
				}
				if (temp_day >= 0)
				{
					temp_year = temp_year - 1;
					temp_month = temp_month + 12;
				}
			}
			else
			if (temp_month != 0)
			{
				if (temp_day < 0)
				{
					temp_month = temp_month - 1;
					temp_day = temp_day + max_values[flag - 1];
				}
			}
			else
				if (temp_day < 0)
				{
					temp_year = temp_year - 1;
					temp_month = temp_month + 11;
					temp_day = temp_day + max_values[flag - 1];
				}
		}
		else
		{
			if (temp_month < 0)
			{
				temp_month *= (-1);
				temp_day *= (-1);
				flag = month[index];
			}
			if (temp_day < 0)
			{
				temp_month--;
				temp_day = temp_day + max_values[flag];
			}
		}
		a[0] = temp_year;
		a[1] = temp_month;
		a[2] = temp_day;
		//printf("%d %d %d\n", temp_year, temp_month, temp_day);
		return 1;
	}
	int shift(int _year, int _month, int _day, int index, bool direction)
	{
		if (index >= number)
			return -1;
		int flag;
		int flag2;
		if (direction)
		{
			flag = (day[index] + _day) / (max_values[month[index]-1]+1);
			day[index] = (day[index] + _day) % (max_values[month[index]-1] + 1) + flag;
			flag2 = (month[index] + _month + flag) / 13;
			month[index] = (month[index] + _month + flag) % 13 + flag2;
			year[index] = year[index] + _year + flag2;
		}
		else
		{
				
		}
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
	int a[3];
	int year[3] = { 2000, 1998, 2001 }, month[3] = { 3, 6, 12 }, day[3] = { 27, 22, 24 }, number = 3;
	char **s;
	s = new char*[3];
	for (int i = 0; i < number; i++)
		s[i] = new char[7];
	strcpy_s(s[0], 7, "name");
	strcpy_s(s[1], 7, "cool");
	strcpy_s(s[2], 7, "party");
	//c1.print();
	Calendar_events c2(number,year, month, day, s);
	int _year = 1, _month = 2, _day = 3;
	char *s1;
	s1 = new char[7];
	strcpy_s(s1,7,"named");
	//c1.set_event(_year, _month, _day,s1);
	Calendar_events c3(c1);
	//c3.print();
	if (c2.difference(1999, 12, 22, 1, a) == 1)
		for (int i = 0; i < 3; i++)
			printf("%d ", a[i]);
	printf("\n");
	c2.shift(1, 5, 10, 1,true);
	c2.print();
	_getch();
}