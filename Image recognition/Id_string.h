#pragma once
#include "My_names.h"
using namespace My_names;

class Id_string
{
public:
	//������������
	Id_string() = default;
	//����������� �� ������.
	Id_string(const string &s) :data(s) { ++counter; id = counter;/* cout << id<< endl; */}
	//����������� �� ������ � id.
	Id_string(const string &s, int id):data(s), id(id)
	{
		if (counter < id)
			counter = id;
	}
	//����������� �� ��������� �����.
	Id_string(ifstream &);
	~Id_string() {}

	//������
	string get_data() const { return data; }//������ ����� �������� ������.
	int get_id() const { return id; }//������ �������������.

	//�������� � �������� ����.
	bool bin_write(ofstream & fout)const;

	//��������� �� ��������� �����.
	bool bin_read(ifstream & fin);

	//�������-������.

	//�������� ������ ��� ������ � ��������� ����.
	friend ostream& operator<< (ostream &, const Id_string &);

	friend istream& operator>>(istream&, Id_string &);

private:
	
	string data;
	int id = 0;
	static int counter;

};

