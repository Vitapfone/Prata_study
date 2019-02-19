﻿// Streams of memory.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
//#include "My_names.h"
//#include "Simple structures.h"
#include "Outer_stream.h"
#include "Inner_stream.h"
#include "Figures.h"
#include "Warning.h"
#include "Cluster.h"
//#include "Inspector.h"
#include "Focus of attention.h"
//#include "Id_string.h"
#include "Image.h"
#include "Link.h"


//using namespace My_names;

constexpr size_t Width = 120;//Константа, задающая ширину рабочего пространства.
constexpr size_t Height = 56;//Константа, задающая высоту рабочего пространства.
constexpr size_t Frames = 1;//Количество переданных в поток кадров.

constexpr double Equality_min = 0.85;//Константа, определяющая минимальное сходство образов для решения об их идентичности.

void figure_moving(Figure &, size_t);//Движение фигуры в зависимости от стадии цикла записи.

//Заполнение переданных контейнеров базы данных из файлов.
void database_initialization(const string & file1, const string & file2, const string & file3, map<int, Image> & images, map<int, Link> & links, map<int, Id_string> & strings);
//Запись содержимого контейнеров в файлы.
void database_recording(const string & file1, const string & file2, const string & file3, map<int, Image> & images, map<int, Link> & links, map<int, Id_string> & strings);

int main()
{
	system("pause");
	
//УЧАСТОК ИНИЦИАЛИЗАЦИИ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//ЗАПОЛНЕНИЕ БАЗЫ ДАННЫХ ИЗ ФАЙЛОВ.

	map<int, Id_string> string_map;//Карта для хранения прочитанных строк в соответствии с их идентификаторами.
	map<int, Link> link_map;//Карта для хранения связей в соответствии с их айди.
	map<int,Image> image_map;//Карта для образов.

	cout << "Before database initialisation\n";

	//Функция выполняет всю работу.
	database_initialization(  "Figures\\figures_data.bin", "Links\\links_data.bin", "Strings\\strings_data.bin", image_map, link_map, string_map);
	
	cout << "After database initialisation\n";
	cout << image_map.size() << ' ' << link_map.size() << ' ' << string_map.size() << endl;
	
	char g;
	cin >> g;
	cin.ignore(1000, '\n');

	//КОНСТРУИРОВАНИЕ ПОТОКОВ
	Square fig(20, 3, 50);//Фигура для демонстрации записи в поток.
	//My::Rectangle fig(20, 10, 10);
	//Circle fig(20, 10, 9);
	//Rhomb fig(20, 10, 10);
	//Triangle fig(20, 10, 10);

	Outer_stream<Width, Height> outs(3);//Внешний поток заданной длины.
	Inner_stream ins(Width, Height, Frames - 2);//Внутренний поток.

	Focus_of_attention foc(10, 10, ins.Input_frame());//Задаем начальное положение фокуса внимания.


//УЧАСТОК РАБОЧЕГО ПРОЦЕССА//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (size_t i = 0; i < Frames; i++)//Цикл записи.
	{

	//УЧАСТОК ВВОДА ДАННЫХ ВО ВНЕШНИЙ ПОТОК /////////////////////////////////////////////////////////////////////////////////////////////////////////

		fig.print(outs.Input_frame());//Фигура отрисовывает себя на предоставленном потоком кадре ввода.

		outs.process();//Кадр ввода отправляется в поток.



	//УЧАСТОК УПРАВЛЕНИЯ ВНИМАНИЕМ ///////////////////////////////////////////////////////////////////////////////////////////////////

		//Вектор для хранения предупреждений от функций управления вниманием внешнего потока.
		vector<Warning> warnings;

		//Простейшая функция управления вниманием. Выдает координаты кластера, в котором больше всего точек, отличных от фона. Файл Cluster.h
		Warning w1 = most_filled_cluster(outs.get_ro_frame(0), ' ');

		//Заносим предупреждение в вектор.
		warnings.push_back(w1);

		if (i > 0)//Проверка нужна, т.к. в самом начале записи еще нет второго кадра потока.
		{
			//Простейшая ф-я управления вниманием. Выдает предупреждение с координатами кластера, в котором больше всего точек, состояние которых изменилось с прошлого кадра.
			Warning w2 = most_difference_in_cluster(outs.get_ro_frame(0), outs.get_ro_frame(1));
			//Заносим предупреждение в вектор.
			warnings.push_back(w2);
		}
		




		//НАЧАЛО РАБОТЫ ФИЛЬТРА ВОСПРИЯТИЯ. НА БУДУЩЕЕ. ПОКА НИЧЕГО НЕТ!

		//На будущее. Фильтр восприятия обрабатывает все предупреждения, корректируя их важность. 

		//После занесения всех предупреждений сортируем так, чтобы первым эл-том был тот, у кого наибольшая важность.
		sort(warnings.begin(), warnings.end(), [](const Warning & w1, const Warning & w2) {return w1.get_importance() > w2.get_importance(); });
		Warning most_important = warnings[0];

		//Передача данных от внешнего потока внутреннему. Пока без каких-либо ограничений и модификаций.

		//Внешний поток выдает свой нулевой кадр. 
		Outer_frame<Width, Height> outer_data = outs.get_ro_frame(0);

		//Буфер для конвертации данных в формат кадра внутреннего потока.
		Inner_frame buffer;
		for (auto & e : outer_data)//Конвертация.
		{
			buffer.emplace_back(e.cbegin(), e.cend());
		}

		//КОНЕЦ РАБОТЫ ФИЛЬТРА ВОСПРИЯТИЯ.



		//Ввод данных во внутренний поток.
		ins.Input_frame() = move(buffer);//Используется семантика перемещения.
		ins.process();




	//УЧАСТОК РАБОТЫ АЛГОРИТМОВ ВНУТРЕННЕГО ПОТОКА//////////////////////////////////////////////////////////////////////////////////////////////

		//Переместить фокус внимания к месту, указанному в важнейшем предупреждении.
		foc.relocate(most_important.where());

		//Создаем ссылку на первый кадр потока, чтобы не вызывать функцию каждый раз.
		const Inner_frame & current_frame = ins.get_ro_frame(0);

		int count = 0;
		//cout << "Before elemental clusterization" << endl;
		do
		{
			++count;

		} while (!foc.go_inside(current_frame));//Пока фокус не попал на объект, будем пытаться его туда направить.
		//cout << "Number of relocations: " << count << endl;//Показываем, сколько раз пришлось двигать фокус.

		foc.assign_object(current_frame);//Устанавливаем символ объекта.
		

		//КОНСТРУИРОВАНИЕ ОБРАЗА

		//Область внимания устанавливается в размер не больший, чем нужно для вмещения всего объекта.
		foc.part_concentrate_to_object(current_frame);//Режим внимания теперь частично-сконцентрированный.

		//Границы зоны объекта. В них и будет работать алгоритм распознавания.
		Borders object_area = foc.get_borders();

		//Попробуем найти "центр тяжести" объекта.
		//cout << "Searching center of gravity..." << endl;
		foc.to_Weight_Center(current_frame);

		//Создаем образ.
		Image figure(object_area, current_frame, foc.get_background(), foc.get_object());
		
		//Копия текущего кадра, чтобы все его модификации для наглядности не сохранялись в потоке.
		Inner_frame current_frame_copy = current_frame;
		foc.mark(current_frame_copy); //Обозначаем положение фокуса внимания.

		cout << endl;

		//Отрисовываем текущий кадр.
		print_frame(current_frame_copy);


		//РАСПОЗНАВАНИЕ ОБРАЗА

		bool match = false;//Логическая переменная, истинность которой означает, что образ распознан.

		//Тут проверяется соответствие образов актуальной фигуры и образа, ранее записанного в файл. Выводятся сообщения о соответствии.
		for (const auto & e : image_map)
		{
			auto & im = e.second;

			if (image_equality(figure, im, Equality_min))//Если образы совпадают.
			{
				match = true;
				figure.set_is_link(im.get_is_link());//Установлена идентичность образов, значит оба образа должны хранить один и тот же указатель.
				cout << "Images are equal!!\t";

				//Через связь надо получить доступ к строке.
				cout << (figure.get_is_link().pl->get_right_ptr()->get_data()) << endl;

				Image::decrease_counter();//Уменьшаем счетчик, т.к. эта фигура не будет записываться в файл.

				break;//Как только совпадение найдено, завершаем проверку.
			}

			//else//Образы не совпадают.
			//{
			//	cout << "No match!\n" << (im.get_non_link().ps->get_data()) << endl;//Выводим сообщение об этом и специфическое для эталонного образа сообщение.
			//}
			//cout << endl;
		}


		//УЧАСТОК МЫСЛИТЕЛЬНОЙ РАБОТЫ /////////////////////////////////////////////////////////////////////////////////////

		// ИМИТАЦИЯ СОЗДАНИЯ НОВЫХ СВЯЗЕЙ

		if (match == false)//Образы не совпали ни с одним эталоном.
		{
			//Временные строки.
			string figure_name;

			cout << "Adding new figure  to a database. It's name is:";//Надо ввести имя для новой фигуры.
			cin >> figure_name;

			string new_figure_link{ "This is " + figure_name + "." };//Конструируются строки сообщений, которые здесь имитируют связи новой фигуры.
			Id_string new_string(new_figure_link);
			
			
			

			//Создаем новую связь для образа и строки.
			Link new_link(&figure, figure.get_id(), 10, &new_string, new_string.get_id(), 10);
			

			//Регистрируем связь в образе.
			figure.set_is_link({ &new_link, Link_side::left, new_link.get_id() });
			//Регистрируем связь в строке.
			new_string.set_is_link({ &new_link, Link_side::right, new_link.get_id() });

			//Вставляем новую связь в карту.
			link_map[new_link.get_id()] = new_link;
			string_map[new_string.get_id()] = new_string;//Вставляем новые строки в карту.
			image_map[figure.get_id()] = figure;//Вставляем новую фигуру в карту.

			assert(new_string.get_id() == figure.get_id());
			cout << new_string.get_id() << ' ' << figure.get_id() << endl;

			//Вектор, дополненный новой фигурой, перебирается еще раз, чтобы проверить распознавание этой добавленной фигуры.
			for (const auto & e : image_map)
			{
				auto & im = e.second;

				if (image_equality(figure, im, Equality_min))//Если образы совпадают.
				{
					match = true;
					figure.set_is_link(im.get_is_link());//Установлена идентичность образов, значит оба образа должны хранить один и тот же указатель.
					cout << "Images are equal!!\t";

					//Через связь надо получить доступ к строке.
					cout << figure.get_is_link().pl->get_right_ptr()->get_data() << endl;

					break;//Как только совпадение найдено, завершаем проверку.
				}
				//else//Образы не совпадают.
				//{
				//	cout << "No match!\n" << (im.get_non_link().ps->get_data()) << endl;//Выводим сообщение об этом и специфическое для эталонного образа сообщение.
				//}
				cout << endl;
			}
		}


		

		//system("cls");

		//Движение фигуры в зависимости от стадии цикла записи.
		figure_moving(fig, i);


	//УЧАСТОК ПОДГОТОВКИ К СЛЕДУЮЩЕМУ ЦИКЛУ СОЗНАНИЯ ///////////////////////////////////////////////////////////////////////////////

		warnings.clear();//Очищаем список предупреждений, чтобы заполнить его в следующем цикле.
	}


//УЧАСТОК ЗАПИСИ ДАННЫХ В ФАЙЛЫ ПЕРЕД ЗАВЕРШЕНИЕМ ПРОГРАММЫ //////////////////////////////////////////////////////////////////
	cout << image_map.size() << ' ' << link_map.size() << ' ' << string_map.size() << endl;
	
	//Функция выполняет всю работу.
	database_recording("Figures\\figures_data.bin", "Links\\links_data.bin", "Strings\\strings_data.bin", image_map, link_map, string_map);

	//ins.play(10);//Вывод содержимого потока в консоль.

	cout << "End...\n";

	return 0;
}


//Движение фигуры в зависимости от стадии цикла записи.
void figure_moving(Figure & fig, size_t i)
{
	//Далее код для простейшего движения фигуры. Фигура пройдет по кругу за время цикла записи.
	if (i <= Frames / 4)
	{
		fig.move_right();
	}
	else if (i <= Frames / 2)
	{
		fig.move_down();
	}
	else if (i <= 0.75*Frames)
	{
		fig.move_left();
	}
	else
	{
		fig.move_up();
	}
}

