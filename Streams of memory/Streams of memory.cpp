// Streams of memory.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "My_names.h"
#include "Simple structures.h"
#include "Outer_stream.h"
#include "Inner_stream.h"
#include "Figures.h"
#include "Warning.h"
#include "Cluster.h"
#include "Inspector.h"
#include "Focus of attention.h"
#include "Id_string.h"
#include "Image.h"

using namespace My_names;

constexpr size_t Width = 120;//Константа, задающая ширину рабочего пространства.
constexpr size_t Height = 56;//Константа, задающая высоту рабочего пространства.
constexpr size_t Frames = 130;//Количество переданных в поток кадров.

constexpr double Equality_min = 0.85;//Константа, определяющая минимальное сходство образов для решения об их идентичности.

void figure_moving(Square &, size_t);//Движение фигуры в зависимости от стадии цикла записи.

int main()
{
	system("pause");
	
//УЧАСТОК ИНИЦИАЛИЗАЦИИ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//ЧТЕНИЕ СТРОК ИЗ ФАЙЛА

	map<int, Id_string> string_map;//Карта для хранения прочитанных строк в соответствии с их идентификаторами.
	ifstream ifs_str("Strings\\strings_data.bin", ifstream::binary);

	Id_string temp;//Временный объект строки.
	while (temp.bin_read(ifs_str))//Пока не достигнут конец файла.
	{
		string_map[temp.get_id()] = temp;
	}

	//КОНСТРУИРОВАНИЕ ОБРАЗОВ ИЗ ФАЙЛОВ.

	ifstream ifs_Images("Figures\\figures_data.bin", ifstream::binary);
	list<Image> im_list;//Вектор образов

	Image temp1;

	while (temp1.bin_read(ifs_Images))//Чтение из файла во временный объект.
	{
		temp1.set_is_link(&string_map[temp1.get_is_link().id]);//Восстановление связей.
		temp1.set_non_link(&string_map[temp1.get_non_link().id]);

		im_list.push_back(temp1);
	}


	//КОНСТРУИРОВАНИЕ ПОТОКОВ
	Square fig(20, 10, 10);//Фигура для демонстрации записи в поток.

	Outer_stream<Width, Height> outs(3);//Внешний поток заданной длины.
	Inner_stream ins(Width, Height, Frames - 2);//Внутренний поток.

	Focus_of_attention foc(10, 10, ins.Input_frame());//Задаем начальное положение фокуса внимания.

	for (size_t i = 0; i < Frames; i++)//Цикл записи.
	{

	//УЧАСТОК ВВОДА ДАННЫХ ВО ВНЕШНИЙ ПОТОК /////////////////////////////////////////////////////////////////////////////////////////////////////////

		fig.print(outs.Input_frame());//Фигура отрисовывает себя на предоставленном потоком кадре ввода.

		//outs.print_input();//Отрисовка кадра ввода.

		outs.process();//Кадр ввода отправляется в поток.



	//УЧАСТОК УПРАВЛЕНИЯ ВНИМАНИЕМ ///////////////////////////////////////////////////////////////////////////////////////////////////

		//Focus_of_attention foc(10, 10, ar1);//Задаем начальное положение фокуса внимания.

		//Вектор для хранения предупреждений от функций управления вниманием внешнего потока.
		vector<Warning> warnings;

		//Простейшая функция управления вниманием. Выдает координаты кластера, в котором больше всего точек, отличных от фона. Файл Cluster.h
		Warning w1 = most_filled_cluster(outs.get_frame(0), ' ');

		//Заносим предупреждение в вектор.
		warnings.push_back(w1);

		if (i > 0)//Проверка нужна, т.к. в самом начале записи еще нет второго кадра потока.
		{
			//Простейшая ф-я управления вниманием. Выдает предупреждение с координатами кластера, в котором больше всего точек, состояние которых изменилось с прошлого кадра.
			Warning w2 = most_difference_in_cluster(outs.get_frame(0), outs.get_frame(1));
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
		Outer_frame<Width, Height> outer_data = outs.get_frame(0);

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

		//Переместить к нему фокус внимания.
		foc.relocate(most_important.where());

		Inner_frame & current_frame = ins.get_frame(0);

		int count = 0;
		//cout << "Before elemental clusterization" << endl;
		do
		{
			++count;

		} while (!foc.go_inside(current_frame));//Пока фокус не попал на объект, будем пытаться его туда направить.
		//cout << "Number of relocations: " << count << endl;//Показываем, сколько раз пришлось двигать фокус.

		foc.assign_object(current_frame);//Устанавливаем символ объекта.
		

		//УЧАСТОК КОНСТРУИРОВАНИЯ ОБРАЗА//////////////////////////////////////////////////////////////////////////////////////////////

		//Область внимания устанавливается в размер не больший, чем нужно для вмещения всего объекта.
		foc.part_concentrate_to_object(current_frame);//Режим внимания теперь частично-сконцентрированный.

		//Границы зоны объекта. В них и будет работать алгоритм распознавания.
		Borders object_area = foc.get_borders();

		//Создаем образ.
		Image figure(object_area, current_frame, foc.get_background(), foc.get_object());
		
		//Попробуем найти "центр тяжести" объекта.
		//cout << "Searching center of gravity..." << endl;
		foc.to_Weight_Center(current_frame);


		Inner_frame current_frame_copy = current_frame;
		foc.mark(current_frame_copy); //Обозначаем положение фокуса внимания.
		//cout << endl;

		//Отрисовываем текущий кадр.
		print_frame(current_frame_copy);




		//УЧАСТОК РАСПОЗНАВАНИЯ ///////////////////////////////////////////////////////////////////////////////////////////

		//РАСПОЗНАВАНИЕ

		bool match = false;//Логическая переменная, истинность которой означает, что образ распознан.

		//Тут проверяется соответствие образов актуальной фигуры и образа, ранее записанного в файл. Выводятся сообщения о соответствии.
		for (const Image &im : im_list)
		{
			if (image_equality(figure, im, Equality_min))//Если образы совпадают.
			{
				match = true;
				figure.set_is_link(im.get_is_link());//Установлена идентичность образов, значит оба образа должны хранить один и тот же указатель.
				cout << "Images are equal!!\t" << (figure.get_is_link().ps->get_data()) << endl;//Выводим содержимое указателя, сообщая юзеру, что это за фигура.
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
			Id_string id_new_figure_link(new_figure_link);
			string new_figure_non_link = "Not equal to " + figure_name + ".";
			Id_string id_new_figure_non_link(new_figure_non_link);

			string_map[id_new_figure_link.get_id()] = id_new_figure_link;//Вставляем новые строки в карту.
			string_map[id_new_figure_non_link.get_id()] = id_new_figure_non_link;

			figure.set_is_link(&string_map[id_new_figure_link.get_id()]);//Фигура получает свои связи.
			figure.set_non_link(&string_map[id_new_figure_non_link.get_id()]);

			im_list.push_back(figure);//Образ неизвестной ранее фигуры добавляется в вектор эталонов.

			//Вектор, дополненный новой фигурой, перебирается еще раз, чтобы проверить распознавание этой добавленной фигуры.
			for (const Image &im : im_list)
			{
				if (image_equality(figure, im, Equality_min))//Если образы совпадают.
				{
					match = true;
					figure.set_is_link(im.get_is_link());//Установлена идентичность образов, значит оба образа должны хранить один и тот же указатель.
					cout << "Images are equal!!\n\t" << (figure.get_is_link().ps->get_data()) << endl;//Выводим содержимое указателя, сообщая юзеру, что это за фигура.
					break;
				}
				//else//Образы не совпадают.
				//{
				//	cout << "No match!\n" << (im.get_non_link().ps->get_data()) << endl;//Выводим сообщение об этом и специфическое для эталонного образа сообщение.
				//}
				cout << endl;
			}
		}


		

		system("cls");

		//Движение фигуры в зависимости от стадии цикла записи.
		figure_moving(fig, i);


	//УЧАСТОК ПОДГОТОВКИ К СЛЕДУЮЩЕМУ ЦИКЛУ СОЗНАНИЯ ///////////////////////////////////////////////////////////////////////////////

		warnings.clear();//Очищаем список предупреждений, чтобы заполнить его в следующем цикле.

		
	}


//УЧАСТОК ЗАПИСИ ДАННЫХ В ФАЙЛЫ ПЕРЕД ЗАВЕРШЕНИЕМ ПРОГРАММЫ //////////////////////////////////////////////////////////////////

	ofstream ofstrings("Strings\\strings_data.bin", ofstream::binary);//Создаем файл для записи связанных с образами строк. Папка должна быть создана заранее.
	for (const auto &e : string_map)//Записываем все строки из карты.
	{
		e.second.bin_write(ofstrings);
	}
	ofstrings.close();//Закрываем поток.

	ofstream ofsImages("Figures\\figures_data.bin", ofstream::binary);//Создаем файл для записи образов.
	for (const auto & e : im_list)
	{
		e.bin_write(ofsImages);
	}
	ofsImages.close();


	//ins.play(10);//Вывод содержимого потока в консоль.

	cout << "End...\n";

	return 0;
}


//Движение фигуры в зависимости от стадии цикла записи.
void figure_moving(Square & fig, size_t i)
{
	//Далее код для простейшего движения фигуры. Фигура пройдет по кругу за время цикла записи.
	if (i <= Frames / 4)
	{
		fig.moveRight();
	}
	else if (i <= Frames / 2)
	{
		fig.moveDown();
	}
	else if (i <= 0.75*Frames)
	{
		fig.moveLeft();
	}
	else
	{
		fig.moveUp();
	}
}

