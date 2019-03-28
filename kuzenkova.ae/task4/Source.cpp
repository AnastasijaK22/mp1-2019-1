#include <conio.h>
#include <iostream>
#include <fstream>
#include <locale.h>

using namespace std;

class Date
{
	// класс дата
	int year;
	int month;
	int day;
	int max_values[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
public:
	// конструктор инициализатор
	Date(int _year = 1901, int _month = 1, int _day = 1);
	// метод - узнать год
	int get_year() const { return year; }
	// метод - узнать месяц
	int get_month() const { return month; }
	// метод - узнать день
	int get_day() const { return day; }
	// метод - установить дату
	void set_date(int _year, int _month, int _day);
	// метод - узнать день недели
	int day_week() const;
	// перегрузка вывода
	friend ostream& operator<<(ostream &os, const Date &d);
};
class Time_Interval
{
	// класс временной интервал
	int start_hour;
	int start_minute;
	int final_hour;
	int final_minute;
public:
	// конструктор инициализатор
	Time_Interval(int stHour = 0, int stMinute = 0, int fHour = 0, int fMinute = 1);
	// метод - узнать интервал
	void get_interval(int &stHour, int &stMinute, int &fHour, int &fMinute) const;
	// метод - установить интервал
	void set_interval(int stHour, int stMinute, int fHour, int fMinute);
	// перегрузка вывода
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
	void add_memory(int add = 1);
public:
	// конструктор по умолчанию
	Step_meter();
	// конструктор копирования
	Step_meter(const Step_meter &s);
	// оператор присваивания
	Step_meter& operator=(const Step_meter &s);
	// метод - установить дату
	void set_time(Date dat);
	// метод - установить подсчет
	void set_counting(Time_Interval interval, int step);
	// метод - узнать установленную дату
	Date get_time() const;
	// метод - среднее значение шагов в месяце или за все время
	double average_inMonth(int month) const;
	// метод - среднее значение шагов в день недели
	double average_inDay(int day_week) const;
	// метод - найти максимальное значение шагов 
	void max_inMonth(int day, int month, int &max_step, Date &dat) const;
	// метод - выдать информацию о подсчете
	void put_counting(int index, int &step, Date &dat, Time_Interval &time) const;
	// метод - считать данные из файла
	void file_get(char *s = "task4.txt");
	// метод - вывести данные в файл
	void file_print(int i = 0, char *s = "task4.txt");
	// метод - вывод подсчетов
	void print() const;
	// деструктор
	~Step_meter();
};
Date::Date(int _year, int _month, int _day)
{
	if ((_year < 1901) || (_month < 1) || (_month > 12))
		throw "Неверная дата";
	if ((_day < 1) || (_day > (max_values[_month - 1] + 1 * (_month == 2) * (_year % 4 == 0))))
		throw "Неверная дата";
	year = _year;
	month = _month;
	day = _day;
}
void Date::set_date(int _year, int _month, int _day)
{
	Date temp(_year, _month, _day);
	*this = temp;
}
int Date::day_week() const
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
Time_Interval::Time_Interval(int stHour, int stMinute, int fHour, int fMinute)
{
	if ((stHour < 0) || (stHour > 23) || (fHour < 0) || (fHour > 23))
		throw "Неверно введен час";
	if ((stMinute < 0) || (stMinute > 60) || (fMinute < 0) || (fMinute > 60))
		throw "Неверно введены минуты";
	if ((stHour > fHour) || ((stHour == fHour) && (stMinute > fMinute)))
		throw "Неверно введен интервал";
	start_hour = stHour;
	start_minute = stMinute;
	final_hour = fHour;
	final_minute = fMinute;
}
void Time_Interval::get_interval(int &stHour, int &stMinute, int &fHour, int &fMinute) const
{
	stHour = start_hour;
	stMinute = start_minute;
	fHour = final_hour;
	fMinute = final_minute;
}
void Time_Interval::set_interval(int stHour, int stMinute, int fHour, int fMinute)
{
	Time_Interval temp(stHour, stMinute, fHour, fMinute);
	*this = temp;
}
Step_meter::Step_meter()
{
	count = 1;
	date_counting = new Date[count];
	interval_counting = new Time_Interval[count];
	steps = new int[count];
	current = 0;
	steps[current] = 0;
	isDate = false;
}
Step_meter::Step_meter(const Step_meter &s)
{
	count = s.count;
	date_counting = new Date[count];
	interval_counting = new Time_Interval[count];
	steps = new int[count];
	isDate = s.isDate;
	current = s.current;
	for (int i = 0; i < count; i++)
	{
		date_counting[i] = s.date_counting[i];
		interval_counting[i] = s.interval_counting[i];
		steps[i] = s.steps[i];
	}
}
Step_meter& Step_meter::operator=(const Step_meter &s)
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
	current = s.current;
	for (int i = 0; i < count; i++)
	{
		date_counting[i] = s.date_counting[i];
		interval_counting[i] = s.interval_counting[i];
		steps[i] = s.steps[i];
	}
	return *this;
}
void Step_meter::add_memory(int add)
{
	Step_meter temp = *this;
	count += add;
	delete[] date_counting;
	delete[] interval_counting;
	delete[] steps;
	date_counting = new Date[count];
	interval_counting = new Time_Interval[count];
	steps = new int[count];
	for (int i = 0; i <= current; i++)
	{
		date_counting[i] = temp.date_counting[i];
		interval_counting[i] = temp.interval_counting[i];
		steps[i] = temp.steps[i];
	}
	for (int i = current + 1; i < count; i++)
		steps[i] = 0;
}
void Step_meter::set_time(Date dat)
{
	if (isDate)
	{
		if ((current == count - 1) && (steps[current] > 0))
		{
			add_memory(2);
		}
		if (steps[current] > 0)
			current++;
	}
	isDate = true;
	date_counting[current] = dat;
}
void Step_meter::set_counting(Time_Interval interval, int step)
{
	if (!isDate)
		throw "Не установлена дата";
	if (step < 1)
		throw "Неверно введены шаги";
	if (steps[current] > 0)
	{
		current++;
		if (current >= count - 1)
			add_memory(2);
		date_counting[current] = date_counting[current - 1];
	}
	interval_counting[current] = interval;
	steps[current] = step;
}
Date Step_meter::get_time() const
{
	if (!isDate)
		throw "Дата не установлена";
	return date_counting[current];
}
double Step_meter::average_inMonth(int month) const
{
	if ((month < 1) || (month > 13))
		throw "Неверный месяц";
	int temp = 0;
	int number = 0;
	for (int i = 0; i <= current; i++)
		if (((month == 13) || (date_counting[i].get_month() == month)) && (steps[i] > 0))
		{
			temp += steps[i];
			number++;
		}
	if (number == 0)
		return 0;
	else
		return temp * 1. / number;
}
double Step_meter::average_inDay(int day_week) const
{
	if ((day_week < 0) || (day_week > 6))
		throw "Неверный день недели";
	int temp = 0;
	int number = 0;
	for (int i = 0; i <= current; i++)
		if ((day_week == date_counting[current].day_week()) && (steps[i] > 0))
		{
			temp += steps[i];
			number++;
		}
	if (number == 0)
		return 0;
	else
		return temp * 1. / number;
}
void Step_meter::max_inMonth(int day, int month, int &max_step, Date &dat) const
{
	if ((month < 1) || (month > 13))
		throw "Неверный месяц";
	max_step = 0;
	dat = date_counting[0];
	for (int i = 1; i <= current; i++)
		if (((month == 13) || ((date_counting[i].get_month() == month) && (date_counting[i].get_day() == day))) && (steps[max_step] < steps[i]))
			max_step = i;
	if ((max_step == 0) && ((date_counting[0].get_month() != month) || (date_counting[0].get_day() != day)))
	{
		dat.set_date(1901, 1, 1);
		max_step = 0;
	}
	else
	{
		dat = date_counting[max_step];
		max_step = steps[max_step];
	}
}
void Step_meter::put_counting(int index, int &step, Date &dat, Time_Interval &time) const
{
	if (index > current)
		throw "Неправильный индекс";
	step = steps[index];
	dat = date_counting[index];
	time = interval_counting[index];
}
void Step_meter::file_get(char *s)
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
void Step_meter::file_print(int i, char *s)
{
	ofstream fout;
	if (i != 0)
		fout.open(s, ios_base::app);
	else
		fout.open(s);
	if (!fout.is_open())
		throw "нет такого файла";
	for (int i = 0; i <= current; i++)
		fout << date_counting[i] << interval_counting[i] << steps[i] << endl;
	fout.close();
}
void Step_meter::print() const
{
	for (int i = 0; i <= current; i++)
		cout << i << " " << date_counting[i] << interval_counting[i] << steps[i] << endl;
}
Step_meter::~Step_meter()
{
	delete[] date_counting;
	delete[] interval_counting;
	delete[] steps;
}
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
	bool flag;
	int temp;
	int step;
	Date d;
	Time_Interval t;
	Step_meter s;
	do
	{
		flag = true;
		int year, month, day;
		cout << "Введите дату (день, месяц, год): " << endl;
		cin >> day >> month >> year;
		try 
		{
			d.set_date(year, month, day);
		} 
		catch (char *s)
		{
			cout << s << endl;
			flag = false;
		}
		s.set_time(d);
	} 
	while (!flag);
	int count = 0;
	do
	{
		do
		{
			flag = true;
			int h1, m1, h2, m2, step;
			cout << "Введите временной интервал (час, минуты, час, минуты): " << endl;
			cin >> h1 >> m1 >> h2 >> m2;
			cout << "Введите шаги: ";
			cin >> step;
			try
			{
				t.set_interval(h1, m1, h2, m2);
				s.set_counting(t, step);
			}
			catch (char *s)
			{
				cout << s << endl;
				flag = false;
			}
		} while (!flag);
		count++;
		if (count > 3)
		{
			cout << "Хотите ввести новую дату? Введите 1 - если да" << endl;
			cin >> temp;
			if (temp == 1)
			{
				count = 0;
				do
				{
					flag = true;
					int year, month, day;
					cout << "Введите дату (день, месяц, год): " << endl;
					cin >> day >> month >> year;
					try
					{
						d.set_date(year, month, day);
					}
					catch (char *s)
					{
						cout << s << endl;
						flag = false;
					}
					s.set_time(d);
				} while (!flag);
			}
		}
		cout << "Хотите ввести еще? Введите 1 - если да" << endl;
		cin >> temp;
	} 
	while (temp == 1);
	cout << "Текущая дата: "<< s.get_time() << endl;
	s.print();
	cout << "Введи индекс подсчета: " << endl;
	cin >> temp;
	flag = true;
	try
	{
		s.put_counting(temp, step, d, t);
	}
	catch (char *s)
	{
		cout << s << endl;
		flag = false;
	}
	if (flag)
		cout << d << t << step << endl;
	cout << "Среднее значение шагов в пятницу: " << s.average_inDay(5) << endl;
	cout << "Среднее значение шагов в апреле: " << s.average_inMonth(4) << endl;
	cout << "Среднее значение шагов за все время: " << s.average_inMonth(13) << endl;
	s.max_inMonth(0, 13, step, d);
	cout << "Максимальное значение шагов за все время: " << step << " " << d << endl;
	Step_meter s1 = s;
	s1.file_get();
	s1.print();
	s = s1;
	s.file_print();
	_getch();
}