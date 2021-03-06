#include <stdio.h>
#include <locale.h>
#include <conio.h>
class convert_temperature
{
	float celsius;
public:
	convert_temperature()
	{
		celsius = 0;
	}
	convert_temperature(float t)
	{
		celsius = t;
	}
	convert_temperature(const convert_temperature &t)
	{
		celsius = t.celsius;
	}
	convert_temperature& operator=(const convert_temperature &t)
	{
		celsius = t.celsius;
		return *this;
	}
	convert_temperature& operator+(const convert_temperature &t)
	{
		celsius = t.celsius + celsius;
		return *this;
	}
	void set_temp(float x)
	{
		celsius = x;
	}
	void print_temp()
	{
		printf("Температура в Цельсиях: %f\n", celsius);
	}
	float faren()
	{
		return (celsius * 9) / 5 + 32;
	}
	float rank()
	{
		return (celsius * 9) / 5 + 491.67;
	}
	float kelvin()
	{
		return celsius + 273;
	}
};
int main()
{
	setlocale(LC_ALL, "Rus");
	float a;
	int flag;
	printf("Установите текущую температуру в Цельсиях:\n");
	scanf_s("%f", &a);
	convert_temperature c(a);
	convert_temperature c1;
	printf("Хотите вывести текущую температуру (1-да, 0-нет)?\n");
	do
	{
		scanf_s("%d", &flag);
		if (flag > 1 || flag < 0)
			printf("Неправильно введен номер\n");
	} 
	while (flag > 1 || flag < 0);
	if (flag == 1)
		c.print_temp();
	printf("Хотите вывести температуру в других единицах измернния?\n");
	printf("1 - Кельвин\n2 - Фаренгейт\n3 - Ранкин\n");
	do
	{
		scanf_s("%d", &flag);
		if (flag > 3 || flag < 1)
			printf("Неправильно введен номер\n");
	} 
	while (flag > 3 || flag < 1);
	switch (flag)
	{
		case 1: printf("Температура в Кельвинах: %f\n", c.kelvin()); break;
		case 2: printf("Температура в Фаренгейтах: %f\n", c.faren()); break;
		case 3: printf("Температура в Ранкин: %f\n", c.rank()); break;
	}
	printf("Введите еще раз температуру в Цельсиях:\n");
	scanf_s("%f", &a);
	c1.set_temp(a);
	printf("c1\n");
	c1.print_temp();
	convert_temperature c2;
	c2 = c1 + c;
	printf("c1 + c\n");
	c2.print_temp();
	_getch();
}