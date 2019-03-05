#include "pch.h"
#include "Focus of attention.h"
#include "Cluster.h"
#include "Inspector.h"

//Функция переместит фокус внимания в примерный центр тяжести объекта.
void Focus_of_attention::to_Weight_Center(const Inner_frame & ws)
{
	bool	foc_move_up		= false;	//Переменная, показывающая, что фокус уже передвигался вверх.
	bool	foc_move_down	= false;	//Переменная, показывающая, что фокус уже передвигался вниз.
	int		upCount			= 0;		//Счетчик пикселей объекта выше фокуса.
	int		downCount		= 0;		//Счетчик пикселей объекта ниже фокуса.

	while ((foc_move_up == false) || (foc_move_down == false))//Пока фокус не двигался в обе стороны.
	{

		upCount = 0;//Считаем пиксели выше фокуса.
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

		downCount = 0;//Считаем ниже.
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
		if (upCount > downCount)//Если выше пикселей больше,
		{
			--loc_.y_;			//то передвигаем фокус вверх
			foc_move_up = true;	//Теперь фокус двигался вверх.
		}
		else if (upCount < downCount)//Если меньше --
		{
			++loc_.y_;				//передвигаем вниз.
			foc_move_down = true;	//Теперь фокус двигался вниз.
		}
		else//Если выше и ниже пикселей одинаково,
		{
			break;//то центр найден и цикл надо завершить.
		}
	}
	//cout << "upCount: " << upCount << " downCount " << downCount << endl;

	bool	foc_move_left	= false;	//Переменная, показывающая, что фокус уже передвигался влево.
	bool	foc_move_right	= false;	//Переменная, показывающая, что фокус уже передвигался вправо.
	int		leftCount		= 0;		//Счетчик пикселей объекта левее фокуса.
	int		rightCount		= 0;		//Счетчик пикселей объекта правее фокуса.

	while ((foc_move_left == false) || (foc_move_right == false))//Все аналогично действиям для игреков.
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

//Задает координаты 9-ти элементарных кластеров вокруг фокуса.
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

	for (auto & e : vcl)//Каждый кластер подсчитывает кол-во знаков, отличных от фона.
	{
		e.counter(ws, background_);
	}
	//Ищем наиболее заполненный.
	sort(vcl.begin(), vcl.end(), [](Cluster & c1, Cluster & c2) {return c1.get_count() > c2.get_count(); });

	//Возвращаем его.
	return vcl[0].where();
}

//Пытается передвинуть фокус внутрь объекта.
bool Focus_of_attention::go_inside(const Inner_frame& ws)
{
	Location fcl = clusterize(ws);//Получаем наиболее заполненный элементарный кластер.
	Location center = { fcl.x_ + 3, fcl.y_ + 3 }; //Середина этого кластера.

	//Передвигаем фокус. 
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


//Определить границы области, в которой полностью находится объект. Соответственно им установить границы области концентрации внимания.
//Установить режим частичной концентрации.
void Focus_of_attention::part_concentrate_to_object(const Inner_frame & ws)
{
	Inspector ins(loc_.x_, loc_.y_, background_, object_);//Создаем инспектора для обхода по контуру.

	Borders object_area = ins.left_inspect(ws, 1);//Обходим фигуру по часовой стрелке, начиная с левого края. Получаем точные габариты в виде структуры, где указано, в каком диапазоне координат 
														// содержится наша фигура.

	//Границы устанавливаются по результатам обхода.
	borders_ = object_area;

	//Положение центра объекта.
	Location center = { (borders_.x_max_ + borders_.x_min_) / 2, (borders_.y_max_ + borders_.y_min_) / 2 };
	//Перенесем фокус внимания в центр области, занимаемой объектом
	relocate(center); 

	//Режим внимания меняется на частично сконцентрированный.
	mode_par_con();
}
