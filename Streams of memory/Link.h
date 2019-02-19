#pragma once

#include "Image.h"

class Link
{
	int id = 0;//������������� ����� �����.
	static int counter;//����������� ������� ��� ��������� ���������� ����.

	char time_date[26] = { '\0' };//����� � ���� �������� �����.

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
	Link(Image* l_ptr, int l_id, int l_str, Id_string* r_ptr, int r_id, int r_str); 
	

//������

//�������

	//������ �������������
	int get_id() const { return id; }
	//������ �������� ��������.
	int get_counter() const{ return counter; }
	//������ ���������� � ���� � ������� ��������.
	const string get_time_date() const { return time_date; }

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
	//���������� ��������� �� ����� ������.
	void set_left_ptr(Image* l_ptr) { left_ptr = l_ptr; }
	//���������� �������� ������ �������
	void set_left_attr(int l_id, int l_str) { left_id = l_id; left_strength = l_str; }

	//���������� ����� � ������ ��������.
	void set_right_obj(Id_string* r_ptr, int r_id, int r_str);
	//���������� ��������� �� ������ ������.
	void set_right_ptr(Id_string* r_ptr) { right_ptr = r_ptr; }
	//���������� �������� ������� �������.
	void set_right_attr(int r_id, int r_str) { right_id = r_id; right_strength = r_str; }

	//���������� ����.
	void set_id(int new_id);
	//���������� �������.
	void set_counter(int new_counter) { counter = new_counter; }
	//���������������� ���������� � ���� � ������� ��������.
	void Time_date();
	//���������� ���������� � ���� � ������� ��������.
	void set_time_date(const string & t_d) { strcpy_s(time_date, 26, t_d.c_str()); }
	void set_time_date(const char* t_d){ strcpy_s(time_date, 26, t_d); }
};


//�� �����

namespace Links
{
	//�������� ����� � �������� ����.
	bool bin_write(ofstream & fout, const Link & link);

	//��������� ����� �� ��������� �����.
	bool bin_read(ifstream & fin, Link & link);
}