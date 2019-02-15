#include "pch.h"
#include "Focus of attention.h"
#include "Cluster.h"
#include "Inspector.h"

//������� ���������� ����� �������� � ��������� ����� ������� �������.
void Focus_of_attention::to_Weight_Center(const Inner_frame & ws)
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
	//cout << "upCount: " << upCount << " downCount " << downCount << endl;

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
	//cout << "leftCount: " << leftCount << " rightCount " << rightCount << endl;
}

//������ ���������� 9-�� ������������ ��������� ������ ������.
const Location Focus_of_attention::clusterize(const Inner_frame & ws)
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
	sort(vcl.begin(), vcl.end(), [](Cluster & c1, Cluster & c2) {return c1.get_count() > c2.get_count(); });

	//���������� ���.
	return vcl[0].where();
}

//�������� ����������� ����� ������ �������.
bool Focus_of_attention::go_inside(const Inner_frame& ws)
{
	Location fcl = clusterize(ws);//�������� �������� ����������� ������������ �������.
	Location center = { fcl.x + 3, fcl.y + 3 }; //�������� ����� ��������.
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
void Focus_of_attention::part_concentrate_to_object(const Inner_frame & ws)
{
	Inspector ins(loc.x, loc.y, background, object);//������� ���������� ��� ������ �� �������.

	Borders object_area = ins.left_inspect(ws, 1);//������� ������ �� ������� �������, ������� � ������ ����. �������� ������ �������� � ���� ���������, ��� �������, � ����� ��������� ��������� 
														// ���������� ���� ������.
	//cout << "\nAfter inspecting..." << endl;

	//������� ��������������� �� ����������� ������.
	borders = object_area;

	//��������� ������ �������.
	Location center = { (borders.x_max + borders.x_min) / 2, (borders.y_max + borders.y_min) / 2 };
	relocate(center); //��������� ����� �������� � ����� �������, ���������� ��������

	//����� �������� �������� �� �������� ������������������.
	mode_par_con();
}
