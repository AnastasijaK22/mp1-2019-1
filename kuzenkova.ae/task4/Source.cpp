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
	Date(int _year = 1901, int _month = 1, int _day = 1)
	{
		if ((_year < 1901) || (_month < 1) || (_month > 12))
			throw "Неверная дата";
		if ((_day < 1 ) || (_day > (max_values[_month - 1] + 1 * (_month == 2) * (_year % 4 == 0))))
			throw "Неверная дата";
		year = _year;
		month = _month;
		day = _day;
	}
	/*void get_date(int &_year, int &_month, int &_day) const
	{
		_year = year;
		_month = month;
		_day = day;
	}*/
	int get_year() const 
	{ return year; }
	int get_month() const 
	{ return month; }
	int get_day() const 
	{ return day; }
	void set_date(int _year, int _month, int _day)
	{
		Date temp(_year, _month, _day);
		*this = temp;
	}
	int day_week() const
	{
		const int standart = 730500;
		int sum = 0;
		for (int i = 0; i < month - 1; i++)
			sum = sum + max_values[i];
		if ((year % 4 == 0) && (month > 2))
			sum++;
		sum = (sum + day + 365 * year + (year / 4 - 1 * (year % 4 == 0))) - standart;
		sum = (sum + 6) % 7 + 7 * ((sum + 6) % 7 < 0);
		return sum;
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
		Time_Interval temp;
		*this = temp;
	}
	friend ostream& operator<<(ostream &os, const Time_Interval &t);
};
class Step_meter
{
	Date *date_counting;
	Time_Interval *interval_counting;
	int *steps;
	int current;
	int count;
	bool isDate;
	bool isCounting;
	void add_memory(int add = 1)
	{
		Step_meter temp = *this;
		count += add;
		delete[] date_counting;
		delete[] interval_counting;
		delete[] steps;
		date_counting = new Date[count];
		interval_counting = new Time_Interval[count];
		steps = new int[count];
		for (int i = 0; i <= current ; i++)
		{
			date_counting[i] = temp.date_counting[i];
			interval_counting[i] = temp.interval_counting[i];
			steps[i] = temp.steps[i];
		}
		for (int i = current + 1; i < count; i++)
			steps[i] = 0;
	}
public:
	Step_meter()
	{
		count = 1;
		date_counting = new Date[count];
		interval_counting = new Time_Interval[count];
		steps = new int[count];
		current = 0;
		steps[current] = 0;
		isDate = false;
		//isCounting = false;
	}
	Step_meter(const Step_meter &s)
	{
		count = s.count;
		date_counting = new Date[count];
		interval_counting = new Time_Interval[count];
		steps = new int[count];
		isDate= s.isDate;
		//isCounting = s.isCounting;
		current = s.current;
		for (int i = 0; i < count; i++)
		{
			date_counting[i] = s.date_counting[i];
			interval_counting[i] = s.interval_counting[i];
			steps[i] = s.steps[i];
		}
	}
	Step_meter& operator=(const Step_meter &s)
	{
		if (this == &s)
			return *this;
		delete[] date_counting;
		delete[] interval_counting;
		delete[] steps;
		count = s.count;
		date_counting = new Date[count];
		interval_counting = new Time_Interval[count];
		steps = new int[count];
		isDate = s.isDate;
		//isCounting = s.isCounting;
		current = s.current;
		for (int i = 0; i < count; i++)
		{
			date_counting[i] = s.date_counting[i];
			interval_counting[i] = s.interval_counting[i];
			steps[i] = s.steps[i];
		}
		return *this;
	}
	void set_time(Date dat)
	{
		if (isDate)
		{
			if ((current == count - 1) && (/*isCounting*/ steps[current] > 0))
			{
				add_memory(2);
			}
			if (/*isCounting*/ steps[current] > 0)
				current++;
		}
		isDate = true;
		//isCounting = false;
		date_counting[current] = dat;
	}
	void set_counting(Time_Interval interval, int step)
	{
		if (!isDate)
			throw "Не установлена дата";
		if (step < 1)
			throw "Неверно введены шаги";
		if (/*isCounting*/ steps[current] > 0)
		{
			current++;
			if (current >= count - 1)
				add_memory(2);
			date_counting[current] = date_counting[current - 1];
		}
		interval_counting[current] = interval;
		steps[current] = step;
		//isCounting = true;
	}
	Date get_time() const
	{
		if (!isDate)
			throw "Дата не установлена";
		return date_counting[current];
	}
	double average_inMonth(int month) const
	{
		if ((month < 1) || (month > 13))
			throw "Неверный месяц";
		int temp = 0;
		int number = 0;
		for (int i = 0; i <= current; i++)
			if (((month == 13) || (date_counting[i].get_month() == month)) && /*isCounting*/ (steps[i] > 0))
			{
				temp += steps[i];
				number++;
			}
		/*if ((isCounting) && ((month == 13) || (date_counting[current].get_month() == month)))
		{
			temp += steps[current];
			number++;
		}*/
		if (number == 0)
			return 0;
		else
			return temp * 1. / number;
	}
	double average_inDay(int day_week) const
	{
		if ((day_week < 0) || (day_week > 6))
			throw "Неверный день недели";
		int temp = 0;
		int number = 0;
		for (int i = 0; i <= current; i++)
			if ((day_week == date_counting[current].day_week()) && (/*isCounting*/ steps[i] > 0))
			{
				temp += steps[i];
				number++;
			}
		/*if ((isCounting) && (day_week == date_counting[current].day_week()))
		{
			temp += steps[current];
			number++;
		}*/
		if (number == 0)
			return 0;
		else
			return temp * 1. / number;
	}
	void max_inMonth(int month, int &max_step, Date &dat) const
	{
		if ((month < 1) || (month > 13))
			throw "Неверный месяц";
		max_step = 0;
		dat = date_counting[0];
		for (int i = 1; i <= current; i++)
			if (((month == 13) || (date_counting[i].get_month() == month)) && (steps[max_step] < steps[i]))
				max_step = i;
		dat = date_counting[max_step];
		max_step = steps[max_step];
	}
	void file_get(char *s = "task4.txt")
	{
		ifstream fin(s);
		if (!fin.is_open())
			throw "нет такого файла";
		char temp[50];
		while (!fin.eof())
		{
			fin >> temp;
			if (strlen(temp) != 0) 
			{
				int point[2];
				int a[4];
				int k = 0;
				for (int i = 0; i < strlen(temp); i++)
					if (temp[i] == '.')
					{
						point[k] = i + 1;
						k++;
					}
				try
				{
					Date dat(atoi(temp + point[1]), atoi(temp + point[0]), atoi(temp));
					set_time(dat);
				}
				catch (char *s)
				{
					cout << s << endl;
				}
				fin >> temp;
				for (int i = 0; i < strlen(temp); i++)
					if (temp[i] == ':')
						point[0] = i + 1;
				a[0] = atoi(temp);
				a[1] = atoi(temp + point[0]);
				fin >> temp;
				fin >> temp;
				for (int i = 0; i < strlen(temp); i++)
					if (temp[i] == ':')
						point[0] = i + 1;
				a[2] = atoi(temp);
				a[3] = atoi(temp + point[0]);
				fin >> temp;
				try
				{
					Time_Interval time(a[0], a[1], a[2], a[3]);
					set_counting(time, atoi(temp));
				}
				catch (char *s)
				{
					cout << s << endl;
				}
			}
		}
		fin.close();
	}
	void file_print(char *s = "task4.txt")
	{
		ofstream fout(s,ios_base::app);
		if (!fout.is_open())
			throw "нет такого файла";
		for (int i = 0; i <= current; i++)
			fout << date_counting[i] << interval_counting[i] << steps[i] << endl;
		fout.close();
	}
	void print() const
	{
		for (int i = 0; i <= current; i++)
			cout << date_counting[i] << interval_counting[i] << steps[i] << endl;
	}
	~Step_meter()
	{
		delete[] date_counting;
		delete[] interval_counting;
		delete[] steps;
	}
};

ostream& operator<<(ostream &os, const Date &d)
{
	os << d.day << "." << d.month << "." << d.year << " ";
	return os;
}
ostream& operator<<(ostream &os, const Time_Interval &t)
{
	os << t.start_hour << ":" << t.start_minute << " - " << t.final_hour << ":" << t.final_minute<< " ";
	return os;
}
int main()
{
	setlocale(LC_ALL, "Rus");
	Date *d1;
	d1 = new Date[5];
	d1[0] = {2019, 3, 26};
	try
	{
		d1[1].set_date(2019, 3, 19);
	}
	catch (char *s)
	{
		cout << s << endl;
	}
	cout <<":" << d1[1].day_week() << endl;
	for (int i = 0; i < 5; i++)
		cout << d1[i] << endl;

	Time_Interval *t1 = new Time_Interval[5];
	for (int i = 0; i < 5; i++)
		cout << t1[i] << endl;

	Step_meter c1;
	c1.set_time(d1[1]);
	//c1.set_time(d1[2]);
	c1.set_counting(t1[0], 5);
	cout << c1.average_inDay(1) << endl;
	c1.print();
	cout << endl;
	c1.set_counting(t1[0], 10);
	c1.set_time(d1[0]);
	Step_meter c2 = c1;	
	c2.set_counting(t1[0], 2000);
	c2.print();
	c2 = c1;
	c2 = c2;
	cout << endl;
	c2.print();
	cout << c2.get_time() << endl;
	cout << c2.average_inMonth(8) << endl;
	cout << c2.average_inDay(2) << endl; 
	c2.file_get();
	c2.print();
	Date d;
	int step;
	c2.max_inMonth(13, step, d);
	cout << d << " " << step << endl;
	c2.file_print();
	delete[] d1;
	delete[] t1;
	_getch();
}