#pragma once
// ����� ����� ���������� ����� �������� ��� ����������� � ���������� ��������.
using std::vector;
using std::array;

using Ar60_30 = array<array<char, 60>, 30>;

struct Square
{
	int x0=0, y0=0;//���������� ������ �������� ���� ��������.
	unsigned a = 0;//����� �������.

	vector<vector<char>> vision;//������� "������" ��������.
private:
	//������� ������ �������� ������� ������� ������.
	void make_border();

	//������� ������� � ������� ������ � ���������� ����������� ������� ������� �������.
	bool see_border();

public:
	//������� ������ � ������� ������� ������.
	void print_vis();


	//������� ���������� ������. ����������� �������� ��-��� �������� ������������ ��-��� ������� ������.
	void see_you(Ar60_30 &, int);

	Square(int x = 0, int y = 0, unsigned a1 = 0); //�����������.


	//������ ��������

	void moveRight() { ++x0; }//����������� ������.
	void moveLeft() { --x0; }//����������� �����.
	void moveUp() { --y0; }//����������� ����.
	void moveDown() { ++y0; }//����������� ����.

	int program_move(vector<int> &);//������� �������������������� ��������, ����������� � �������� ��������� ������ ����� �����. ������������ ������� �������� � ���������.


	vector<int>::iterator correct_replace(vector<int>::iterator act, vector<int> &pr); //������� ��������� �������.

	//vector<int>::iterator correct_plus(vector<int>::iterator act, vector<int> &pr);// ������� ��������� ��������� �������������� ����, �.�. ����������� ��-�� � ������.
	//vector<int>::iterator correct_minus(vector<int>::iterator act, vector<int> &pr); //������� ������������� ���������, ��������� ��-�� �� ���������.

	
	void printSquare(Ar60_30 &ar);//������� ��������� ��������.
};