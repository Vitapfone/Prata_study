#include "pch.h"
#include "Square.h"
using std::cout; using std::endl;
using std::array;

//������� ������ �������� ������� ������� ������.
void Square::make_border()
{
	for (int i = 0; i < vision[1].size(); ++i)
	{
		vision[0][i] = '=';
		vision[vision.size() - 1][i] = '=';
	}

	for (int j = 0; j < vision.size(); ++j)
	{
		vision[j][0] = '!';
		vision[j][vision[1].size() - 1] = '!';
	}
}

//������� ������� � ������� ������ � ���������� ����������� ������� ������� �������.
bool Square::see_border()
{
	int x = vision[1].size() / 2;
	int y = vision.size() - 2;
	auto background = vision[y][x];

	for (int i = 0; i <= a; ++i)
	{
		if (vision[y - i][x] != background)
		{
			if (vision[y - i][x + 1]!=background && vision[y - i][x - 1]!=background)
			{
				if (vision[y - i][x + 2] != background && vision[y - i][x - 2] != background)
				{
					cout << "See border!! ";
					return true;
				}
			}

		}
	}
	return false;
}

//������� ������ � ������� ������� ������.
void Square::print_vis()
{
	make_border();
	for (auto &e : vision)
	{
		for (auto &e2 : e)
		{
			cout << e2;
		}
		cout << endl;
	}
}

//������������, ����� � ������ �� ���� ���������� ����.
enum moves
{
	RIGHT = 1, LEFT, UP, DOWN
};

//������� ���������� ������. ����������� �������� ��-��� �������� ������������ ��-��� ������� ������.
void Square::see_you(Ar60_30 & ar, int curr)
{
	cout << "see you... " << endl;
	
	switch (curr)//����������� ������� ��������.
	{
	default:
		break;

	case UP://� ������ ������ ���������� ������� ���������� �������������� ���������� ��������� � �������������.
		for (int i=0; i<2*a; ++i)//���� ������� ������.
		{
			for (int j=0; j<3*a; ++j)//�������� ����.
			{
				if ((x0-a+j) >= 0 && (x0-a+j) < 60 && (Square::y0 - 2 * a + i) >= 0 && (Square::y0 - 2 * a + i) < 30)//�������� ������������ �� ��������� � �������������� ��-��� �������.
				{
					vision[i][j] = ar[Square::y0 - 2 * a + i][x0 - a + j];
				}
				else
				{
					vision[i][j] = '=';//��-�� ������� ������, ��������������� �������������� ��-���, ����������� ������ �����.
				}
			}
		}
		break;
	case DOWN:
		for (int i = 0; i < 2 * a; ++i)
		{
			for (int j = 0; j < 3 * a; ++j)
			{
				if( (x0 + 2 * a - j) >= 0 && (x0 + 2 * a - j) < 60 && (Square::y0 + 3 * a - i) >= 0 && (Square::y0 + 3 * a - i) < 30)
				{
					vision[i][j] = ar[Square::y0+3*a-i][x0+2*a-j];
				}
				else
				{
					vision[i][j] = '=';
				}
			}
		}
		break;
	case LEFT:
		for (int i = 0; i < 2 * a; ++i)
		{
			for (int j = 0; j < 3 * a; ++j)
			{
				if ((x0 - 2 * a + i) >= 0 && (x0 - 2 * a + i) < 60 && (Square::y0 + 2 * a - j) >= 0 && (Square::y0 + 2 * a - j) < 30)
				{
					vision[i][j] = ar[Square::y0 + 2 * a - j][x0 - 2 * a + i];
				}
				else
				{
					vision[i][j] = '=';
				}
			}
		}
		break;
	case RIGHT:
		for (int i = 0; i < 2 * a; ++i)
		{
			for (int j = 0; j < 3 * a; ++j)
			{
				if ((x0 + 3 * a - i) >= 0 && (x0 + 3 * a - i) < 60 && (Square::y0 - a + j) >= 0 && (Square::y0 - a + j) < 30)
				{
					vision[i][j] = ar[Square::y0 - a + j][x0 + 3 * a - i];
				}
				else
				{
					vision[i][j] = '=';
				}
			}
		}
		break;
	}
}

//����������� �������������� ���������� � ��������� ������� ��������� ���������(��������� �� ���������).
Square::Square(int x, int y, unsigned a1) : x0(x), y0(y), a(a1)
{
	vector<char> v1(3 * a, ' ');

	vision.assign (2 * a, v1);
}

//������� ��������� ��������.
void Square::printSquare(Ar60_30 & ar)
{

	for (int y = y0; y != (y0 + a); ++y) //������� ������������ �������, ��������� �� ������� ���������� �����.
	{
		for (int x = x0; x != (x0 + a); ++x)//���������� ���� �������� ������� ����
		{
			if (x >= 0 && x < 60 && y >= 0 && y < 30)//�������, ���������������� �� ������ �� ������� �������.
			{
				ar[y][x] = '0';
			}
		}
	}
}



//������� �������������������� ��������, ����������� � �������� ��������� ������ ����� �����.
int Square::program_move(vector<int> &pr)
{
	static auto act = pr.begin();//����������� �������� �� ������ ������� ���������.
	 
	cout << "Before switch pr.size= "<<pr.size()<<" ";
	
		switch (*act)// �������� ����������� �������. � ����������� �� �����, ����� ����������� ���. ��������.
		{
		default:// ���� ����� ������������, �� �������� �������� � ��������� �������.
			cout << "default ";
			break;
		case RIGHT:
			moveRight();
			cout << "moveRight ";
			break;
		case LEFT:
			moveLeft();
			cout << "moveLeft ";
			break;
		case UP:
			moveUp();
			cout << "moveUp ";
			break;
		case DOWN:
			moveDown();
			cout << "moveDown ";
			break;
		}

	auto curr_move = *act;//��������� ������� �������� � ���������

	act = correct_replace(act, pr); //� ����� ������ ���������� �������� �� ��������� �������, ������� ���������� �� ����.
	
	if (act == pr.end())
	{
		act = pr.begin();
		cout << "act=beg ";
	}

	return curr_move;
}



//vector<int>::iterator Square::correct_plus(vector<int>::iterator act, vector<int>& pr)
//{
//	//����� ������ ����������� ������������� ���������. 
//	if (x0 >= 50)//���� ������� ������� ������ � ������� ����,
//	{
//		act = (pr.insert(act + 1, 2)) - 1; // �� ��������� ��������� ����� �������� �����.
//	}
//
//	if (Square::y0 >= 25) //���� ������� ������ � ����,
//	{
//		act = (pr.insert(act + 1, 3)) - 1; // �� ��������� ��������� ����� �������� �����.
//	}
//
//	if (Square::y0 <= 5) //���� ������� ������ � �����,
//	{
//		act = (pr.insert(act + 1, 4)) - 1;// �� --- �������� ����.
//	}
//
//	if (x0 <= 10)// ���� ������ � ������ ����, 
//	{
//		act = (pr.insert(act + 1, 1)) - 1;// �� -- ������.
//	}
//	
//	return act;
//}
//� ����� ������������� ������������� �������� � ���������� ���������. ������� �������� ��� ����� �����������, ���� ������� ������� ���������.
	//�������� ����� � ��������� �� �����.


//vector<int>::iterator Square::correct_minus(vector<int>::iterator act, vector<int>& pr)
//{
//	bool corr = false;
//	if (x0 >= 50)//���� ������� ������� ������ � ������� ����,
//	{
//		try
//		{
//			cout << "Correction x0>=50 ";
//			if (pr.size() == 0)
//				throw "The program is empty!";
//
//			act = pr.erase(act);// �� ������ ��������� ��-� ������� � ������ � ����� ���������.
//			cout << "erasing...";
//			corr = true;
//		}
//		catch (const char* msg)
//		{
//			std::cerr << msg << endl;
//		}
//		
//	}
//
//	if (x0 <= 10)// ���� ������ � ������ ����, 
//	{
//
//		cout << "Correction x0<=10 ";
//		act = pr.erase(act);// �� ������ ��������� ��-� ������� � ������ � ����� ���������.
//		cout << "erasing...";
//		corr = true;
//	}
//
//	if (Square::y0 >= 25) //���� ������� ������ � ����,
//	{
//		cout << "Correction y0>25 ";
//		act = pr.erase(act);// �� ������ ��������� ��-� ������� � ������ � ����� ���������.
//		cout << "erasing...";
//		corr = true;
//	}
//
//	if (Square::y0 <= 5) //���� ������� ������ � �����,
//	{
//		cout << "Correction y0<=5 ";
//	/*	try
//		{
//			if (pr.size() == 0)
//				throw "The program is empty!";
//		}*/
//		try
//		{
//			cout << "erasing...";
//			if (pr.size() == 0)
//				throw "The program is empty!";
//			act = pr.erase(act);// �� ������ ��������� ��-� ������� � ������ � ����� ���������.
//		}
//		catch (const char* msg)
//		{
//			std::cerr << msg << endl;
//		}
//
//		//act = pr.erase(act);// �� ������ ��������� ��-� ������� � ������ � ����� ���������.
//		
//		corr = true;
//	}
//
//	if(corr==false)
//	{
//		++act;
//	}
//
//	return act;
//	
//}
//� ����� ������������� ��������� �������� � ����������� ��������� � ������, ����� �������� �������� �������� �� ��-� ������� �������. ������������� ��������� 
	// �� ������������, ���� �� �������� ������� ����������� ������ ��� ����� �������.

vector<int>::iterator Square::correct_replace(vector<int>::iterator act, vector<int>& pr)
{
	

	bool corr = false;
	if ( x0>+50 )//���� ������� ������� ������ � ������� ����,
	{
		act = pr.erase(act);// �� ������ ��������� ��-� ������� � ������ � ����� ���������.
		cout << "Erased... ";
		if (act == pr.end())
		{
			cout << "End! ";
			act = pr.insert(act, 2);
		}
		else
		{
			act = pr.insert(act + 1, 2); // �� ��������� ��������� ����� �������� �����. 
		}
		cout << "Inserted... ";

		corr = true;
	}

	if (y0>=25) //���� ������� ������ � ����,
	{
		cout << "Correction y0>=25 ";
		act = pr.erase(act);
		cout << "Erased... ";
		if (act == pr.end())
		{
			cout << "End! ";
			act = pr.insert(act, 3);
		}
		else
		{
			act = pr.insert(act + 1, 3); // �� ��������� ��������� ����� �������� �����.
		}
		
		cout << "Inserted... ";
		corr = true;
	}

	if (y0<=5) //���� ������� ������ � �����,
	{
		cout << "Correction. y0<=5 ";
		act = pr.erase(act);
		cout << "Erased... ";
		if (act == pr.end())
		{
			cout << "End! ";
			act = pr.insert(act, 4);
		}
		else
		{
			act = pr.insert(act + 1, 4);// �� --- �������� ����.
		}
		cout << "Inserted... " << (act == pr.end()) << " ";
		corr = true;
	}

	if (x0<=10)// ���� ������ � ������ ����, 
	{
		cout << "Correction. x0<=10 ";
		act = pr.erase(act);
		cout << "Erased... ";
		if (act == pr.end())
		{
			cout << "End! ";
			act = pr.insert(act, 1);
		}
		else
		{
			act = pr.insert(act + 1, 1);// �� -- ������.
		}
		cout << "Inserted... ";

		corr = true;
	}

	if (corr == false)
	{
		++act;
		cout << "++act ";
	}

	return act;
}
// ��� ��������� ������� ��������� ��������� ���� ������. ��� ��� ������, ��� ��������� ��������. ��� ������ ������� ��������� ���������. ������� ��� �� ���������� �� ������
// � ����� ������������ ���� � ���������������� ����.

