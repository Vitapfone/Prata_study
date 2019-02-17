#pragma once

#include "Image.h"

class Link
{
	int id = 0;//������������� ����� �����.
	static int counter;//����������� ������� ��� ��������� ���������� ����.

	Image* left_ptr = nullptr;//��������� �� ����� ������.
	int left_id = 0;//���� ����� �������.
	int left_strength = 0;//���� ����� ��� ����.

	Id_string* right_ptr = nullptr;//��������� �� ������ ������.
	int right_id = 0;
	int right_strength = 0;

public:

//������������

	Link() = default;
	//����������� � ������ ������������� ����������.
	Link(Image* l_ptr, int l_id, int l_str, Id_string* r_ptr, int r_id, int r_str) : left_ptr(l_ptr), left_id(l_id), left_strength(l_str),
		right_ptr(r_ptr), right_id(r_id), right_strength(r_str)
	{
		++counter;
		id = counter;
	}

//������

//�������

	//������ �������������
	int get_id() const { return id; }

	//������ ��������� �� ����� ������.
	Image* get_left_ptr() const { return left_ptr; }
	//������ ����� �������������.
	int get_left_id() const { return left_id; }
	//������ ����� ����.
	int get_left_strength() const { return left_strength; }

	//������ ��������� �� ������ ������.
	Id_string* get_right_ptr() const { return right_ptr; }
	//������ ������ �������������.
	int get_right_id() const{ return right_id; }
	//������ ������ ����.
	int get_right_strength() const { return right_strength; }

//�������

	//���������� ����� � ����� ��������.
	void set_left_obj(Image* l_ptr, int l_id, int l_str);
	//���������� ����� � ������ ��������.
	void set_right_obj(Id_string* r_ptr, int r_id, int r_str);
	//���������� ����.
	void set_id(int new_id);
};