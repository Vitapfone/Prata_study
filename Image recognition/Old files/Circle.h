#pragma once
struct Circle : public Figure//�����������.
{
	size_t radius = 0;//������ �����.

	//������������.
	Circle() = default;
	Circle(int x, int y, size_t r) : Figure(x, y), radius(r) {}

	~Circle() {}

	void print(Ar60_30 &ws);//�������������� ������� ���������.

	template<size_t W, size_t H> void print(array<array<char, W>, H> &ws);//������� ��������� ����� ��� ������ �������� ������������.
};

//������� ��������� ����� ��� ������ �������� ������������.
template<size_t W, size_t H> void Circle::print(array<array<char, W>, H> & ws)
{
	for (int y = y0 - radius; y <= y0 + radius; ++y)
	{
		for (int x = x0 - radius; x <= x0 + radius; ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)
			{
				if ((x - x0)*(x - x0) + (y - y0)*(y - y0) <= radius * radius)
				{
					ws[y][x] = '0';
				}
			}
		}
	}
}