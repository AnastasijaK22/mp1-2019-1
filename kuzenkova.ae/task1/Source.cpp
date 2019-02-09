#include <stdio.h>
#include <locale.h>
class temp
{
	float celsius;
public:
	temp()
	{
		celsius = 0;
	}
	temp(float t)
	{
		celsius = t;
	}
	void print_temp()
	{
		printf("%f\n", celsius);
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
	temp c(a);
	printf("Хотите вывести текущую температуру в Цельсиях (1-да, 0-нет)?\n");
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
		case 1: printf("%f", c.kelvin()); break;
		case 2: printf("%f", c.faren()); break;
		case 3: printf("%f", c.rank()); break;
	}
	scanf_s("%f", &a);
}