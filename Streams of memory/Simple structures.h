#pragma once
//Служебная структура, служащая для возвращения координат. Simple structures.h.
struct Location
{
	int x = 0, y = 0;
};

struct Borders//Структура для хранения информации о границах прямоугольной области. Simple structures.h
{
	int x_min = 0;//Левая граница.
	int x_max = 0;//Правая граница.
	int y_min = 0, y_max = 0;//Верхняя и нижняя границы.
};

