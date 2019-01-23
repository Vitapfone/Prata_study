#pragma once
#include "My_names.h"
#include "Simple structures.h"

using namespace My_names;



class Warning //����� ��������� �� ������� ���������� ���������� ���������.
{
	string message; //��������� � ���� �������������.
	Location loc;//���������� �������������.
	int importance = 10;//������� �������� ���������.

public:
	Warning() = default;
	Warning(const string & mes, const Location & l, int imp) : message(mes), loc(l), importance(imp) {}
	~Warning() {}

	//������� ���������� ���������.
	void what() const;

	//���������� �������������� �������������.
	Location where()const { return loc; }

	//���������� ��������.
	int get_importance()const { return importance; }
};

