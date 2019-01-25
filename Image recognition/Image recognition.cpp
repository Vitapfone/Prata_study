// Image recognition.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include "My_names.h"
#include "Simple structures.h"
#include "Warning.h"
#include "Figures.h"
#include "Cluster.h"
#include "Inspector.h"
#include "Focus of attention.h"

#include "Id_string.h"
#include "Image.h"
#include "Function templates.h"

using namespace My_names;

constexpr size_t WIDTH = 120;//Константа, задающая ширину рабочего пространства.
constexpr size_t HEIGHT = 60;//Константа, задающая высоту рабочего пространства.
constexpr double EQUALITY_MIN = 0.85;//Константа, определяющая минимальное сходство образов для решения об их идентичности.

int main()
{
	//УЧАСТОК ИНИЦИАЛИЗАЦИИ /////////////////////////////////////////////////////////////////////////////////////////////////////

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
	vector<Image> im_vec;//Вектор образов

	Image temp1;

	while (temp1.bin_read(ifs_Images))//Чтение из файла во временный объект.
	{
		temp1.set_is_link(&string_map[temp1.get_is_link().id]);//Восстановление связей.
		temp1.set_non_link(&string_map[temp1.get_non_link().id]);

		im_vec.push_back(temp1);
	}

	//ПОДГОТОВКА РАБОЧЕГО ПРОСТРАНСТВА

	array<array<char, WIDTH>, HEIGHT> ar1; //Пустой двумерный массив.

	//Square fig(15, 2, 56);//Создаем квадрат со стороной не менее 2.
	Circle fig(70, 30, 25);//Круг создавать радиусом не менее 5. Иначе не различает от ромба.
	//Rhomb fig(60, 30, 25);//Ромб определять с диагональю не менее 4.
	//My::Rectangle fig(15, 2, 55);
	//Triangle fig(35, 5, 50);//Треугольник создавать со стороной не менее 4. Иначе не распознает сам себя.  При стороне 2 -- зависает.

																							//system("mode con lines=60 cols=100");//Задаем размер окна консоли, где сначала кол-во строк, потом столбцов.
	system("pause");//Пауза в начале, чтобы можно было позиционировать окно как надо.

	//Заполняем массив пробелами.
		for (auto &e : ar1) 
		{
			for (auto &e2 : e)
			{
				e2 = ' ';
			}
		}
		cout << "Array constructed. " << endl;

		//Вызываем функцию, чтобы она нарисовала нашу фигуру.
		cout << "Before print " << endl;
		fig.print(ar1);
		cout << "After print" << endl;



	//УЧАСТОК УПРАВЛЕНИЯ ВНИМАНИЕМ ///////////////////////////////////////////////////////////////////////////////////////////////////

		Focus_of_attention foc(10, 10, ar1);//Задаем начальное положение фокуса внимания.

		//Простейшая функция управления вниманием. Выдает координаты кластера, в котором больше всего точек, отличных от фона. Файл Cluster.h
		Warning w1 = most_filled_cluster(ar1, foc.get_background());

		//Вектор для хранения предупреждений от функций управления вниманием внешнего потока.
		vector<Warning> warnings;
		warnings.push_back(w1);
		//Сортируем так, чтобы первым эл-том был тот, у кого наибольшая важность.
		sort(warnings.begin(), warnings.end(), [](const Warning & w1, const Warning & w2) {return w1.get_importance() > w2.get_importance(); });
		Warning most_important = warnings[0];

		most_important.what();//Отладочный вывод.

		//Переместить к нему фокус внимания.
		foc.relocate(most_important.where());
		
		 int count = 0;
		 cout << "Before elemental clusterization" << endl;
		 do
		 {
			 ++count;

		 } while (!foc.go_inside(ar1));//Пока фокус не попал на объект, будем пытаться его туда направить.
		cout <<"Number of relocations: "<< count << endl;//Показываем, сколько раз пришлось двигать фокус.

		foc.assign_object(ar1);//Устанавливаем символ объекта.

		//cout <<"Object is '"<< foc.object <<"'"<< endl;

		//foc.mark(ar1); //Обозначаем положение фокуса внимания.
		//print_workspase(ar1);




	//УЧАСТОК КОНСТРУИРОВАНИЯ ОБРАЗА//////////////////////////////////////////////////////////////////////////////////////////////

		//Область внимания устанавливается в размер не больший, чем нужно для вмещения всего объекта.
		foc.part_concentrate_to_object(ar1);//Режим внимания теперь частично-сконцентрированный.

		//Границы зоны объекта. В них и будет работать алгоритм распознавания.
		Borders object_area = foc.get_borders();

		//Создаем образ.
		Image figure(object_area, ar1, foc.get_background(), foc.get_object());
																							//cout <<figure.get_widht()<<" "<<figure.get_height()<<" "<< figure.get_aspect() << endl;
		//Попробуем найти "центр тяжести" объекта.
		cout <<"Searching center of gravity..."<< endl;
		foc.to_Weight_Center(ar1);

		foc.mark(ar1); //Обозначаем положение фокуса внимания.
		cout << endl;

		//Отрисовываем рабочее пространство.
		print_workspase(ar1);
			



	//УЧАСТОК РАСПОЗНАВАНИЯ ///////////////////////////////////////////////////////////////////////////////////////////
		
	//РАСПОЗНАВАНИЕ

		bool match = false;//Логическая переменная, истинность которой означает, что образ распознан.

		//Тут проверяется соответствие образов актуальной фигуры и образа, ранее записанного в файл. Выводятся сообщения о соответствии.
		for (const Image &im : im_vec)
		{
			if (image_equality(figure, im, EQUALITY_MIN))//Если образы совпадают.
			{
				match = true;
				figure.set_is_link(im.get_is_link());//Установлена идентичность образов, значит оба образа должны хранить один и тот же указатель.
				cout << "Images are equal!!\n\t" << (figure.get_is_link().ps->get_data()) << endl;//Выводим содержимое указателя, сообщая юзеру, что это за фигура.
				break;//Как только совпадение найдено, завершаем проверку.
			}
			else//Образы не совпадают.
			{
				cout << "No match!\n" << (im.get_non_link().ps->get_data()) << endl;//Выводим сообщение об этом и специфическое для эталонного образа сообщение.
			}
			cout << endl;
		}

	//УЧАСТОК МЫСЛИТЕЛЬНОЙ РАБОТЫ /////////////////////////////////////////////////////////////////////////////////////

	// ИМИТАЦИЯ СОЗДАНИЯ НОВЫХ СВЯЗЕЙ

		if (match == false)//Образы не совпали ни с одним эталоном.
		{
			//Временные строки.
			string figure_name;
			string new_figure_link;
			string new_figure_non_link;

			cout << "Adding new figure  to a database. It's name is:";//Надо ввести имя для новой фигуры.
			cin >> figure_name;

			new_figure_link = "This is " + figure_name + ".";//Конструируются строки сообщений, которые здесь имитируют связи новой фигуры.
			Id_string id_new_figure_link(new_figure_link);
			new_figure_non_link = "Not equal to " + figure_name + ".";
			Id_string id_new_figure_non_link(new_figure_non_link);

			string_map[id_new_figure_link.get_id()] = id_new_figure_link;//Вставляем новые строки в карту.
			string_map[id_new_figure_non_link.get_id()] = id_new_figure_non_link;

			figure.set_is_link(&string_map[id_new_figure_link.get_id()]);//Фигура получает свои связи.
			figure.set_non_link(&string_map[id_new_figure_non_link.get_id()]);

			im_vec.push_back(figure);//Образ неизвестной ранее фигуры добавляется в вектор эталонов.

			//Вектор, дополненный новой фигурой, перебирается еще раз, чтобы проверить распознавание этой добавленной фигуры.
			for (const Image &im : im_vec)
			{
				if (image_equality(figure, im, EQUALITY_MIN))//Если образы совпадают.
				{
					match = true;
					figure.set_is_link(im.get_is_link());//Установлена идентичность образов, значит оба образа должны хранить один и тот же указатель.
					cout << "Images are equal!!\n\t" << (figure.get_is_link().ps->get_data()) << endl;//Выводим содержимое указателя, сообщая юзеру, что это за фигура.
					break;
				}
				else//Образы не совпадают.
				{
					cout << "No match!\n" << (im.get_non_link().ps->get_data()) << endl;//Выводим сообщение об этом и специфическое для эталонного образа сообщение.
				}
				cout << endl;
			}
		}



	//УЧАСТОК ПОДГОТОВКИ К СЛЕДУЮЩЕМУ ЦИКЛУ СОЗНАНИЯ ///////////////////////////////////////////////////////////////////////////////

		warnings.clear();//Очищаем список предупреждений, чтобы заполнить его в следующем цикле.

		
	//УЧАСТОК ЗАПИСИ ДАННЫХ В ФАЙЛЫ ПЕРЕД ЗАВЕРШЕНИЕМ ПРОГРАММЫ //////////////////////////////////////////////////////////////////

		ofstream ofstrings("Strings\\strings_data.bin", ofstream::binary);//Создаем файл для записи связанных с образами строк. Папка должна быть создана заранее.
		for (auto &e : string_map)//Записываем все строки из карты.
		{
			e.second.bin_write(ofstrings);
		}
		ofstrings.close();//Закрываем поток.

		ofstream ofsImages("Figures\\figures_data.bin", ofstream::binary);//Создаем файл для записи образов.
		for (auto & e : im_vec)
		{
			e.bin_write(ofsImages);
		}
		ofsImages.close();

	return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
