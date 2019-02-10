#include "pch.h"
#include "My_names.h"
#include "Simple structures.h"
#include "Warning.h"

#include "Cluster.h"

void Cluster::counter(const Inner_frame & ws, char background)
{
	for (int y = loc.y; y != (loc.y + s); ++y)//���������� ��� ��-�� �������� ������������ � �������� ����������� ��������.
	{
		for (int x = loc.x; x != (loc.x + s); ++x)
		{
			if (x >= 0 && x < ws[0].size() && y >= 0 && y < ws.size())//�������, ���������������� �� ������ �� ������� �������.
			{
				if (ws[y][x] != background)//���� ��-� �� ����� ����,
				{
					++count;//�� ����������� ������� ����� ��-���.
				}
			}
		}
	}
}
