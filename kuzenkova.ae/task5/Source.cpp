#include <iostream>
#include <string>
#include <vector>
#include <locale.h>
#include <time.h>
#include <fstream>
#include <iomanip>

using namespace std;

//класс - продукт
class Product
{
	string name;
	int barcode;
	int discount;
	int price;
public:
	// конструктор по умолчанию
	Product() : name("Не товар"), price(0), barcode(0), discount(0) {}
	// конструктор инициализатор
	Product(int _barcode, int _price, string _name);
	// метод - установить продукт
	void set_product(int _barcode, int _price, string _name);
	// метод - вернуть штрихкод
	int get_barcode() const { return barcode; }
	// метод - печать чека с этим товаром
	void product_check(int count) const;
	// метод - вычислить скидку n - ого числа товаров
	float goods_discount(int count) const;
	// метод - вычислить стоимость n - ого числа товаров
	int goods_cost(int count) const;
	// вывод на консоль
	friend ostream& operator<<(ostream &os, const Product &t);
};

// класс - склад
class Storage
{
	vector <Product> goods;
	int count;
public:
	// конструктор инициализатор
	Storage(string s = "task5.txt");
	// метод - печать штрихкодов товаров со склада
	void print_barcodes() const;
	// метод - поиска товара по штрихкоду
	Product seach(int _code) const;
};

// класс - касса
class Cashbox
{
	Storage stock;
	vector <Product> choosen_products;
	vector <int> quantity_products;
	int quantity;
	int code;
	Product choosen;
	int total;
	float total_discount;
public:
	// конструктор по умолчанию
	Cashbox() : stock(), quantity(0), code(0), total(0), total_discount(0) { }
	// метод - сканировать товар
	void scan_product(int _code);
	// метод - вернуть описание товара
	Product get_description() const;
	// метод - добавить товар в чек
	bool add_product(int count = 1);
	// метод - печать чека
	void print_check() const;
	// метод - удалить продукт
	bool delete_product(int _code);
	// метод - вернуть итоговую сумму
	int total_cost() const { return total - (int)total_discount; }
};

Product::Product(int _barcode, int _price, string _name)
{
	if ((_barcode < 1) || (_barcode > 9999))
		throw "Неверный штрихкод\n";
	if (_price < 1)
		throw "Неверная цена\n";
	name = _name;
	price = _price;
	barcode = _barcode;
	discount = 1 + rand() % (50);
}

void Product::set_product(int _barcode, int _price, string _name)
{
	Product temp(_barcode, _price, _name);
	*this = temp;
}

void Product::product_check(int count) const
{
	cout << " " << name << endl;
	cout << setw(5) << right << count << setw(3) << " x " << setw(10) << left << price << setw(15) << right << " =" << goods_cost(count) << endl;
}

float Product::goods_discount(int count) const
{
	//if (count < 1)
		//throw "Неверное колтчество товаров";
	return price * count * discount / 100.;
}

int Product::goods_cost(int count) const
{
	//if (count < 1)
	//throw "Неверное колтчество товаров";
	return price * count;
}

Storage::Storage(string s)
{
	count = 0;
	ifstream fin("task5.txt");
	if (!fin.is_open())
		throw "нет такого файла\n";
	string temp;
	while (!fin.eof())
	{
		fin >> temp;
		if (temp.length() != 0)
		{
			int code = stoi(temp);
			string name;
			do
			{
				fin >> temp;
				name += temp;
				if (temp[temp.length() - 1] != '*')
					name += ' ';
			} while (temp[temp.length() - 1] != '*');
			name = name.substr(1, name.length() - 2);
			fin >> temp;
			int price = stoi(temp);
			Product t(code, price, name);
			goods.push_back(t);
			count++;
		}
	}
}

void Storage::print_barcodes() const
{
	for (int i = 0; i < count; i++)
	{
		int temp = goods[i].get_barcode();
		cout << temp / 1000 << (temp % 1000) / 100 << (temp % 100) / 10 << temp % 10 << endl;
	}
}

Product Storage::seach(int _code) const
{
	Product temp;
	for (int i = 0; i < count; i++)
		if (goods[i].get_barcode() == _code)
		{
			temp = goods[i];
			break;
		}
	return temp;
}

void Cashbox::scan_product(int _code)
{
	if ((_code < 1) || (_code > 9999))
		throw "Неверно введен штрихкод\n";
	code = _code;
	choosen = stock.seach(code);
}

Product Cashbox::get_description() const
{
	if (code == 0)
		throw "Не отсканирован товар\n";
	return choosen;
}

bool Cashbox::add_product(int count)
{
	if (count < 1)
		throw "Неверное число продуктов\n";
	bool flag = false;
	if (choosen.get_barcode() != 0)
	{
		int i;
		for (i = 0; i < quantity; i++)
			if (choosen_products[i].get_barcode() == code)
			{
				quantity_products[i] += count;
				break;
			}
		if (i == quantity)
		{
			choosen_products.push_back(choosen);
			quantity_products.push_back(count);
			quantity++;
		}
		flag = true;
		total += choosen.goods_cost(count);
		total_discount += choosen.goods_discount(count);
	}
	return flag;
}

void Cashbox::print_check() const
{
	if (quantity != 0)
	{
		for (int i = 0; i < quantity; i++)
		{
			choosen_products[i].product_check(quantity_products[i]);
		}
		cout << "Подитог: " << total << endl;
		cout << "Скидка: " << (int)total_discount << endl;
		cout << "Итог: " << total - (int)total_discount << endl;
	}
	else
		cout << "Ни один товар не добавлен в чек!" << endl;
}

bool Cashbox::delete_product(int _code)
{
	if ((_code < 1) || (_code > 9999))
		throw "Неверно введен штрихкод\n";
	for (int i = 0; i < quantity; i++)
	{
		if (choosen_products[i].get_barcode() == _code)
		{
			total_discount -= choosen_products[i].goods_discount(quantity_products[i]);
			total -= choosen_products[i].goods_cost(quantity_products[i]);
			choosen_products.erase(choosen_products.begin() + i);
			quantity_products.erase(quantity_products.begin() + i);
			quantity--;
			return 1;
		}
	}
	return 0;
}

ostream& operator<<(ostream &os, const Product &t)
{
	os << t.name << ": цена - " << t.price << " руб., скидка - " << t.discount << "%" << endl;
	return os;
}
int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Rus");
	char s[11] = "task5.txt";
	Storage stock(s);
	stock.print_barcodes();
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
	cout << "Добавили товар " << stock.seach(2341) << endl;
	d.print_check();
	cout << "Итоговая сумма: " << d.total_cost() << endl;
	cin >> a;
}