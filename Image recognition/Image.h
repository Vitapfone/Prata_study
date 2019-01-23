#pragma once
#include "My_names.h"
#include "Id_string.h"
#include "Simple structures.h"

using namespace My_names;

class Image
{
	vector<vector<bool>> data;// ������ ������� ��������, ��� ����� ��������� �����.

	size_t width = 0, height = 0; //������ � ������ ������.
	double aspect_rate = 0.0;//��������� ������ � ������.

	Id_string *is_ps = nullptr;//���������, ����������� ����� ������������� ����� ������� ������.
	int id_is_ps = 0;//������������� ��� ����� ���������, �������� ����� ����� ��� ������.
	Id_string *non_ps = nullptr;
	int id_non_ps = 0;

public:
	Image() = default;
	//����������� �������� ���������� ������ �� ������ ��������������� ���������� ���������.
	template<size_t W, size_t H> 
	Image(const Borders & bs, array<array<char, W>, H> &, char, char);
	//����������� �������� ���������� ������ �� ��������� �����.
	Image(ifstream &);

	~Image() {}

	//������

	size_t get_widht() const { return width; }//������ ������.
	size_t get_height() const { return height; }//������ ������.
	double get_aspect() const { return aspect_rate; }//������ ��������� ������ � ������.
	Id_string * get_is_ps() const { return is_ps; }//������ �������� ���������.
	Id_string * get_non_ps() const { return non_ps; }

	int get_id_is_ps() const { return id_is_ps; }//������ ������������� ���������.
	int get_id_non_ps() const { return id_non_ps; }
	
	void set_is_ps(Id_string* other) { is_ps = other; id_is_ps = other->get_id(); }//���������� ����� ��������� � ������ ������� � ���������������.
	void set_non_ps(Id_string* other) { non_ps = other; id_non_ps = other->get_id(); }

	//������� � ������� ����� � ������� ��� ���������� ����.
	void visualize();

	//��������� �� ��������� �����.
	bool bin_read(ifstream & fin);

	//�������� � �������� ����.
	bool bin_write(ofstream & fout)const;

	//�������� ������� ��-�� ����������� �������.
	friend ostream & operator<<(ostream &, const Image &);

	//������� ������� ��������� �� ������. 
	friend bool image_equality(const Image & im1, const Image & im2, double min_equality);	
};



//����������� �������� ���������� ������ �� ������ ��������������� ���������� ���������.
template<size_t W, size_t H> Image::Image(const Borders & bs, array<array<char, W>, H> & ws, char bg, char obj) : data(vector<vector<bool>>())
{
	//cout << "Constructing... ";
	for (int i = bs.y_min, i2 = 0; i <= bs.y_max; ++i, ++i2)
	{
		//cout << "i=" << i << " ";
		data.push_back(vector<bool>());
		for (int j = bs.x_min; j <= bs.x_max; ++j)
		{
			if (j >= 0 && j < W && i >= 0 && i < H)//�������, ���������������� �� ������ �� ������� �������.
			{
				if (ws[i][j] == obj)
				{
					data[i2].push_back(1);
				}
				else
				{
					data[i2].push_back(0);
				}
			}
		}
	}

	width = data[0].size();//������ ����� ������� �������� ��. �������.
	height = data.size();

	aspect_rate = ((double)width / height);
}