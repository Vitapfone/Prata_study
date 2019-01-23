// List reverse.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "My_list.h"

using std::cin;

int main()
{
	My_list<int> li;
	
	//Заполняем для демонстрации.
	for (size_t i = 0; i < 11; i++)
	{
		li.insert(i);
	}
	li.show();

	li.reverse();//Разворачиваем.
	li.show();

	My_list<int> li2;
	std::forward_list<int> f_list;//Стандартный односвязный список для сравнения.

	cout << "Enter list size: ";
	int size;
	while (!(cin >> size))
	{
		cout << "Only digits!\n";
		cin.clear();
		cin.ignore(1000, '\n');
	}

	//Заполняем оба списка.
	clock_t fill_start = clock();
	for (size_t i = 0; i < size; i++)
	{
		li2.insert(i);
		f_list.emplace_front(i);
	}
	clock_t fill_end = clock();
	cout<<"Filling lists time is "<< (double)(fill_end - fill_start) / CLOCKS_PER_SEC << " seconds.\n";

	//Разворачиваем наш список и замеряем время, на это потраченное.
	clock_t my_start = clock();
	li2.reverse();
	clock_t my_end = clock();
	cout << "My_list reversing time is " << (double)(my_end - my_start) / CLOCKS_PER_SEC << " seconds.\n";

	////Аналогично для стандартного списка.
	clock_t std_start = clock();
	f_list.reverse();
	clock_t std_end = clock();
	cout << "Std forward_list reversing time is " << (double)(std_end - std_start) / CLOCKS_PER_SEC << " seconds.\n";

	return 0;
}

