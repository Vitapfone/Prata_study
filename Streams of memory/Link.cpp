#include "pch.h"
#include "Link.h"

int Link::counter = 0;//������������� ��������.

//����������� � ������ ������������� ����������.
Link::Link(Image * l_ptr, int l_id, int l_str, Id_string * r_ptr, int r_id, int r_str): left_ptr(l_ptr), left_id(l_id), left_strength(l_str),
		right_ptr(r_ptr), right_id(r_id), right_strength(r_str)
{
	//���������� �������� � ��������� ����.
	++counter;
	id = counter;

	//������ ���� � ������� ��������.
	const time_t timer = time(0);
	ctime_s(time_date, 26, &timer);
}

//���������� ����� � ����� ��������.
inline void Link::set_left_obj(Image * l_ptr, int l_id, int l_str)
{
	left_ptr		= l_ptr;
	left_id			= l_id;
	left_strength	= l_str;
}

//���������� ����� � ������ ��������.
inline void Link::set_right_obj(Id_string * r_ptr, int r_id, int r_str)
{
	right_ptr		= r_ptr;
	right_id		= r_id;
	right_strength	= r_str;
}

//���������� ����.
inline void Link::set_id(int new_id)
{
	id = new_id;
	if (counter < id)
		counter = id;
}

//���������������� ���������� � ���� � ������� ��������.
inline void Link::Time_date()
{
	const time_t timer = time(0);
	ctime_s(time_date, 26, &timer);
}

//�������� ����� � �������� ����.
bool Link::bin_write(ofstream & fout) const
{
	fout.write((char*)&id, sizeof(id));
	fout.write(time_date, 26);
	fout.write((char*)&left_id, sizeof(left_id));
	fout.write((char*)&left_strength, sizeof(left_strength));
	fout.write((char*)&right_id, sizeof(right_id));
	fout.write((char*)&right_strength, sizeof(right_strength));

	if (fout)//��� ��� ������� ��������, ���������� true.
	{
		return true;
	}
	else
	{
		return false;
	}
}

//��������� ����� �� ��������� �����.
bool Link::bin_read(ifstream & fin)
{
	using std::swap;	//������������ ����� "copy and swap" ��� ������������ ��� ����������.

	Link temp;			//��������� ��������� ������, � ������� � ���������� ��� ���������.

	//��������� ����.
	if (!fin.read((char*)&temp.id, sizeof id))
	{
		return false;
	}

	fin.read(temp.time_date, 26);
	fin.read((char*)&temp.left_id, sizeof(left_id));
	fin.read((char*)&temp.left_strength, sizeof(left_strength));
	fin.read((char*)&temp.right_id, sizeof(right_id));
	fin.read((char*)&temp.right_strength, sizeof(right_strength));

	if (!fin)//���� ��������� ����, �� ����� ���������� �����.
	{
		return false;
	}

	//���� ��� ������ ��� ����������, �� ��������� ������ ������������ � ����������.
	swap(*this, temp);

	//��������� �������,���� ����.
	if (counter < id)
		counter = id;

	return true;
}
