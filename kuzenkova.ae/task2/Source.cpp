
#include <stdio.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
class Calendar_events
{
	int year[30];
	int month[30];
	int day[30];
	int number=0;
	char *name[30];
public:
	Calendar_events()
	{
		number = 1;
		year[0] = 1;
		month[0] = 1;
		day[0] = 1;
		name[0] = new char[1];
		name[0][0] = '\0';
	}
	void print()
	{
		for (int i = 0; i < number; i++)
			printf("%d год %d мес€ц %d день\n",year[i],month[i],day[i]);
	}
};
int main()
{
	setlocale(LC_ALL, "Rus");
	Calendar_events c1;
	int year = 2, month = 3, day = 28;
	char *s = "день рождени€ ѕаул€";
	c1.print();
	_getch();
}