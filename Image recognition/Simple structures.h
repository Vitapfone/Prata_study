#pragma once
//��������� ���������, �������� ��� ����������� ���������. Simple structures.h.
struct Location
{
	int x = 0, y = 0;
};

struct Borders//��������� ��� �������� ���������� � �������� ������������� �������. Simple structures.h
{
	int x_min;//����� �������.
	int x_max;//������ �������.
	int y_min, y_max;//������� � ������ �������.
};