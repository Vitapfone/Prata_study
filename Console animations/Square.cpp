#include "pch.h"
#include "Square.h"
using std::cout; using std::endl;
using std::array;

//Функция делает видимыми границы области зрения.
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

//Функция смотрит в область зрения и определяет приближение границы рабочей области.
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

//Функция вывода в консоль области зрения.
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

//Перечисление, чтобы в свичах не было магических цифр.
enum moves
{
	RIGHT = 1, LEFT, UP, DOWN
};

//Функция реализации зрения. Присваивает значения эл-тов рабочего пространства эл-там области зрения.
void Square::see_you(Ar60_30 & ar, int curr)
{
	cout << "see you... " << endl;
	
	switch (curr)//Проверяется текущее движение.
	{
	default:
		break;

	case UP://В каждом случае проводится сложное непонятное преобразование абсолютных координат в относительные.
		for (int i=0; i<2*a; ++i)//Ряды области зрения.
		{
			for (int j=0; j<3*a; ++j)//Элементы ряда.
			{
				if ((x0-a+j) >= 0 && (x0-a+j) < 60 && (Square::y0 - 2 * a + i) >= 0 && (Square::y0 - 2 * a + i) < 30)//Проверки предохраняют от обращения к несуществующим эл-там массива.
				{
					vision[i][j] = ar[Square::y0 - 2 * a + i][x0 - a + j];
				}
				else
				{
					vision[i][j] = '=';//Эл-ты области зрения, соответствующие несуществующим эл-там, заполняются знаком равно.
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

//Конструктор инициализирует переменные и заполняет область видимости пробелами(состояние по умолчанию).
Square::Square(int x, int y, unsigned a1) : x0(x), y0(y), a(a1)
{
	vector<char> v1(3 * a, ' ');

	vision.assign (2 * a, v1);
}

//Функция отрисовки квадрата.
void Square::printSquare(Ar60_30 & ar)
{

	for (int y = y0; y != (y0 + a); ++y) //Функция отрисовывает квадрат, перебирая по очереди содержимое рядов.
	{
		for (int x = x0; x != (x0 + a); ++x)//Внутренний цикл печатает символы ряда
		{
			if (x >= 0 && x < 60 && y >= 0 && y < 30)//Условие, предостерегающее от выхода за границы массива.
			{
				ar[y][x] = '0';
			}
		}
	}
}



//Функция запрограммированного движения, принимающая в качестве программы вектор целых чисел.
int Square::program_move(vector<int> &pr)
{
	static auto act = pr.begin();//Статический итератор на начало вектора программы.
	 
	cout << "Before switch pr.size= "<<pr.size()<<" ";
	
		switch (*act)// Проверка управляющей команды. В зависимости от числа, будет выполняться опр. действие.
		{
		default:// Если число неправильное, то итератор перейдет к следующей команде.
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

	auto curr_move = *act;//Сохраняем текущее движение в программе

	act = correct_replace(act, pr); //В любом случае возвращает итератор на следующий элемент, поэтому инкремента не надо.
	
	if (act == pr.end())
	{
		act = pr.begin();
		cout << "act=beg ";
	}

	return curr_move;
}



//vector<int>::iterator Square::correct_plus(vector<int>::iterator act, vector<int>& pr)
//{
//	//Здесь должна происходить корректировка программы. 
//	if (x0 >= 50)//Если квадрат слишком близко к правому краю,
//	{
//		act = (pr.insert(act + 1, 2)) - 1; // то следующим действием будет движение влево.
//	}
//
//	if (Square::y0 >= 25) //Если слишком близко к низу,
//	{
//		act = (pr.insert(act + 1, 3)) - 1; // то следующим действием будет движение вверх.
//	}
//
//	if (Square::y0 <= 5) //Если слишком близко к верху,
//	{
//		act = (pr.insert(act + 1, 4)) - 1;// то --- движение вниз.
//	}
//
//	if (x0 <= 10)// Если близко к левому краю, 
//	{
//		act = (pr.insert(act + 1, 1)) - 1;// то -- вправо.
//	}
//	
//	return act;
//}
//В итоге положительная корректировка приводит к раздуванию программы. Квадрат движется все более замысловато, едва касаясь области коррекции.
	//Зависает рядом с границами на время.


//vector<int>::iterator Square::correct_minus(vector<int>::iterator act, vector<int>& pr)
//{
//	bool corr = false;
//	if (x0 >= 50)//Если квадрат слишком близко к правому краю,
//	{
//		try
//		{
//			cout << "Correction x0>=50 ";
//			if (pr.size() == 0)
//				throw "The program is empty!";
//
//			act = pr.erase(act);// то удалим последний эл-т который и привел к этому состоянию.
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
//	if (x0 <= 10)// Если близко к левому краю, 
//	{
//
//		cout << "Correction x0<=10 ";
//		act = pr.erase(act);// то удалим последний эл-т который и привел к этому состоянию.
//		cout << "erasing...";
//		corr = true;
//	}
//
//	if (Square::y0 >= 25) //Если слишком близко к низу,
//	{
//		cout << "Correction y0>25 ";
//		act = pr.erase(act);// то удалим последний эл-т который и привел к этому состоянию.
//		cout << "erasing...";
//		corr = true;
//	}
//
//	if (Square::y0 <= 5) //Если слишком близко к верху,
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
//			act = pr.erase(act);// то удалим последний эл-т который и привел к этому состоянию.
//		}
//		catch (const char* msg)
//		{
//			std::cerr << msg << endl;
//		}
//
//		//act = pr.erase(act);// то удалим последний эл-т который и привел к этому состоянию.
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
//В итоге отрицательная коррекция приводит к опустошению программы и ошибке, когда пытаемся получить итератор на эл-т пустого вектора. Нежелательное поведение 
	// не прекращается, пока не наступит очередь выполняться нужной для этого команде.

vector<int>::iterator Square::correct_replace(vector<int>::iterator act, vector<int>& pr)
{
	

	bool corr = false;
	if ( x0>+50 )//Если квадрат слишком близко к правому краю,
	{
		act = pr.erase(act);// то удалим последний эл-т который и привел к этому состоянию.
		cout << "Erased... ";
		if (act == pr.end())
		{
			cout << "End! ";
			act = pr.insert(act, 2);
		}
		else
		{
			act = pr.insert(act + 1, 2); // то следующим действием будет движение влево. 
		}
		cout << "Inserted... ";

		corr = true;
	}

	if (y0>=25) //Если слишком близко к низу,
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
			act = pr.insert(act + 1, 3); // то следующим действием будет движение вверх.
		}
		
		cout << "Inserted... ";
		corr = true;
	}

	if (y0<=5) //Если слишком близко к верху,
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
			act = pr.insert(act + 1, 4);// то --- движение вниз.
		}
		cout << "Inserted... " << (act == pr.end()) << " ";
		corr = true;
	}

	if (x0<=10)// Если близко к левому краю, 
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
			act = pr.insert(act + 1, 1);// то -- вправо.
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
// При коррекции заменой программа сохраняет свой размер. Чем она меньше, тем увереннее движение. Тем больше влияние отдельной коррекции. Квадрат как бы отражается от границ
// и почти прямолинейно идет к противоположному краю.

