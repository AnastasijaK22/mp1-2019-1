#include <locale.h>
#include "Game_snake.h"
using namespace std;

HWND hwnd = GetConsoleWindow();
HDC hdc = GetDC(hwnd);

int main()
{
	setlocale(LC_ALL, "Rus");
	HANDLE hWnd = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD bufferSize = { 80, 50 };
	SetConsoleScreenBufferSize(hwnd, bufferSize);
	MoveWindow(hwnd, 50, 50, 1000, 1000, FALSE);
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	system("color F0");
	The_Lord_of_the_Snakes o;
	o.menu();
	Sleep(100);
	std::cin.ignore();
	return 0;
}