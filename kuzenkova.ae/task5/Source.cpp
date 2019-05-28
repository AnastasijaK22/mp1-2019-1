#include <iostream>
#include "Cashbox.h"
#include <locale.h>

using namespace std;

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Rus");
	char s[11] = "task5.txt";
	Storage temp(s);
	Cashbox::set_storage(temp);
	temp.print_barcodes();
	int a;
	Cashbox d;
	do
	{
		cout << "Введите штрихкод: ";
		cin >> a;
		try
		{
			d.scan_product(a);
			cout << "Хотите получить описание товара? (1 -да, 0 - нет)" << endl;
			cin >> a;
			if (a == 1)
				cout << d.get_description() << endl;
			cout << "Хотите добавить товар в покупку?  (1 -да, 0 - нет)" << endl;
			cin >> a;
			if (a == 1) 
				d.add_product();
		}
		catch (char  *s)
		{
			cout << s;
		}
		cout << "Хотите продолжить? (1 - да, 0 -нет)" << endl;;
		cin >> a;
		if (a != 1)
			break;
	} 
	while (1 > 0);
	d.print_check();
	Cashbox d1;
	d1 = d;
	cout << "Введите штрихкод товара, который хотите удалить" << endl;
	cin >> a;
	try 
	{
		if (!d1.delete_product(a))
			cout << "В чеке нет товара с таким штрихкодом" << endl;
	}
	catch (char *s)
	{
		cout << s;
	}
	d = d1;
	d.print_check();
	d.scan_product(2341);
	d.add_product();
	cout << "Добавили товар " << temp.seach(2341) << endl;
	d.print_check();
	cout << "Итоговая сумма: " << d.total_cost() << endl;
	cin >> a;
}