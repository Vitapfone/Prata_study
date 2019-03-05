#include "pch.h"
#include "Focus of attention.h"
#include "Cluster.h"
#include "Inspector.h"

//������� ���������� ����� �������� � ��������� ����� ������� �������.
void Focus_of_attention::to_Weight_Center(const Inner_frame & ws)
{
	bool	foc_move_up		= false;	//����������, ������������, ��� ����� ��� ������������ �����.
	bool	foc_move_down	= false;	//����������, ������������, ��� ����� ��� ������������ ����.
	int		upCount			= 0;		//������� �������� ������� ���� ������.
	int		downCount		= 0;		//������� �������� ������� ���� ������.

	while ((foc_move_up == false) || (foc_move_down == false))//���� ����� �� �������� � ��� �������.
	{

		upCount = 0;//������� ������� ���� ������.
		for (int y = borders_.y_min_; y < loc_.y_; ++y)
		{
			for (int x = borders_.x_min_; x <= borders_.x_max_; ++x)
			{
				if (ws[y][x] == object_)
				{
					++upCount;
				}
			}
		}

		downCount = 0;//������� ����.
		for (int y = loc_.y_ + 1; y <= borders_.y_max_; ++y)
		{
			for (int x = borders_.x_min_; x <= borders_.x_max_; ++x)
			{
				if (ws[y][x] == object_)
				{
					++downCount;
				}
			}
		}
		if (upCount > downCount)//���� ���� �������� ������,
		{
			--loc_.y_;			//�� ����������� ����� �����
			foc_move_up = true;	//������ ����� �������� �����.
		}
		else if (upCount < downCount)//���� ������ --
		{
			++loc_.y_;				//����������� ����.
			foc_move_down = true;	//������ ����� �������� ����.
		}
		else//���� ���� � ���� �������� ���������,
		{
			break;//�� ����� ������ � ���� ���� ���������.
		}
	}
	//cout << "upCount: " << upCount << " downCount " << downCount << endl;

	bool	foc_move_left	= false;	//����������, ������������, ��� ����� ��� ������������ �����.
	bool	foc_move_right	= false;	//����������, ������������, ��� ����� ��� ������������ ������.
	int		leftCount		= 0;		//������� �������� ������� ����� ������.
	int		rightCount		= 0;		//������� �������� ������� ������ ������.

	while ((foc_move_left == false) || (foc_move_right == false))//��� ���������� ��������� ��� �������.
	{

		leftCount = 0;
		for (int x = borders_.x_min_; x < loc_.x_; ++x)
		{
			for (int y = borders_.y_min_; y <= borders_.y_max_; ++y)
			{
				if (ws[y][x] == object_)
				{
					++leftCount;
				}
			}
		}

		rightCount = 0;
		for (int x = loc_.x_ + 1; x <= borders_.x_max_; ++x)
		{
			for (int y = borders_.y_min_; y <= borders_.y_max_; ++y)
			{
				if (ws[y][x] == object_)
				{
					++rightCount;
				}
			}
		}
		if (leftCount > rightCount)
		{
			--loc_.x_;
			foc_move_left = true;
		}
		else if (leftCount < rightCount)
		{
			++loc_.x_;
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
	Cluster cl5(loc_.x_ - 2, loc_.y_ - 2);
	Cluster cl4(loc_.x_ - 7, loc_.y_ - 2);
	Cluster cl6(loc_.x_ + 3, loc_.y_ - 2);
	Cluster cl8(loc_.x_ - 2, loc_.y_ + 3);
	Cluster cl7(loc_.x_ - 7, loc_.y_ + 3);
	Cluster cl9(loc_.x_ + 3, loc_.y_ + 3);
	Cluster cl1(loc_.x_ - 7, loc_.y_ - 7);
	Cluster cl2(loc_.x_ - 2, loc_.y_ - 7);
	Cluster cl3(loc_.x_ + 3, loc_.y_ - 7);

	vector<Cluster> vcl{ cl1, cl2, cl3, cl4, cl5, cl6, cl7, cl8, cl9 };

	for (auto & e : vcl)//������ ������� ������������ ���-�� ������, �������� �� ����.
	{
		e.counter(ws, background_);
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
	Location center = { fcl.x_ + 3, fcl.y_ + 3 }; //�������� ����� ��������.

	//����������� �����. 
	relocate(center); 

	if (ws[loc_.y_][loc_.x_] == background_)
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
	Inspector ins(loc_.x_, loc_.y_, background_, object_);//������� ���������� ��� ������ �� �������.

	Borders object_area = ins.left_inspect(ws, 1);//������� ������ �� ������� �������, ������� � ������ ����. �������� ������ �������� � ���� ���������, ��� �������, � ����� ��������� ��������� 
														// ���������� ���� ������.

	//������� ��������������� �� ����������� ������.
	borders_ = object_area;

	//��������� ������ �������.
	Location center = { (borders_.x_max_ + borders_.x_min_) / 2, (borders_.y_max_ + borders_.y_min_) / 2 };
	//��������� ����� �������� � ����� �������, ���������� ��������
	relocate(center); 

	//����� �������� �������� �� �������� ������������������.
	mode_par_con();
}
