#pragma once
#include "Storage.h"

// ����� - �����
class Cashbox
{
	static Storage stock;
	vector <Product> choosen_products;
	vector <int> quantity_products;
	int quantity;
	int code;
	Product choosen;
	int total;
	float total_discount;
public:
	// ����������� �� ���������
	Cashbox() : quantity(0), code(0), total(0), total_discount(0) { }
	static void set_storage(string s)
	{
		Storage temp(s);
		Cashbox::stock = temp;
	};
	// ����� - ����������� �����
	void scan_product(int _code);
	// ����� - ������� �������� ������
	Product get_description() const;
	// ����� - �������� ����� � ���
	bool add_product(int count = 1);
	// ����� - ������ ����
	void print_check() const;
	// ����� - ������� �������
	bool delete_product(int _code);
	// ����� - ������� �������� �����
	int total_cost() const { return total - (int)total_discount; }
};