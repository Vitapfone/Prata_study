#pragma once
//Служебная структура, служащая для возвращения координат. Simple structures.h.
struct Location
{
	int x = 0, y = 0;
};

struct Borders//Структура для хранения информации о границах прямоугольной области. Simple structures.h
{
	int x_min;//Левая граница.
	int x_max;//Правая граница.
	int y_min, y_max;//Верхняя и нижняя границы.
};