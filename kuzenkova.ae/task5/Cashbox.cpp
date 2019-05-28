#include "Cashbox.h"

void Cashbox::scan_product(int _code)
{
	if ((_code < 1) || (_code > 9999))
		throw "������� ������ ��������\n";
	code = _code;
	choosen = stock.seach(code);
}

Product Cashbox::get_description() const
{
	if (code == 0)
		throw "�� ������������ �����\n";
	return choosen;
}

bool Cashbox::add_product(int count)
{
	if (count < 1)
		throw "�������� ����� ���������\n";
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
		cout << "�������: " << total << endl;
		cout << "������: " << (int)total_discount << endl;
		cout << "����: " << total - (int)total_discount << endl;
	}
	else
		cout << "�� ���� ����� �� �������� � ���!" << endl;
}

bool Cashbox::delete_product(int _code)
{
	if ((_code < 1) || (_code > 9999))
		throw "������� ������ ��������\n";
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

Storage Cashbox::stock("task5.txt");