#pragma once
using std::array;
using Ar60_30 = array<array<char, 60>, 30>;

struct Figure
{
	size_t x0 = 0, y0 = 0;//����������.

	//������������.
	Figure() = default;
	Figure(size_t x, size_t y) :x0(x), y0(y) {}
	//����������� ����������.
	virtual ~Figure() = default;

	virtual void print(Ar60_30 &ws) = 0; //������ ����������� ������� ��������� ������. ������ ���� ����� �����������.

	//������ ��������

	void moveRight() { ++x0; }//����������� ������.
	void moveLeft() { --x0; }//����������� �����.
	void moveUp() { --y0; }//����������� ����.
	void moveDown() { ++y0; }//����������� ����.

};