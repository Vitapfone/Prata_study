#include "pch.h"
#include "Id_string.h"

int Id_string::counter = 0;//������������� ������������ ����� ������ ���� � ��� ����������� � ������� ��������� �����.

//����������� �� ��������� �����.
Id_string::Id_string(ifstream & fin)
{
	
	size_t len;
	fin.read((char*)&len, sizeof len);

	char* buf = new char[len];
	fin.read(buf, len);
	data.assign(buf);
	delete[] buf;

	fin.read((char*)&id, sizeof id);

	if (counter < id)
		counter = id;
}

//�������� � �������� ����.
bool Id_string::bin_write(ofstream & fout) const
{
	size_t len = data.size() + 1;//�������� ������ ������, �������� ��������.
	fout.write((char*)&len, sizeof len);//���������� ���� ������.
	fout.write(data.c_str(), len);//���������� ���� ������.
	fout.write((char*)&id, sizeof id);//���������� id.

	if (fout)//��� ��� ������� ��������, ���������� true.
	{
		return true;
	}
	else
	{
		return false;
	}
}

//��������� �� ��������� �����.
bool Id_string::bin_read(ifstream & fin)
{
	//������ ����� ������.
	size_t len;
	if (!fin.read((char*)&len, sizeof len))//���� ������ ��������� (����� �����),
	{
		return false;//�� ���������� false.
	}

	//cout <<"LEN "<< len << endl;

	//�������� ��� ��� ������.
	shared_ptr<char> buf(new char[len]);
	
	fin.read(buf.get(), len);//������ � ��� ������.
	data.assign(buf.get());//����������� ���������� ������ ������.
	
	//������ id.
	fin.read((char*)&id, sizeof id);

	if (counter < id)
		counter = id;

	if (fin)//���� ��� ��������� �������, �� ���������� true.
	{
		return true;
	}
	else
	{
		return false;
	}
}

//�������� ������ ��� ������ � ��������� ����.
ostream & operator<<(ostream &os, const Id_string &ids)
{
	os << ids.data << "\n" << ids.id << endl;
	return os;
}

//�������� ��� ������ �� ���������� �����.
istream & operator>>(istream &is, Id_string & ids)
{
	std::getline(is, ids.data);
	is>>ids.id;
	is.ignore(1, '\n');
	if (Id_string::counter < ids.id)
		Id_string::counter = ids.id;
	return is;
}
