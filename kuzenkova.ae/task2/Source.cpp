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
	int max_values[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	char **name;
	//функция для копирования строки
	void mycpy(int len, int i, char *s1)
	{
		for (int j = 0; j < len; j++)
			name[i][j] = s1[j];
		name[i][len] = '\0';
	}
public:
	//конструктор по умолчанию
	Calendar_events();
	//конструктор инициализатор
	Calendar_events(int _number, int* _year, int* _month, int* _day, char **_name);
	//конструктор копирования
	Calendar_events(const Calendar_events &c);
	// метод - устоновить событие
	void set_event(int _year, int _month, int _day, char *_name);
	// метод - разница между событием и заданной датой
	int difference(int _year, int _month, int _day, int index, int *a);
	// сдвиг даты события
	int shift(int _year, int _month, int _day, int index, bool direction);
	// вывод события
	void print();
	// поиск события
	void search_event(char *s);
	// оператор присваивания
	Calendar_events& operator=(const Calendar_events &c);
	//деструктор
	~Calendar_events()
	{
		for (int i = 0; i < number; i++)
		{
			delete[] name[i];
		}
		delete[] name;
	}
};
Calendar_events::Calendar_events()
{
	number = 1;
	year[0] = 1;
	month[0] = 1;
	day[0] = 1;
	name = new char*[30];
	name[0] = new char[1];
	name[0][0] = '\0';
}
Calendar_events::Calendar_events(int _number, int* _year, int* _month, int* _day, char **_name)
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
		mycpy(len, i, _name[i]);
	}
}
Calendar_events::Calendar_events(const Calendar_events &c)
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
		mycpy(len, i, c.name[i]);
	}
}
Calendar_events& Calendar_events::operator=(const Calendar_events &c)
{
	if (this == &c)
		return *this;
	for (int i = 0; i < number; i++)
	{
		delete[] name[i];
	}
	delete[] name;
	number = c.number;
	name = new char*[30];
	for (int i = 0; i < number; i++)
	{
		year[i] = c.year[i];
		month[i] = c.month[i];
		day[i] = c.day[i];
		int len = strlen(c.name[i]);
		name[i] = new char[len + 1];
		mycpy(len, i, c.name[i]);
	}
	return *this;
}
void Calendar_events::print()
{
	for (int i = 0; i < number; i++)
	{
		printf("%d. %d год %d месяц %d день \n",i+1, year[i], month[i], day[i]);
		puts(name[i]);
	}
}
void Calendar_events::set_event(int _year, int _month, int _day, char *_name)
{
		number++;
		year[number - 1] = _year;
		month[number - 1] = _month;
		day[number - 1] = _day;
		int len = strlen(_name);
		name[number - 1] = new char[len + 1];
		mycpy(len, number-1, _name);
}
void Calendar_events::search_event(char *s)
{
	int len_name;
	int i;
	char *p;
	int len_s = strlen(s);
	for (i = 0; i < number; i++)
	{
		len_name = strlen(name[i]);
		if ((len_name == len_s))
		{
			p = strstr(name[i], s);
			if (p != NULL)
				break;
		}
	}
	if (i == number)
		printf("Нет такого события\n");
	else
	{
		printf("Такое событие есть! Его дата: %d год %d месяц %d день \n", year[i], month[i], day[i]);
	}
}
int Calendar_events::shift(int _year, int _month, int _day, int index, bool direction)
{
	index--;
	if (index >= number)
		return -1;
	int flag = 0;
	int flag2 = 0;
	if (direction)
	{
		flag = (day[index] + _day) / (max_values[month[index] - 1] + 1);
		day[index] = (day[index] + _day) % (max_values[month[index] - 1] + 1) + flag;
		flag2 = (month[index] + _month + flag) / 13;
		month[index] = (month[index] + _month + flag) % 13 + flag2;
		year[index] = year[index] + _year + flag2;
	}
	else
	{
		if (day[index] - _day <= 0)
			flag = 1;
		if (month[index] - 1 - flag == -1)
			flag2 = 1;
		day[index] = day[index] - _day + max_values[month[index] - 1 - flag + 12 * flag2] * flag;
		month[index] = month[index] - flag + 12 * flag2;
		year[index] = year[index] - flag2;
		flag2 = 0;
		if ((month[index] - _month) <= 0)
			flag2 = 1;
		month[index] = month[index] - _month + 12 * flag2;
		year[index] = year[index] - _year - flag2;
	}
}
int Calendar_events::difference(int _year, int _month, int _day, int index, int *a)
{
	int temp_year, temp_month, temp_day;
	int flag = _month;
	index--;
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
	return 1;
}
int main()
{
	setlocale(LC_ALL, "Rus");
	Calendar_events c1;
	int max_values[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int a[3], flag;
	int year[3] = { 2000, 1998, 2001 }, month[3] = { 3, 1, 12 }, day[3] = { 27, 22, 24 }, number = 3;
	char **s;
	s = new char*[3];
	for (int i = 0; i < number; i++)
		s[i] = new char[30];
	strcpy_s(s[0], 30, "Birthday Party");
	strcpy_s(s[1], 30, "Deadline");
	strcpy_s(s[2], 30, "Exam");
	Calendar_events c2(number,year, month, day, s);
	for (int i = 0; i < 3; i++)
		delete[] s[i];
	delete[] s;
	do
	{
		printf("Хотите вывести ваш календарь событий?\n Да - 1, Нет - 0\n");
		scanf_s("%d", &flag);
		if (flag > 1 || flag < 0)
			printf("Некоректный ввод\n");
	} 
	while (flag > 1 || flag < 0);
	if (flag == 1)
		c2.print();
	int _year, _month, _day;
	char *s1, temp;
	s1 = new char[30];
	do
	{
		printf("Введите год: ");
		scanf_s("%d", &_year);
		printf("\nВведите месяц: ");
		scanf_s("%d", &_month);
		printf("\nВведите день: ");
		scanf_s("%d", &_day);
		if (_year > 2020 || _year < 1 || _month > 12 || _month < 1 || _day < 1 || _day > max_values[_month - 1])
			printf("Некоректный ввод\n");
	} while (_year > 2020 || _year < 1 || _month > 12 || _month < 1 || _day < 1 || _day > max_values[_month - 1]);
	scanf_s("%c", &temp);
	printf("\nВведите название: ");
	gets_s(s1, 30);
	c2.set_event(_year, _month, _day, s1);
	do
	{
		printf("Хотите сравнить эту дату с другим событием в календаре?\n Да - 1, Нет - 0\n");
		scanf_s("%d", &flag);
		if (flag > 1 || flag < 0)
			printf("Некоректный ввод\n");
	} while (flag > 1 || flag < 0);
	if (flag == 1)
	{
		int index;
		printf("Введите номер события:\n");
		do 
		{
			scanf_s("%d", &index);
			if (c2.difference(_year, _month, _day, index, a) != 1)
				printf("Нет события с таким номером!\n");
		} 
		while (c2.difference(_year, _month, _day, index, a) != 1);
		for (int i = 0; i < 3; i++)
			printf("%d ", a[i]);
	}
	Calendar_events c3(c2);
	scanf_s("%c", &temp);
	printf("\nВведите название: ");
	gets_s(s1, 30);
	c3.search_event(s1);
	do
	{
		printf("Хотите сдвинуть дату 1 события в календаре на 1 год 2 месяца 25 дней?\n Да - 1, Нет - 0\n");
		scanf_s("%d", &flag);
		if (flag > 1 || flag < 0)
			printf("Некоректный ввод\n");
	} while (flag > 1 || flag < 0);
	if (flag == 1)
	{
		c2.shift(1, 2, 25, 1, false);
		c2.print();
	}
	c2 = c1;
	printf("Приравняли события из 2 календаря 1:\n");
	c2.print();
	_getch();
}