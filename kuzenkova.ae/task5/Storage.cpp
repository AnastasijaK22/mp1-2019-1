#include "Storage.h"

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

ostream& operator<<(ostream &os, const Product &t)
{
	os << t.name << ": цена - " << t.price << " руб., скидка - " << t.discount << "%" << endl;
	return os;
}