#pragma once
#include "My_names.h"
#include "Simple structures.h"

using namespace My_names;

class Inspector
{
	
	Location loc{ 0, 0 };
	char bg = ' ';//���, �� ��������� ������.
	char obj;//������.

public:

	//�����������.
	Inspector(int x, int y, char b, char o) : loc{ x, y }, bg(b), obj(o) {}


	//������ ��������.
	void moveLeft() { --loc.x; }
	void moveRight() { ++loc.x; }
	void moveUp() { --loc.y; }
	void moveDown() { ++loc.y; }

	//������� ������ �����. ������ �������� ����������, ����� ����� �� ������� ������� ��� ������.
	template<size_t W, size_t H> const Borders left_inspect(array<array<char, W>, H> &, bool);
private:
	//������� ���������, ����� ���� ��������� �����.
	int start_stop(bool &, bool &, int &, int &);
};

//������� ������ �����. ������ �������� ����������, ����� ����� �� ������� ������� ��� ������.
template<size_t W, size_t H> const Borders Inspector::left_inspect(array<array<char, W>, H> &ws, bool clockwise)
{
	cout << "\nStart left-inspecting..." << endl;
	set<int> xset, yset; //������ ���������, ���������� �����������.

	bool is_finished = false; //����������, ���������� � ���, �������� �� �����.
	bool is_started = false; //����������, ���������� � ���, ����� �� �����.

	int start_x, start_y; //���������� ��� �������� ��������� ������ ������.


	while (!is_finished)//���� ����� �� ��������.
	{

		//���� ��� ��-�� ������ ���������� ����������� �������, �� �������� ��� �����.
		if (ws[loc.y - 1][loc.x - 1] == obj && ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == obj && ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == obj && ws[loc.y + 1][loc.x] == obj
			&& ws[loc.y + 1][loc.x - 1] == obj && ws[loc.y][loc.x - 1] == obj)
		{
			cout << " moveLeft... " << loc.x << " " << loc.y;
			moveLeft();
			//continue;
		}
		else 
		if (ws[loc.y + 1][loc.x - 1] == bg && ws[loc.y][loc.x - 1] == bg && ws[loc.y - 1][loc.x - 1] == bg //������� �����
			&& ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == obj && ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == obj && ws[loc.y + 1][loc.x] == obj)
		{

			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);//������� ���������� � ������.
			yset.insert(loc.y);

			(clockwise) ? moveUp() : moveDown();
			//continue;
		}
		else
		if (ws[loc.y + 1][loc.x - 1] == bg && ws[loc.y][loc.x - 1] == bg && ws[loc.y - 1][loc.x - 1] == bg && ws[loc.y - 1][loc.x] == bg && ws[loc.y - 1][loc.x + 1] == bg
			&& ws[loc.y][loc.x + 1] == obj && ws[loc.y + 1][loc.x + 1] == obj && ws[loc.y + 1][loc.x] == obj)//� ������� ����� ����.
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveRight() : moveDown();
			//continue;
		}
		else
		if (ws[loc.y - 1][loc.x - 1] == bg && ws[loc.y - 1][loc.x] == bg && ws[loc.y - 1][loc.x + 1] == bg //������� ������.
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
			&& ws[loc.y + 1][loc.x] == obj && ws[loc.y + 1][loc.x - 1] == obj && ws[loc.y][loc.x - 1] == obj)//� ������� ������ ����.
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveDown() : moveLeft();
			//continue;
		}
		else
		if (ws[loc.y - 1][loc.x + 1] == bg && ws[loc.y][loc.x + 1] == bg && ws[loc.y + 1][loc.x + 1] == bg //������� ������
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
			&& ws[loc.y][loc.x - 1] == obj && ws[loc.y - 1][loc.x - 1] == obj && ws[loc.y - 1][loc.x] == obj)//� ������ ������ ����.
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc.x);
			yset.insert(loc.y);

			(clockwise) ? moveLeft() : moveUp();
			//continue;
		}
		else
		if (ws[loc.y + 1][loc.x + 1] == bg && ws[loc.y + 1][loc.x] == bg && ws[loc.y + 1][loc.x - 1] == bg //������� �����.
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
			&& ws[loc.y - 1][loc.x] == obj && ws[loc.y - 1][loc.x + 1] == obj && ws[loc.y][loc.x + 1] == obj)//� ������ ����� ����.
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

	return { *xset.begin(), *xset.rbegin(), *yset.begin(), *yset.rbegin() }; //���������� ����������������� �� ����� ���-��, ���������� ���������� � ���������� ����������, 
																			//���������� �����������.
}
