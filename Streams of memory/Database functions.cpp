#include "pch.h"
#include "My_names.h"
#include "Simple structures.h"
#include "Id_string.h"
#include "Image.h"

using namespace My_names;

//���������� ���������� ����������� ���� ������ �� ������.
void database_initialization(const string & file1, const string & file2, map<int, Id_string> & strings, list<Image> & images)
{
	//������ ����� �� �����.

	ifstream ifs_str(file1, ifstream::binary);
	Id_string temp;//��������� ������ ������.

	while (temp.bin_read(ifs_str))//���� �� ��������� ����� �����.
	{
		strings[temp.get_id()] = temp;//��������� ����������� � �����.
	}

	//��������������� ������� �� ������.

	ifstream ifs_Images(file2, ifstream::binary);
	Image temp1;//��������� ������ ������.

	while (temp1.bin_read(ifs_Images))//������ �� ����� �� ��������� ������.
	{
		temp1.set_is_link(&strings[temp1.get_is_link().id]);//�������������� ������.
		temp1.set_non_link(&strings[temp1.get_non_link().id]);

		images.push_back(temp1);
	}
}

//������ ����������� ����������� � �����.
void database_recording(const string & file1, const string & file2, map<int, Id_string>& strings, list<Image>& images)
{
	ofstream ofstrings(file1, ofstream::binary);//������� ���� ��� ������ ��������� � �������� �����. ����� ������ ���� ������� �������.
	for (const auto &e : strings)//���������� ��� ������ �� �����.
	{
		e.second.bin_write(ofstrings);
	}
	
	ofstream ofsImages(file2, ofstream::binary);//������� ���� ��� ������ �������.
	for (const auto & e : images)
	{
		e.bin_write(ofsImages);
	}
}
