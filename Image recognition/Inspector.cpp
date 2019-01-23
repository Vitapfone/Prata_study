#include "pch.h"

#include "Inspector.h"


//Функция определит, когда пора завершать обход.
int Inspector::start_stop(bool &is_started, bool &is_finished, int &start_x, int &start_y)
{
	if (is_started == true && loc.x == start_x && loc.y == start_y)// Если обход начат ранее, и координаты инспектора равны координатам старта обхода, то значит он 
																// сделал круг, и обход можно считать завершенным.
	{
		is_finished = true;
		return 1;
	}
	if (is_started == false)//Если обход еще не стартовал,
	{
		is_started = true; // то объявляем старт
		start_x = loc.x;// и запоминаем координаты старта.
		start_y = loc.y;
		
	}
	cout << "( " << loc.x << ", " << loc.y << " ) ";
	return 0;
}


