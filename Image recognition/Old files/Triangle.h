#pragma once
using std::cout; using std::endl;
struct Triangle : Figure //���������, �������������� �������������� ������������� �����������.
{
	size_t cathetus = 0;// ����� ������.
	size_t point_A_x = 0, point_A_y = 0;//���������� ������� � ������ �����.
	size_t point_B_x = 0, point_B_y = 0; //���������� ������ ������� � ������ �����. ���������� ������ ����������� �� Figure. 

	//������������
	Triangle() = default;
	Triangle(size_t x, size_t y, size_t cat) : Figure(x, y), cathetus(cat), point_A_x(x), point_A_y(y + cathetus), point_B_x(x + cathetus), point_B_y(y + cathetus)
	{
		//cout << point_A_x << " " << point_A_y << " " << point_B_x << " " << point_B_y << endl;
	}

	~Triangle() {}

	void print(Ar60_30 &ws); //��������������� ����������� ������� �� �������� ������.

	template<size_t W, size_t H> void print(array<array<char, W>, H> & ws);//��������� ������������ ��� �������� ������������ ������ �������.

};

//��������� ������������ ��� �������� ������������ ������ �������.
template<size_t W, size_t H> void Triangle::print(array<array<char, W>, H> & ws)
{
	for (size_t y = y0; y <= point_A_y; ++y)
	{
		for (size_t x = x0; x <= point_B_x; ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//�������, �������������� �� ������ �� ������� �������.
			{
				if (x - x0 < y - y0)
				{
					ws[y][x] = '0';
				}
			}
		}
	}
}