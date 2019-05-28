#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <fstream>
#include <iomanip>

using namespace std;

//����� - �������
class Product
{
	string name;
	int barcode;
	int discount;
	int price;
public:
	// ����������� �� ���������
	Product() : name("�� �����"), price(0), barcode(0), discount(0) {}
	// ����������� �������������
	Product(int _barcode, int _price, string _name);
	// ����� - ���������� �������
	void set_product(int _barcode, int _price, string _name);
	// ����� - ������� ��������
	int get_barcode() const { return barcode; }
	// ����� - ������ ���� � ���� �������
	void product_check(int count) const;
	// ����� - ��������� ������ n - ��� ����� �������
	float goods_discount(int count) const;
	// ����� - ��������� ��������� n - ��� ����� �������
	int goods_cost(int count) const;
	// ����� �� �������
	friend ostream& operator<<(ostream &os, const Product &t);
};

// ����� - �����
class Storage
{
	vector <Product> goods;
	int count;
public:
	Storage() : count(0) {}
	// ����������� �������������
	Storage(string s);
	// ����� - ������ ���������� ������� �� ������
	void print_barcodes() const;
	// ����� - ������ ������ �� ���������
	Product seach(int _code) const;
};