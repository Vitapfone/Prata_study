#pragma once
#include "Inspector.h"

using namespace My_names;

enum Attention_mode{Distributed, Partially_concentrated};

class Focus_of_attention
{
	//���������� ������ ��������.
	Location loc{ 0, 0 };

	char background =' ';//���. �� ��������� ������, ��� �������� ��������� ���.
	char object = '0';
	Attention_mode mode = Distributed;//����� ��������. �� ��������� ��������������.

	Borders borders;//��������� ��� �������� ���������� � �������� ������� ��������.

public:
	//�����������
	template<size_t W, size_t H> Focus_of_attention(int x, int y, array<array<char, W>, H> & ws) : loc{ x, y }, background(ws[y][x]), borders{ 0, W - 1, 0, H - 1 } {}


	//�������

	//������ ���
	char get_background() const { return background; }

	//������ ������
	char get_object() const { return object; }

	//������ X.
	int get_x() const { return loc.x; }

	//������ Y.
	int get_y() const { return loc.y; }

	//������ �����
	int get_mode() const { return mode; }

	//������ ������� ������� ��������.
	Borders get_borders()const { return borders; }

	//�������

	//���������� ����� �������� ���������������� ��������.
	void mode_par_con() { mode = Partially_concentrated; }

	//���������� ������.
	template<size_t W, size_t H> 
	void assign_object(array<array<char, W>, H> &ws) { object = ws[loc.y][loc.x]; }



	//����������  ���������.
	template<size_t W, size_t H> 
	void mark(array<array<char, W>, H> & ws) { ws[loc.y][loc.x] = '+'; }

	//�����������.
	void relocate(const Location & new_loc) { loc = new_loc; }

	//����������� � ����� ������� �������.
	template<size_t W, size_t H>  
	void to_Weight_Center(array<array<char, W>, H> & ws);

	//������ ���������� 9-�� ������������ ��������� ������ ������.
	template<size_t W, size_t H> 
	Cluster clusterize(array<array<char, W>, H> & ws);

	//�������� ����������� ����� ������ �������.
	template<size_t W, size_t H> 
	bool go_inside(array<array<char, W>, H> & ws);

	//���������� ������� �������, � ������� ��������� ��������� ������. �������������� �� ���������� ������� ������� ������������ ��������.
	//���������� ����� ��������� ������������.
	template<size_t W, size_t H>
	void part_concentrate_to_object(array<array<char, W>, H> & ws);

};

//������� ���������� ����� �������� � ��������� ����� ������� �������.
template<size_t W, size_t H>  
void Focus_of_attention::to_Weight_Center(array<array<char, W>, H> & ws)
{
	bool foc_move_up = false;//����������, ������������, ��� ����� ��� ������������ �����.
	bool foc_move_down = false;//����������, ������������, ��� ����� ��� ������������ ����.
	int upCount = 0;//������� �������� ������� ���� ������.
	int downCount = 0;//������� �������� ������� ���� ������.

	while ((foc_move_up == false) || (foc_move_down == false))//���� ����� �� �������� � ��� �������.
	{

		upCount = 0;//������� ������� ���� ������.
		for (int y = borders.y_min; y < loc.y; ++y)
		{
			for (int x = borders.x_min; x <= borders.x_max; ++x)
			{
				if (ws[y][x] == object)
				{
					++upCount;
				}
			}
		}

		downCount = 0;//������� ����.
		for (int y = loc.y + 1; y <= borders.y_max; ++y)
		{
			for (int x = borders.x_min; x <= borders.x_max; ++x)
			{
				if (ws[y][x] == object)
				{
					++downCount;
				}
			}
		}
		if (upCount > downCount)//���� ���� �������� ������,
		{
			--loc.y;//�� ����������� ����� �����
			foc_move_up = true;//������ ����� �������� �����.
		}
		else if (upCount < downCount)//���� ������ --
		{
				++loc.y;//����������� ����.
				foc_move_down = true;//������ ����� �������� ����.
		}
		else//���� ���� � ���� �������� ���������,
		{
				break;//�� ����� ������ � ���� ���� ���������.
		}
	}
	cout << "upCount: " << upCount << " downCount " << downCount << endl;

	bool foc_move_left = false;//����������, ������������, ��� ����� ��� ������������ �����.
	bool foc_move_right = false;//����������, ������������, ��� ����� ��� ������������ ������.
	int leftCount = 0;//������� �������� ������� ����� ������.
	int rightCount = 0;//������� �������� ������� ������ ������.

	while ((foc_move_left == false) || (foc_move_right == false))//��� ���������� ��������� ��� �������.
	{

		leftCount = 0;
		for (int x = borders.x_min; x < loc.x; ++x)
		{
			for (int y = borders.y_min; y <= borders.y_max; ++y)
			{
				if (ws[y][x] == object)
				{
					++leftCount;
				}
			}
		}

		rightCount = 0;
		for (int x = loc.x + 1; x <= borders.x_max; ++x)
		{
			for (int y = borders.y_min; y <= borders.y_max; ++y)
			{
				if (ws[y][x] == object)
				{
					++rightCount;
				}
			}
		}
		if (leftCount > rightCount)
		{
			--loc.x;
			foc_move_left = true;
		}
		else if (leftCount < rightCount)
		{
			++loc.x;
			foc_move_right = true;
		}
		else
		{
			break;
		}
	}
	cout << "leftCount: " << leftCount << " rightCount " << rightCount << endl;
}

//������ ���������� 9-�� ������������ ��������� ������ ������.
template<size_t W, size_t H> 
Cluster Focus_of_attention::clusterize(array<array<char, W>, H> & ws)
{
	Cluster cl5(loc.x - 2, loc.y - 2);
	Cluster cl4(loc.x - 7, loc.y - 2);
	Cluster cl6(loc.x + 3, loc.y - 2);
	Cluster cl8(loc.x - 2, loc.y + 3);
	Cluster cl7(loc.x - 7, loc.y + 3);
	Cluster cl9(loc.x + 3, loc.y + 3);
	Cluster cl1(loc.x - 7, loc.y - 7);
	Cluster cl2(loc.x - 2, loc.y - 7);
	Cluster cl3(loc.x + 3, loc.y - 7);

	vector<Cluster> vcl{ cl1, cl2, cl3, cl4, cl5, cl6, cl7, cl8, cl9 };

	for (auto & e : vcl)//������ ������� ������������ ���-�� ������, �������� �� ����.
	{
		e.counter(ws, background);
	}
	//���� �������� �����������.
	sort(vcl.begin(), vcl.end(), [](Cluster & c1, Cluster & c2) {return c1.count > c2.count; });

	//���������� ���.
	return vcl[0];
}

//�������� ����������� ����� ������ �������.
template<size_t W, size_t H>
bool Focus_of_attention::go_inside(array<array<char, W>, H>& ws)
{
	Cluster fcl = clusterize(ws);//�������� �������� ����������� ������������ �������.
	Location center = { fcl.xC + 3, fcl.yC + 3 }; //�������� ����� ��������.
	relocate(center); //����������� �����. 

	if (ws[loc.y][loc.x] == background)
	{
		return false;
	}
	else
	{
		return true;
	}
}


//���������� ������� �������, � ������� ��������� ��������� ������. �������������� �� ���������� ������� ������� ������������ ��������.
//���������� ����� ��������� ������������.
template<size_t W, size_t H>
void Focus_of_attention::part_concentrate_to_object(array<array<char, W>, H>& ws)
{
	Inspector ins(loc.x, loc.y, background, object);//������� ���������� ��� ������ �� �������.

	Borders object_area = ins.left_inspect(ws, 1);//������� ������ �� ������� �������, ������� � ������ ����. �������� ������ �������� � ���� ���������, ��� �������, � ����� ��������� ��������� 
														// ���������� ���� ������.
	cout << "\nAfter inspecting..." << endl;

	//������� ��������������� �� ����������� ������.
	borders = object_area;

	//��������� ������ �������.
	Location center = { (borders.x_max + borders.x_min) / 2, (borders.y_max + borders.y_min) / 2 };
	relocate(center); //��������� ����� �������� � ����� �������, ���������� ��������

	//����� �������� �������� �� �������� ������������������.
	mode = Partially_concentrated;
}
