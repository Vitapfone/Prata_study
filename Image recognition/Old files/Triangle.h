#pragma once
using std::cout; using std::endl;
struct Triangle : Figure //Структура, представляющая равнобедренный прямоугольный треугольник.
{
	size_t cathetus = 0;// Длина катета.
	size_t point_A_x = 0, point_A_y = 0;//Координаты вершины с прямым углом.
	size_t point_B_x = 0, point_B_y = 0; //Координаты второй вершины с острым углом. Координаты первой наследуются от Figure. 

	//КОНСТРУКТОРЫ
	Triangle() = default;
	Triangle(size_t x, size_t y, size_t cat) : Figure(x, y), cathetus(cat), point_A_x(x), point_A_y(y + cathetus), point_B_x(x + cathetus), point_B_y(y + cathetus)
	{
		//cout << point_A_x << " " << point_A_y << " " << point_B_x << " " << point_B_y << endl;
	}

	~Triangle() {}

	void print(Ar60_30 &ws); //Переопределение виртуальной функции из базового класса.

	template<size_t W, size_t H> void print(array<array<char, W>, H> & ws);//Отрисовка треугольника для рабочего пространства любого размера.

};

//Отрисовка треугольника для рабочего пространства любого размера.
template<size_t W, size_t H> void Triangle::print(array<array<char, W>, H> & ws)
{
	for (size_t y = y0; y <= point_A_y; ++y)
	{
		for (size_t x = x0; x <= point_B_x; ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//Условие, предохраняющее от выхода за границы массива.
			{
				if (x - x0 < y - y0)
				{
					ws[y][x] = '0';
				}
			}
		}
	}
}