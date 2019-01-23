#include "pch.h"
#include "Image.h"
#include "My_names.h"

using namespace My_names;

//����������� �������� ���������� ������ �� ��������� �����.
Image::Image(ifstream & ifs) : data(vector<vector<bool>>())
{
	//��������� ������ � ������ ������.
	ifs.read((char*)&width, sizeof width);
	ifs.read((char*)&height, sizeof height);
	aspect_rate = (double) width / height;//���������� ����� �����, �.�. ��� ������������� �������(����� ��� ����� �����) ������������� ������� �����.

	bool* buf = new bool[width];//�������� �����.
	for (size_t i = 0; i < height; i++)
	{
		ifs.read((char*)&buf, width);//������ � ����� ���-�� ����, ������ ������ ( ������ bool == 1 ����).
		vector<bool> temp(buf, buf + width);//������� ��������� ������ �� ������.
		data.push_back(temp);
		delete[] buf;//������� �����.
	}

	//������ ���������.
	ifs.read((char*)&id_is_ps, sizeof id_is_ps);
	ifs.read((char*)&id_non_ps, sizeof id_non_ps);
}


//������� � ������� ����� � ������� ��� ���������� ����.
void Image::visualize()
{
	for (int i = 0; i < data.size(); ++i)
	{
		for (int j = 0; j < data[0].size(); ++j)
		{
			cout << ((data[i][j] == 1)?'0':' ');
		}
		cout << endl;
	}
}

//��������� �� ��������� �����.
bool Image::bin_read(ifstream & fin)
{
	//��������� ������ � ������ ������.
	
	if (!fin.read((char*)&width, sizeof width))
	{
		return false;
	}
	fin.read((char*)&height, sizeof height);
	aspect_rate = (double)width / height;//���������� ����� �����, �.�. ��� ������������� �������(����� ��� ����� �����) ������������� ������� �����.

	if (!data.empty())//���� ��. ������ �� ����, �� ������� ���. �� ������ ������.
	{
		data.clear();
	}

	shared_ptr<bool> buf;//����� ��������� �� ������� �����.
	vector<bool> temp(width);

	for (size_t i = 0; i < height; i++)
	{
		buf.reset(new bool[width]);//�������� �����.
		//cout << "Read into buf\n";
		fin.read((char*)buf.get(), width);//������ � ����� ���-�� ����, ������ ������ ( ������ bool == 1 ����).
		temp.assign(buf.get(), buf.get() + width);//������� ��������� ������ �� ������.
		data.push_back(temp);
	}

	//������ ���������.
	fin.read((char*)&id_is_ps, sizeof id_is_ps);
	fin.read((char*)&id_non_ps, sizeof id_non_ps);

	if (fin)
		return true;
	else
		return false;
}

//�������� � �������� ����.
bool Image::bin_write(ofstream & fout) const
{
	fout.write((char*)&width, sizeof width);//������ ������.
	fout.write((char*)&height, sizeof height);//������ ������.

	bool elem;//��������� ��������� ��� ��-��.
	for (size_t i = 0; i < height; i++)//������������ ������.
	{
		for (size_t j = 0; j < width; j++)
		{
			elem = data[i][j];
			fout.write((char*)&elem, sizeof elem);
		}
	}
	//������ ���� ������.
	fout.write((char*)&id_is_ps, sizeof id_is_ps);
	fout.write((char*)&id_non_ps, sizeof id_non_ps);

	if (fout)//���� ��� �������,
	{
		return true;//�� ���������� true.
	}
	else
	{
		return false;
	}
}


//�������� ������� ��-�� ����������� �������. ������ ������������ ��� ������ � ����.
ostream & operator<<(ostream & os, const Image & im)
{
	for (int i = 0; i < im.data.size(); ++i)
	{
		for (int j = 0; j < im.data[0].size(); ++j)
		{
			os << im.data[i][j];
		}
		os << endl;
	}
	os << '\n';
	os << im.id_is_ps << ' ' << im.id_non_ps << endl;

	return os;
}


//������� ������� ��������� �� ������.
bool image_equality(const Image & im1, const Image & im2, double min_equality)
{
	
	//cout << "Start comparison...";
	if (im1.get_aspect() >= im2.get_aspect()*0.9 && im1.get_aspect() <= im2.get_aspect()*1.1)//���� ��������� ������ ���� ������� ����������� � �������� +-10%, �� �� ����� 
																							// ���������� ���������.
	{
		Image wider = (im1.get_widht() >= im2.get_widht()) ? im1 : im2;//��������� ����� ��� �������� ����� ������� ������.
		//cout << "Wider image:" << endl;
		//wider.visualize();

		Image narrow = (im1.get_widht() < im2.get_widht()) ? im1 : im2;//��������� ����� ��� ����� ������.
		//cout << "Narrow image:" << endl;
		//narrow.visualize();

		Image higher = (im1.get_height() >= im2.get_height()) ? im1 : im2;//��������� ����� ��� �������� ����� ������� ������.
		//cout << "Higher image:" << endl;
		//higher.visualize();

		Image low = (im1.get_height() < im2.get_height()) ? im1 : im2;//��������� ����� ��� ������ ������.
		//cout << "Lower image:" << endl;
		//low.visualize();

		size_t count = 0;//������� ����������.
		//��� ���������� ����� ������� �������� ��������� ���� ������� ������ �������� � �������������� �������������� ��������� ��������� (��������).
		for (int i = 0; i < higher.get_height(); ++i)
		{
			for (int j = 0; j < wider.get_widht(); ++j)
			{
				if (im1.data[round(i*im1.get_height() / higher.get_height())][round(j*im1.get_widht() / wider.get_widht())] ==
																			im2.data[round(i*im2.get_height() / higher.get_height())][round(j*im2.get_widht() / wider.get_widht())])
				{
					++count;
				}
			}
		}

		size_t max_square = higher.get_height()*wider.get_widht();//����������� ��������� ���-�� ��������� � ������.
		double equality = count / static_cast<double>(max_square);//���� ���������� �� ���� ��������.

		cout << count << " " << max_square << " " << equality << endl;

		if (equality >= min_equality)//���������, ������������ ����������� �������� ������� ��� ������� �� �� ������������.
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else //���� ��������� ������ ������ �����������,
	{
		cout << "Huge aspect rate difference!" << endl;
		return false;//�� �������, ��� ��� �� �����.
	}
		
}