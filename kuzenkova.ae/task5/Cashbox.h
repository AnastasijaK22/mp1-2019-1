#pragma once
#include "Storage.h"

// класс - касса
class Cashbox
{
	static Storage &stock;
	vector <Product> choosen_products;
	vector <int> quantity_products;
	int quantity;
	int code;
	Product choosen;
	int total;
	float total_discount;
public:
	// конструктор по умолчанию
	Cashbox() : quantity(0), code(0), total(0), total_discount(0) { }
	static void set_storage(Storage temp)
	{
		Cashbox::stock = temp;
	};
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