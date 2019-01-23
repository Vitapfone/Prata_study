#pragma once
#include "Warning.h"


using namespace My_names;

struct Cluster
{
	int xC = 0, yC = 0;//���������� ������ �������� ���� ��������.
	int s = 5; //����� ������� ����������� ��������.
	int count = 0; //���������� �����, ���������� ��������� �� ����.

	//������������

	//������ �����. Count �������� ������ �� ��������� �����.
	Cluster(int x = 0, int y = 0, int s1 = 5) :xC(x), yC(y), s(s1) {}


	//���������� ������ ��������.
	int size() { return s * s; }

	//������� ������������ ���������� ����� � ��������, ���������� �������� �� ���� ��������.
	template<size_t W, size_t H>  void counter(array<array<char, W>, H> &ws, char background);

	//������� ������� �������� ������.
	void print() const { cout << xC << ", " << yC << ", " << count << endl; }

	//������ ����� ���������� � �������� �������.
	void assign(int x, int y) { xC = x; yC = y; count = 0; }
};

//������� ������������ ���������� ����� � ��������, ���������� �������� �� ���� ��������.
template<size_t W, size_t H>
void Cluster::counter(array<array<char, W>, H> &ws, char background)
{
	//cout << "Counting... " << endl;
	for (int y = yC; y != (yC + s); ++y)//���������� ��� ��-�� �������� ������������ � �������� ����������� ��������.
	{
		for (int x = xC; x != (xC + s); ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//�������, ���������������� �� ������ �� ������� �������.
			{
				if (ws[y][x] != background)//���� ��-� �� ����� ����,
				{
					++count;//�� ����������� ������� ����� ��-���.
				}
			}
		}
	}
}


//���������� ������� ���������� ���������. ������ ���������� ��������, � ������� ������ ����� �����, �������� �� ����. Cluster.h.
template<size_t W, size_t H>
Warning most_filled_cluster(array<array<char, W>, H> &ws, char background)
{
	//������� �������� ��� ������
	vector<Cluster> vc;

	for (int i = 0; i < H; i += 10)
	{
		for (int j = 0; j < W; j += 10)
		{
			vc.push_back(Cluster(j, i, 10));
		}
	}

	for (auto & e : vc)//������ ������� ������������ ���-�� ������, �������� �� ����.
	{
		e.counter(ws, background);
	}
	cout << "After cluster counting" << endl;

	//����� �������� ����������� �������.
	sort(vc.begin(), vc.end(), [](Cluster & c1, Cluster & c2) {return c1.count > c2.count; });

	//��������� ���������� �������� ��������.
	int x = vc[0].xC + vc[0].s / 2;
	int y = vc[0].yC + vc[0].s / 2;

	return Warning("Unidentified contrast object!", { x, y }, 10);
}