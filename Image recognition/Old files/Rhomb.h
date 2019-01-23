#pragma once
struct Rhomb : public Figure
{
	size_t diagonal = 0;

	//������������
	Rhomb() = default;
	Rhomb(size_t x, size_t y, size_t diag) : Figure(x, y), diagonal(diag) {}

	~Rhomb() {}

	void print(Ar60_30 &ws); //��������������� ����������� ������� �� �������� ������.

	template<size_t W, size_t H> void print(array<array<char, W>, H> & ws);//������ ������� ��� ��������� � ������� ������������ ������ �������.

};

template<size_t W, size_t H> void Rhomb::print(array<array<char, W>, H> & ws)
{
	for (size_t y = (y0 - diagonal / 2); y <= y0; ++y)
	{
		for (size_t x = (x0 - diagonal / 2); x <= (x0 + diagonal / 2); ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//�������, �������������� �� ������ �� ������� �������.
			{
				if (x >= x0 - (y - (y0 - diagonal / 2)) && x <= x0 + (y - (y0 - diagonal / 2)))
				{
					ws[y][x] = '0';
				}
			}
		}
	}

	for (size_t y = y0; y <= y0 + diagonal / 2; ++y)
	{
		for (size_t x = x0 - diagonal / 2; x <= x0 + diagonal / 2; ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//�������, �������������� �� ������ �� ������� �������.
			{
				if (x >= x0 - (y0 + diagonal / 2 - y) && x <= x0 + (y0 + +diagonal / 2 - y))
				{
					ws[y][x] = '0';
				}
			}
		}
	}
}
