#include <iostream>
#include <string>
#include <vector>
#include <locale.h>
#include <time.h>
#include <fstream>
#include <iomanip>

using namespace std;

class Product
{
	string name;
	int barcode;
	int discount;
	int price;
public:
	Product() : name("Не товар"), price(0), barcode(0), discount(0) {}
	Product(int _barcode, int _price, string _name)
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
	void set_product(int _barcode, int _price, string _name)
	{
		Product temp(_barcode, _price, _name);
		*this = temp;
	}
	int get_barcode() const { return barcode; }
	void product_check(int count) const
	{
		cout << " " << name << endl;
		cout << setw(5) << right << count << setw(3) << " x " << setw(10) << left << price << setw(15) << right << " =" << goods_cost(count) << endl;
	}
	float goods_discount(int count) const
	{
		//if (count < 1)
			//throw "Неверное колтчество товаров";
		return price * count * discount / 100.;
	}
	int goods_cost(int count) const
	{
		//if (count < 1)
		//throw "Неверное колтчество товаров";
		return price * count;
	}
	friend ostream& operator<<(ostream &os, const Product &t);
};

class Storage
{
	vector <Product> goods;
	int count;
public:
	Storage(string s = "task5.txt")
	{
		count = 0;
		ifstream fin(s);
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
	void print_barcodes() const
	{
		for (int i = 0; i < count; i++)
		{
			int temp = goods[i].get_barcode();
			cout << temp / 1000 << (temp % 1000) / 100 << (temp % 100) / 10 << temp % 10 << endl;
		}
	}
	Product seach(int _code) const
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
};
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
	Cashbox() : stock(), quantity(0), code(0), total(0), total_discount(0) { }
	void scan_product(int _code)
	{
		if ((_code < 1) || (_code > 9999))
			throw "Неверно введен штрихкод\n";
		code = _code;
		choosen = stock.seach(code);
	}
	Product get_description() const
	{
		if (code == 0)
			throw "Не отсканирован товар\n";
		return choosen;
	}
	bool add_product(int count = 1)
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

	void print_check() const
	{
		if (quantity != 0)
		{
			for (int i = 0; i < quantity; i++)
			{
				choosen_products[i].product_check(quantity_products[i]);
			}
			cout << "Подитог: " << total << endl;
			cout << "Скидка: " << total_discount << endl;
			cout << "Итог: " << total - total_discount << endl;
		}
		else
			cout << "Ни один товар не добавлен в чек!" << endl;
	}
	void delete_product(int _code)
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
			}
		}
	}
	int total_sum() const
	{
		return total - total_discount;
	}
};
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
		cin >> a;
		try
		{
			d.scan_product(a);
			cout << d.get_description() << endl;
			d.add_product(2);
		}
		catch (char  *s)
		{
			cout << s;
		}
		d.print_check();
	} 
	while (1 > 0);
	cin >> a;
}