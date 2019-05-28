#pragma once
#include <iostream>
#include <string>
#include <vector>
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
	Storage() : count(0) {}
	// конструктор инициализатор
	Storage(string s);
	// метод - печать штрихкодов товаров со склада
	void print_barcodes() const;
	// метод - поиска товара по штрихкоду
	Product seach(int _code) const;
};