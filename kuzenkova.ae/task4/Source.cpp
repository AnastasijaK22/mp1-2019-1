#include <conio.h>
#include <iostream>
#include <fstream>
#include <locale.h>

using namespace std;

class Date
{
	int year;
	int month;
	int day;
	int max_values[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
public:
	Date(int _year = 1, int _month = 1, int _day = 1)
	{
		if ((_year < 1) || (_month < 1) || (_month > 12))
			throw "Неверная дата";
		if ((_day < 1 ) || (_day > max_values[_month - 1]))
			throw "Неверная дата";
		year = _year;
		month = _month;
		day = _day;
	}
	void get_date(int &_year, int &_month, int &_day) const
	{
		_year = year;
		_month = month;
		_day = day;
	}
	void set_date(int _year, int _month, int _day)
	{
		if ((_year < 0) || (_month < 1) || (_month > 12))
			throw "Неверная дата";
		if ((_day < 0) || (_day > max_values[_month - 1]))
			throw "Неверная дата";
		year = _year;
		month = _month;
		day = _day;
	}
	friend ostream& operator<<(ostream &os, const Date &d);
};
class Time_Interval
{
	int start_hour;
	int start_minute;
	int final_hour;
	int final_minute;
public:
	Time_Interval(int stHour = 0, int stMinute = 0, int fHour = 0, int fMinute = 1)
	{
		if ((stHour < 0) || (stHour > 23) || (fHour < 0) || (fHour > 23))
			throw "Неверно введен час";
		if ((stMinute < 0) || (stMinute > 60) || (fMinute < 0) || (fMinute > 60))
			throw "Неверно введены минуты";
		start_hour = stHour;
		start_minute = stMinute;
		final_hour = fHour;
		final_minute = fMinute;
	}
	void get_interval(int &stHour, int &stMinute, int &fHour, int &fMinute) const
	{
		stHour = start_hour;
		stMinute = start_minute;
		fHour = final_hour;
		fMinute = final_minute;
	}
	void set_interval(int stHour, int stMinute, int fHour, int fMinute)
	{
		if ((stHour < 0) || (stHour > 23) || (fHour < 0) || (fHour > 23))
			throw "Неверно введен час";
		if ((stMinute < 0) || (stMinute > 60) || (fMinute < 0) || (fMinute > 60))
			throw "Неверно введены минуты";
		start_hour = stHour;
		start_minute = stMinute;
		final_hour = fHour;
		final_minute = fMinute;
	}
	friend ostream& operator<<(ostream &os, const Time_Interval &t);
};
class Step_meter
{
	Date *date_counting;
	Time_Interval *interval_counting;
	int *steps;
	int count;
public:

};

ostream& operator<<(ostream &os, const Date &d)
{
	os << d.year << " " << d.month << " " << d.day << endl;
	return os;
}
ostream& operator<<(ostream &os, const Time_Interval &t)
{
	os << t.start_hour << " " << t.start_minute << " " << t.final_hour << " " << t.final_minute<< endl;
	return os;
}
int main()
{
	setlocale(LC_ALL, "Rus");
	/*Date d(1999, 12, 10);
	int year, month, day = 0;
	cout << d;
	d.get_date(year, month, day);
	cout << year << " " << month << " " << day << endl;
	Date *d1;
	d1 = new Date[5];
	d1[0] = {year, 12, 12};
	try
	{
		d1[1].set_date(-1, -1, 74);
	}
	catch (char *s)
	{
		cout << s << endl;
	}
	for (int i = 0; i < 5; i++)
		cout << d1[i];
	delete[] d1;
	Time_Interval t(1, 1, 1, 3);
	cout << t;
	t.set_interval(3, 5, 6, 10);
	cout << t;
	int a, b, c, h;
	t.get_interval(a, b, c, h);
	cout << a << " " << b << " " << c << " " << h << endl;
	Time_Interval *t1 = new Time_Interval[5];
	for (int i = 0; i < 5; i++)
		cout << t1[i];
	delete[] t1;*/
	_getch();
}