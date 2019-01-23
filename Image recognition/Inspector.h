#pragma once
#include "My_names.h"
#include "Simple structures.h"

using namespace My_names;

class Inspector
{
	
	Location loc{ 0, 0 };
	char bg = ' ';//Фон, по умолчанию пробел.
	char obj;//Объект.

public:

	//Конструктор.
	Inspector(int x, int y, char b, char o) : loc{ x, y }, bg(b), obj(o) {}


	//Методы движения.
	void moveLeft() { --loc.x; }
	void moveRight() { ++loc.x; }
	void moveUp() { --loc.y; }
	void moveDown() { ++loc.y; }

	//Функция обхода слева. Второй параметр определяет, будет обход по часовой стрелке или против.
	template<size_t W, size_t H> const Borders left_inspect(array<array<char, W>, H> &, bool);
private:
	//Функция определит, когда пора завершать обход.
	int start_stop(bool &, bool &, int &, int &);
};

//Функция обхода слева. Второй параметр определяет, будет обход по часовой стрелке или против.
template<size_t W, size_t H> const Borders Inspector::left_inspect(array<array<char, W>, H> &ws, bool clockwise)
{
	cout << "\nStart left-inspecting..." << endl;
	set<int> xset, yset; //Списки координат, пройденных инспектором.

	bool is_finished = false; //Переменная, сообщающая о том, завершен ли обход.
	bool is_started = false; //Переменная, сообщающая о том, начат ли обход.

	int start_x, start_y; //Переменные для хранения координат начала поиска.


	while (!is_finished)//Пока обход не закончен.
	{

		//Если все эл-ты вокруг инспектора принадлежат объекту, то сдвигаем его влево.
		if (ws[loc.y - 1][loc.x - 1] == obj && ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == obj && ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == obj && ws[loc.y + 1][loc.x] == obj
			&& ws[loc.y + 1][loc.x - 1] == obj && ws[loc.y][loc.x - 1] == obj)
		{
			cout << " moveLeft... " << loc.x << " " << loc.y;
			moveLeft();
			//continue;
		}
		else 
		if (ws[loc.y + 1][loc.x - 1] == bg && ws[loc.y][loc.x - 1] == bg && ws[loc.y - 1][loc.x - 1] == bg //Граница слева
			&& ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == obj && ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == obj && ws[loc.y + 1][loc.x] == obj)
		{

			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);//Заносим координаты в списки.
			yset.insert(loc.y);

			(clockwise) ? moveUp() : moveDown();
			//continue;
		}
		else
		if (ws[loc.y + 1][loc.x - 1] == bg && ws[loc.y][loc.x - 1] == bg && ws[loc.y - 1][loc.x - 1] == bg && ws[loc.y - 1][loc.x] == bg && ws[loc.y - 1][loc.x + 1] == bg
			&& ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == obj && ws[loc.y + 1][loc.x] == obj)//В верхнем левом углу.
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveRight() : moveDown();
			//continue;
		}
		else
		if (ws[loc.y - 1][loc.x - 1] == bg && ws[loc.y - 1][loc.x] == bg && ws[loc.y - 1][loc.x + 1] == bg //Граница сверху.
			&& ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == obj && ws[loc.y + 1][loc.x] == obj && ws[loc.y + 1][loc.x - 1] == obj && ws[loc.y][loc.x - 1] == obj)
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveRight() : moveLeft();
			//continue;
		}
		else
		if (ws[loc.y - 1][loc.x - 1] == bg && ws[loc.y - 1][loc.x] == bg && ws[loc.y - 1][loc.x + 1] == bg && ws[loc.y][loc.x + 1] == bg && ws[loc.y + 1][loc.x + 1] == bg
			&& ws[loc.y + 1][loc.x] == obj && ws[loc.y + 1][loc.x - 1] == obj && ws[loc.y][loc.x - 1] == obj)//В верхнем правом углу.
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveDown() : moveLeft();
			//continue;
		}
		else
		if (ws[loc.y - 1][loc.x + 1] == bg && ws[loc.y][loc.x + 1] == bg && ws[loc.y + 1][loc.x + 1] == bg //Граница справа
			&& ws[loc.y + 1][loc.x] == obj && ws[loc.y + 1][loc.x - 1] == obj && ws[loc.y][loc.x - 1] == obj && ws[loc.y - 1][loc.x - 1] == obj && ws[loc.y - 1][loc.x] == obj)
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveDown() : moveUp();
			//continue;
		}
		else
		if (ws[loc.y - 1][loc.x + 1] == bg && ws[loc.y][loc.x + 1] == bg && ws[loc.y + 1][loc.x + 1] == bg && ws[loc.y + 1][loc.x] == bg && ws[loc.y + 1][loc.x - 1] == bg
			&& ws[loc.y][loc.x - 1] == obj && ws[loc.y - 1][loc.x - 1] == obj && ws[loc.y - 1][loc.x] == obj)//В нижнем правом углу.
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveLeft() : moveUp();
			//continue;
		}
		else
		if (ws[loc.y + 1][loc.x + 1] == bg && ws[loc.y + 1][loc.x] == bg && ws[loc.y + 1][loc.x - 1] == bg //Граница снизу.
			&& ws[loc.y][loc.x - 1] == obj && ws[loc.y - 1][loc.x - 1] == obj && ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == obj && ws[loc.y][loc.x + 1] == obj)
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveLeft() : moveRight();
			//continue;
		}
		else
		if (ws[loc.y + 1][loc.x + 1] == bg && ws[loc.y + 1][loc.x] == bg && ws[loc.y + 1][loc.x - 1] == bg && ws[loc.y][loc.x - 1] == bg && ws[loc.y - 1][loc.x - 1] == bg
			&& ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == obj && ws[loc.y][loc.x + 1] == obj)//В нижнем левом углу.
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveUp() : moveRight();
			//continue;
		}
		else
		if (ws[loc.y + 1][loc.x - 1] == bg && ws[loc.y][loc.x - 1] == bg
			&& ws[loc.y - 1][loc.x - 1] == obj && ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == obj && ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == obj && ws[loc.y + 1][loc.x] == obj)
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveUp() : moveDown();
			//continue;
		}
		else
		if (ws[loc.y + 1][loc.x - 1] == bg && ws[loc.y - 1][loc.x - 1] == bg
			&& ws[loc.y][loc.x - 1] == obj && ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == obj && ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == obj && ws[loc.y + 1][loc.x] == obj)
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x - 1);
			yset.insert(loc.y);

			(clockwise) ? moveUp() : moveDown();
			//continue;
		}
		else
		if (ws[loc.y][loc.x - 1] == bg && ws[loc.y - 1][loc.x - 1] == bg
			&& ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == obj && ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == obj && ws[loc.y + 1][loc.x] == obj && ws[loc.y + 1][loc.x - 1] == obj)
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveUp() : moveDown();
			//continue;
		}
		else
		if (ws[loc.y + 1][loc.x - 1] == bg && ws[loc.y][loc.x - 1] == bg && ws[loc.y - 1][loc.x - 1] == bg && ws[loc.y - 1][loc.x] == bg
			&& ws[loc.y - 1][loc.x + 1] == obj && ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == obj && ws[loc.y + 1][loc.x] == obj)
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveRight() : moveDown();
			//continue;
		}
		else
		if (ws[loc.y - 1][loc.x - 1] == bg
			&& ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == obj && ws[loc.y][loc.x + 1] == obj && ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == obj && ws[loc.y + 1][loc.x] == obj
			&& ws[loc.y + 1][loc.x - 1] == obj && ws[loc.y][loc.x - 1] == obj)
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveUp() : moveLeft();
			//continue;
		}
		else
		if (ws[loc.y][loc.x - 1] == bg && ws[loc.y - 1][loc.x - 1] == bg && ws[loc.y - 1][loc.x] == bg && ws[loc.y - 1][loc.x + 1] == bg
			&& ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == obj && ws[loc.y + 1][loc.x] == obj && ws[loc.y + 1][loc.x - 1] == obj)
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveRight() : moveDown();
			//continue;
		}
		else
		if (ws[loc.y - 1][loc.x - 1] == bg && ws[loc.y - 1][loc.x] == bg
			&& ws[loc.y - 1][loc.x + 1] == obj && ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == obj && ws[loc.y + 1][loc.x] == obj && ws[loc.y + 1][loc.x - 1] == obj && ws[loc.y][loc.x - 1] == obj)
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveRight() : moveLeft();
			//continue;
		}
		else
		if (ws[loc.y - 1][loc.x - 1] == bg && ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == bg
			&& ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == obj && ws[loc.y + 1][loc.x] == obj && ws[loc.y + 1][loc.x - 1] == obj && ws[loc.y][loc.x - 1])
		{
			cout << "pos 8, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y - 1);

			(clockwise) ? moveRight() : moveLeft();
			//continue;
		}
		else
		if (ws[loc.y - 1][loc.x] == bg && ws[loc.y - 1][loc.x + 1] == bg
			&& ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == obj && ws[loc.y + 1][loc.x] == obj && ws[loc.y + 1][loc.x - 1] == obj && ws[loc.y][loc.x - 1] == obj && ws[loc.y - 1][loc.x - 1] == obj)
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveRight() : moveLeft();
			//continue;
		}
		else
		if (ws[loc.y - 1][loc.x - 1] == bg && ws[loc.y - 1][loc.x] == bg && ws[loc.y - 1][loc.x + 1] == bg && ws[loc.y][loc.x + 1] == bg
			&& ws[loc.y + 1][loc.x + 1] == obj && ws[loc.y + 1][loc.x] == obj && ws[loc.y + 1][loc.x - 1] == obj && ws[loc.y][loc.x - 1] == obj)
		{
			cout << "pos 10, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveDown() : moveLeft();
			//continue;
		}
		else
		if (ws[loc.y - 1][loc.x + 1] == bg
			&& ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == obj && ws[loc.y + 1][loc.x] == obj && ws[loc.y + 1][loc.x - 1] == obj && ws[loc.y][loc.x - 1] == obj && ws[loc.y - 1][loc.x - 1] == obj
			&& ws[loc.y - 1][loc.x] == obj)
		{
			cout << "pos 11, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveRight() : moveUp();
			//continue;
		}
		else
		if (ws[loc.y - 1][loc.x] == bg && ws[loc.y - 1][loc.x + 1] == bg && ws[loc.y][loc.x + 1] == bg && ws[loc.y + 1][loc.x + 1] == bg
			&& ws[loc.y + 1][loc.x] == obj && ws[loc.y + 1][loc.x - 1] == obj && ws[loc.y][loc.x - 1] == obj && ws[loc.y - 1][loc.x - 1] == obj)
		{
			cout << "pos 12, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveDown() : moveLeft();
			//continue;
		}
		else
		if (ws[loc.y - 1][loc.x + 1] == bg && ws[loc.y][loc.x + 1] == bg
			&& ws[loc.y + 1][loc.x + 1] == obj && ws[loc.y + 1][loc.x] == obj && ws[loc.y + 1][loc.x - 1] == obj && ws[loc.y][loc.x - 1] == obj && ws[loc.y - 1][loc.x - 1] == obj && ws[loc.y - 1][loc.x] == obj)
		{
			cout << "pos 13, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveDown() : moveUp();
			//continue;
		}
		else
		if (ws[loc.y - 1][loc.x + 1] == bg && ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == bg
			&& ws[loc.y + 1][loc.x] == obj && ws[loc.y + 1][loc.x - 1] == obj && ws[loc.y][loc.x - 1] == obj && ws[loc.y - 1][loc.x - 1] == obj && ws[loc.y - 1][loc.x] == obj)
		{
			cout << "pos 14, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x + 1);
			yset.insert(loc.y);

			(clockwise) ? moveDown() : moveUp();
			//continue;
		}
		else
		if (ws[loc.y][loc.x + 1] == bg && ws[loc.y + 1][loc.x + 1] == bg
			&& ws[loc.y + 1][loc.x] == obj && ws[loc.y + 1][loc.x - 1] == obj && ws[loc.y][loc.x - 1] == obj && ws[loc.y - 1][loc.x - 1] == obj && ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == obj)
		{
			cout << "pos 15, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveDown() : moveUp();
			//continue;
		}
		else
		if (ws[loc.y - 1][loc.x + 1] == bg && ws[loc.y][loc.x + 1] == bg && ws[loc.y + 1][loc.x + 1] == bg && ws[loc.y + 1][loc.x] == bg
			&& ws[loc.y + 1][loc.x - 1] == obj && ws[loc.y][loc.x - 1] == obj && ws[loc.y - 1][loc.x - 1] == obj && ws[loc.y - 1][loc.x] == obj)
		{
			cout << "pos 16, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveLeft() : moveUp();
			//continue;
		}
		else
		if (ws[loc.y + 1][loc.x + 1] == bg
			&& ws[loc.y + 1][loc.x] == obj && ws[loc.y + 1][loc.x - 1] == obj && ws[loc.y][loc.x - 1] == obj && ws[loc.y - 1][loc.x - 1] == obj && ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == obj
			&& ws[loc.y][loc.x + 1] == obj)
		{
			cout << "pos 17, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveDown() : moveRight();
			//continue;
		}
		else
		if (ws[loc.y][loc.x + 1] == bg && ws[loc.y + 1][loc.x + 1] == bg && ws[loc.y + 1][loc.x] == bg && ws[loc.y + 1][loc.x - 1] == bg
			&& ws[loc.y][loc.x - 1] == obj && ws[loc.y - 1][loc.x - 1] == obj && ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == obj)
		{
			cout << "pos 18, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveLeft() : moveUp();
			//continue;
		}
		else
		if (ws[loc.y + 1][loc.x + 1] == bg && ws[loc.y + 1][loc.x] == bg
			&& ws[loc.y + 1][loc.x - 1] == obj && ws[loc.y][loc.x - 1] == obj && ws[loc.y - 1][loc.x - 1] == obj && ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == obj && ws[loc.y][loc.x + 1] == obj)
		{
			cout << "pos 19, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveLeft() : moveRight();
			//continue;
		}
		else
		if (ws[loc.y + 1][loc.x + 1] == bg && ws[loc.y + 1][loc.x] == obj && ws[loc.y + 1][loc.x - 1] == bg
			&& ws[loc.y][loc.x - 1] == obj && ws[loc.y - 1][loc.x - 1] == obj && ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == obj && ws[loc.y][loc.x + 1] == obj)
		{
			cout << "pos 20, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y + 1);

			(clockwise) ? moveLeft() : moveRight();
			//continue;
		}
		else
		if (ws[loc.y + 1][loc.x] == bg && ws[loc.y + 1][loc.x - 1] == bg
			&& ws[loc.y][loc.x - 1] == obj && ws[loc.y - 1][loc.x - 1] == obj && ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == obj && ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == obj)
		{
			cout << "pos 21, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveLeft() : moveRight();
			//continue;
		}
		else
		if (ws[loc.y + 1][loc.x + 1] == bg && ws[loc.y + 1][loc.x] == bg && ws[loc.y + 1][loc.x - 1] == bg && ws[loc.y][loc.x - 1] == bg
			&& ws[loc.y - 1][loc.x - 1] == obj && ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == obj && ws[loc.y][loc.x + 1] == obj)
		{
			cout << "pos 22, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveUp() : moveRight();
			//continue;
		}
		else
		if (ws[loc.y + 1][loc.x - 1] == bg
			&& ws[loc.y][loc.x - 1] == obj && ws[loc.y - 1][loc.x - 1] == obj && ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == obj && ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == obj
			&& ws[loc.y + 1][loc.x] == obj)
		{
			cout << "pos 23 ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveLeft() : moveDown();
			//continue;
		}
		else
		if (ws[loc.y + 1][loc.x] == bg && ws[loc.y + 1][loc.x - 1] == bg && ws[loc.y][loc.x - 1] == bg && ws[loc.y - 1][loc.x - 1] == bg
			&& ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == obj && ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == obj)
		{
			cout << "pos 24, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveUp() : moveRight();
			//continue;
		}
		else
		if (ws[loc.y][loc.x - 1] == bg && ws[loc.y - 1][loc.x - 1] == bg && ws[loc.y - 1][loc.x] == bg
			&& ws[loc.y - 1][loc.x + 1] == obj && ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == obj && ws[loc.y + 1][loc.x] == obj && ws[loc.y + 1][loc.x - 1] == obj)
		{
			cout << "pos 25, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveRight() : moveDown();
			//continue;
		}
		else
		if (ws[loc.y - 1][loc.x] == bg && ws[loc.y - 1][loc.x + 1] == bg && ws[loc.y][loc.x + 1] == bg
			&& ws[loc.y + 1][loc.x + 1] == obj && ws[loc.y + 1][loc.x] == obj && ws[loc.y + 1][loc.x - 1] == obj && ws[loc.y][loc.x - 1] == obj && ws[loc.y - 1][loc.x - 1] == obj)
		{
			cout << "pos 26, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveDown() : moveLeft();
			//continue;
		}
		else
		if (ws[loc.y][loc.x + 1] == bg && ws[loc.y + 1][loc.x + 1] == bg && ws[loc.y + 1][loc.x] == bg
			&& ws[loc.y + 1][loc.x - 1] == obj && ws[loc.y][loc.x - 1] == obj && ws[loc.y - 1][loc.x - 1] == obj && ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == obj)
		{
			cout << "pos 27, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveLeft() : moveUp();
			//continue;
		}
		else
		if (ws[loc.y + 1][loc.x] == bg && ws[loc.y + 1][loc.x - 1] == bg && ws[loc.y][loc.x - 1] == bg
			&& ws[loc.y - 1][loc.x - 1] == obj && ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == obj && ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == obj)
		{
			cout << "pos 28.";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveUp() : moveRight();
			//continue;
		}
		else
		if (ws[loc.y][loc.x - 1] == bg && ws[loc.y - 1][loc.x - 1] == bg && ws[loc.y - 1][loc.x] == bg && ws[loc.y - 1][loc.x + 1] == bg && ws[loc.y][loc.x + 1] == bg
			&& ws[loc.y + 1][loc.x + 1] == obj && ws[loc.y + 1][loc.x] == obj && ws[loc.y + 1][loc.x - 1] == obj)
		{
			cout << "pos 29 ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			start_y = loc.y + 1;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveDown() : moveDown();
			//continue;
		}
		else
		if (ws[loc.y - 1][loc.x + 1] == bg && ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == bg && ws[loc.y + 1][loc.x] == bg && ws[loc.y + 1][loc.x - 1] == bg
			&& ws[loc.y][loc.x - 1] == obj && ws[loc.y - 1][loc.x - 1] == obj && ws[loc.y - 1][loc.x] == obj)
		{
			cout << "pos 30 ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x + 1);
			yset.insert(loc.y);

			(clockwise) ? moveLeft() : moveUp();
			//continue;
		}
		else
		if (ws[loc.y + 1][loc.x - 1] == bg && ws[loc.y][loc.x - 1] == bg && ws[loc.y - 1][loc.x - 1] == bg && ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == bg
			&& ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == obj && ws[loc.y + 1][loc.x] == obj)
		{
			cout << "pos 31 ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y - 1);

			(clockwise) ? moveRight() : moveDown();
			//continue;
		}
		else
		if (ws[loc.y + 1][loc.x + 1] == bg && ws[loc.y + 1][loc.x] == bg && ws[loc.y + 1][loc.x - 1] == bg && ws[loc.y][loc.x - 1] == obj && ws[loc.y - 1][loc.x - 1] == bg
			&& ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == obj && ws[loc.y][loc.x + 1] == obj)
		{
			cout << "pos 32 ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x - 1);
			yset.insert(loc.y);

			(clockwise) ? moveUp() : moveRight();
			//continue;
		}
		else
		if (ws[loc.y - 1][loc.x - 1] == bg && ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == bg && ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == bg && ws[loc.y + 1][loc.x] == obj
			&& ws[loc.y + 1][loc.x - 1] == bg && ws[loc.y][loc.x - 1] == obj)
		{
			cout << "pos 33 ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x - 1), xset.insert(loc.x), xset.insert(loc.x + 1);
			yset.insert(loc.y - 1), yset.insert(loc.y), yset.insert(loc.y + 1);
			//continue;
		}
	}

	return { *xset.begin(), *xset.rbegin(), *yset.begin(), *yset.rbegin() }; //Возвращаем сконструированную на месте стр-ру, содержащую наименьшие и наибольшие координаты, 
																			//пройденные инспектором.
}
