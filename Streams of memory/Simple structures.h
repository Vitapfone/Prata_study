#pragma once

//Служебная структура, служащая для возвращения координат. Simple structures.h.
struct Location
{
	int x_ = 0, y_ = 0;
};

struct Borders//Структура для хранения информации о границах прямоугольной области. Simple structures.h
{
	int		x_min_ = 0;				//Левая граница.
	int		x_max_ = 0;				//Правая граница.
	int		y_min_ = 0, y_max_ = 0;	//Верхняя и нижняя границы.
};

