#include "pch.h"

#include "Inspector.h"


//������� ���������, ����� ���� ��������� �����.
int Inspector::start_stop(bool &is_started, bool &is_finished, int &start_x, int &start_y)
{
	if (is_started == true && loc.x == start_x && loc.y == start_y)// ���� ����� ����� �����, � ���������� ���������� ����� ����������� ������ ������, �� ������ �� 
																// ������ ����, � ����� ����� ������� �����������.
	{
		is_finished = true;
		return 1;
	}
	if (is_started == false)//���� ����� ��� �� ���������,
	{
		is_started = true; // �� ��������� �����
		start_x = loc.x;// � ���������� ���������� ������.
		start_y = loc.y;
		
	}
	cout << "( " << loc.x << ", " << loc.y << " ) ";
	return 0;
}


