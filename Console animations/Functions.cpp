//Здесь определим необходимые для отображения квадрата функции.

#include "pch.h"
#include "Square.h"
using std::cout; using std::endl;

//Делает границы рабочего пространства видимыми.
void make_border(Ar60_30 & ar)
{
	for (int i = 0; i < 60; ++i)
	{
		ar[0][i] = '=';
		ar[29][i] = '=';
	}
	for (int j = 0; j < 30; ++j)
	{
		ar[j][0] = '!';
		ar[j][59] = '!';
	}
}

//Отрисовывает все рабочее пространство
void print_workspase(Ar60_30 & ar)
{
	make_border(ar);
	for (auto &e : ar)// Выводим в консоль.
	{
		for (auto &e2 : e)
		{
			cout << e2;
		}
		cout << endl;
	}
	cout << endl;

}