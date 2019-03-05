// Streams of memory.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"

#include "Outer_stream.h"
#include "Inner_stream.h"
#include "Figures.h"
#include "Warning.h"
#include "Cluster.h"
#include "Focus of attention.h"
#include "Image.h"
#include "Link.h"

//using namespace My_names;

constexpr size_t	Width		= 120;	//Константа, задающая ширину рабочего пространства.
constexpr size_t	Height		= 80;	//Константа, задающая высоту рабочего пространства.
constexpr size_t	Frames		= 180;	//Количество переданных в поток кадров.
constexpr float		Scale		= 10.0;	//Коэффициент масштаба отображаемого кадра относительно кадра потока.
constexpr float		Rad			= 5.0;	//Радиус метки фокуса внимания.

constexpr double Equality_min	= 0.85;//Константа, определяющая минимальное сходство образов для решения об их идентичности.

//Движение фигуры в зависимости от стадии цикла записи.
void figure_moving(Figure &, size_t);

//Заполнение переданных контейнеров базы данных из файлов.
void database_initialization(const string &			file1,
							 const string &			file2, 
							 const string &			file3, 
							 map<int, Image> &		images, 
							 map<int, Link> &		links, 
							 map<int, Id_string> &	strings);

//Запись содержимого контейнеров в файлы.
void database_recording(const string &			file1,
						const string &			file2,
						const string &			file3,
						map<int, Image> &		images,
						map<int, Link> &		links,
						map<int, Id_string> &	strings);

//Создание отрисовываемой формы на основе типа фигуры.
unique_ptr<sf::Shape> get_visible_shape(const Figure* fig, float scale);

//Вывести меню выбора типа фигуры.
void display_menu();

//Функция для выбора типа создаваемой фигуры.
unique_ptr<Figure> select_figure();


int main()
{
	//Пауза для удобства начального позиционирования окна консоли.
	system("pause");
	
//УЧАСТОК ИНИЦИАЛИЗАЦИИ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//ЗАПОЛНЕНИЕ БАЗЫ ДАННЫХ ИЗ ФАЙЛОВ.

	map<int, Id_string> string_map;	//Карта для хранения прочитанных строк в соответствии с их идентификаторами.
	map<int, Link>		link_map;	//Карта для хранения связей в соответствии с их айди.
	map<int,Image>		image_map;	//Карта для образов.

	//Функция выполняет всю работу.
	database_initialization(	"Figures\\figures_data.bin",	"Links\\links_data.bin",	"Strings\\strings_data.bin", 
								image_map,						link_map,					string_map);
	
	//КОНСТРУИРОВАНИЕ ПОТОКОВ

	Outer_stream<Width, Height> outs(3);		//Внешний поток заданной длины.
	Inner_stream ins(Width, Height, Frames - 2);//Внутренний поток.

	Focus_of_attention foc(10, 10, ins.Input_frame());//Задаем начальное положение фокуса внимания.

	//КОНСТРУИРОВАНИЕ ФИГУР

	unique_ptr<Figure> fig = select_figure();


	//ИНИЦИАЛИЗАЦИЯ ГРАФИКИ

	//Создание окна
	sf::RenderWindow window(sf::VideoMode(Width*Scale, Height*Scale), "Streams of memory");
	window.setPosition(sf::Vector2i(50, 50));

	//Включение вертикальной синхронизации.
	window.setVerticalSyncEnabled(true);

	unique_ptr<sf::Shape>	shape;	//Форма из граф. библиотеки, которая будет представлять наши фигуры.
	Location				pos;	//Положение этой формы.

	if (shape = get_visible_shape(fig.get(), Scale))//Получение отрисовываемой формы на основе типа фигуры.
	{
		pos = fig->where();
		shape->setPosition(pos.x_*Scale, pos.y_*Scale);
	}
	else
	{
		cout << "Error! Wrong figure!";
		exit(EXIT_FAILURE);
	}
	
	sf::CircleShape mark(Rad);//Метка для фокуса внимания.
	mark.setFillColor(sf::Color::Red);


//УЧАСТОК РАБОЧЕГО ПРОЦЕССА//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	for (size_t i = 0; window.isOpen() && i < Frames; i++)//Цикл записи. Можно прервать, закрыв графическое окно.
	{
		//ОБРАБОТКА СОБЫТИЙ ГРАФИЧЕСКОГО ОКНА

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)//Если нажать на крестик (как обычно),
				window.close();//то окно закроется.
		}



	//УЧАСТОК ВВОДА ДАННЫХ ВО ВНЕШНИЙ ПОТОК /////////////////////////////////////////////////////////////////////////////////////////////////////////

		
		//Фигура отрисовывает себя на предоставленном потоком кадре ввода.
		fig->print(outs.Input_frame());
		
		//Кадр ввода отправляется в поток.
		outs.process();



	//УЧАСТОК РАБОТЫ СТОРОЖЕВЫХ АЛГОРИТМОВ ///////////////////////////////////////////////////////////////////////////////////////////////////
		
		
		vector<Warning> warnings;//Вектор для хранения предупреждений от функций управления вниманием внешнего потока.

		//Простейший сторожевой алгоритм. Выдает координаты кластера, в котором больше всего точек, отличных от фона. Файл Cluster.h
		Warning w1 = most_filled_cluster(outs.get_ro_frame(0), ' ');

		//Заносим предупреждение в вектор.
		warnings.push_back(w1);

		if (i > 0)//Проверка нужна, т.к. в самом начале записи еще нет второго кадра потока.
		{
			//Простейший сторожевой алгоритм. Выдает предупреждение с координатами кластера, в котором больше всего точек, состояние которых изменилось с прошлого кадра.
			Warning w2 = most_difference_in_cluster(outs.get_ro_frame(0), outs.get_ro_frame(1));
			//Заносим предупреждение в вектор.
			warnings.push_back(w2);
		}
		

	//УЧАСТОК РАБОТЫ ФИЛЬТРА ВОСПРИЯТИЯ. НА БУДУЩЕЕ. ПОКА НИЧЕГО НЕТ!///////////////////////////////////////////////////////////////////////////

		
		//На будущее. Фильтр восприятия обрабатывает все предупреждения, корректируя их важность. 

		//После занесения всех предупреждений сортируем так, чтобы первым эл-том был тот, у кого наибольшая важность.
		sort(warnings.begin(), warnings.end(), [](const Warning & w1, const Warning & w2) {return w1.get_importance() > w2.get_importance(); });
		Warning most_important = warnings[0];

		//Передача данных от внешнего потока внутреннему. Пока без каких-либо ограничений и модификаций.

		//Внешний поток выдает свой нулевой кадр. 
		Outer_frame<Width, Height> outer_data = outs.get_ro_frame(0);

		Inner_frame buffer;//Буфер для конвертации данных в формат кадра внутреннего потока.

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
		do
		{
			++count;

		} while (!foc.go_inside(current_frame));//Пока фокус не попал на объект, будем пытаться его туда направить.
		
		//Устанавливаем символ объекта.
		foc.assign_object(current_frame);
		
		
		//КОНСТРУИРОВАНИЕ ОБРАЗА

		//Область внимания устанавливается в размер не больший, чем нужно для вмещения всего объекта.
		foc.part_concentrate_to_object(current_frame);//Режим внимания теперь частично-сконцентрированный.
		
		//Границы зоны объекта. В них и будет работать алгоритм распознавания.
		Borders object_area = foc.get_borders();
		
		//Попробуем найти "центр тяжести" объекта.
		foc.to_Weight_Center(current_frame);

		//Создаем образ.
		Image figure(object_area, current_frame, foc.get_background(), foc.get_object());
		
		//Устанавливаем положение метки фокуса внимания.
		mark.setPosition(foc.get_x()*Scale - Rad, foc.get_y()*Scale - Rad);
		
		
		//Отрисовываем текущий кадр.
	
		window.clear(sf::Color::Black);
		window.draw(*shape);
		window.draw(mark);
		window.display();

		//sf::sleep(sf::seconds(0.5));

		//РАСПОЗНАВАНИЕ ОБРАЗА

		bool match = false;//Логическая переменная, истинность которой означает, что образ распознан.

		//Тут проверяется соответствие образов актуальной фигуры и образа, ранее записанного в файл. Выводятся сообщения о соответствии.
		for (const auto & e : image_map)
		{
			auto & im = e.second;

			if (image_equality(figure, im, Equality_min))//Если образы совпадают.
			{
				match = true;

				//Установлена идентичность образов, значит оба образа должны хранить один и тот же указатель.
				figure.set_is_link(im.get_is_link());

				//Через связь надо получить доступ к строке.
				//cout << (figure.get_is_link().pl->get_right_ptr()->get_data()) << endl;

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
			string figure_name;//Временные строки.

			//Надо ввести имя для новой фигуры.
			cout << "Adding new figure  to a database. It's name is:";
			cin >> figure_name;

			//Конструируются строки сообщений, которые здесь имитируют связи новой фигуры.
			string new_figure_link{ "This is " + figure_name + "." };
			Id_string new_string(new_figure_link);
			
			//Создаем новую связь для образа и строки.
			Link new_link(&figure, figure.get_id(), 10, &new_string, new_string.get_id(), 10);
			
			//Регистрируем связь в образе.
			figure.set_is_link({ &new_link, Link_side::left, new_link.get_id() });
			//Регистрируем связь в строке.
			new_string.set_is_link({ &new_link, Link_side::right, new_link.get_id() });

			//Вставляем новую связь в карту.
			link_map[new_link.get_id()] = new_link;
			//Вставляем новые строки в карту.
			string_map[new_string.get_id()] = new_string;
			//Вставляем новую фигуру в карту.
			image_map[figure.get_id()] = figure;

			assert(new_string.get_id() == figure.get_id());
			
			//Вектор, дополненный новой фигурой, перебирается еще раз, чтобы проверить распознавание этой добавленной фигуры.
			for (const auto & e : image_map)
			{
				auto & im = e.second;

				if (image_equality(figure, im, Equality_min))//Если образы совпадают.
				{
					match = true;
					//Установлена идентичность образов, значит оба образа должны хранить один и тот же указатель.
					figure.set_is_link(im.get_is_link());
					cout << "Images are equal!!\t";

					//Через связь надо получить доступ к строке.
					cout << figure.get_is_link().pl_->get_right_ptr()->get_data() << endl;

					break;//Как только совпадение найдено, завершаем проверку.
				}
				//else//Образы не совпадают.
				//{
				//	cout << "No match!\n" << (im.get_non_link().ps->get_data()) << endl;//Выводим сообщение об этом и специфическое для эталонного образа сообщение.
				//}
				//cout << endl;
			}
		}//if (match == false)//Образы не совпали ни с одним эталоном.

		//Движение фигуры в зависимости от стадии цикла записи.
		figure_moving(*fig, i);

		//Устанавливаем новое положение формы на экране.
		pos = fig->where();
		shape->setPosition(pos.x_*Scale, pos.y_*Scale);


	//УЧАСТОК ПОДГОТОВКИ К СЛЕДУЮЩЕМУ ЦИКЛУ СОЗНАНИЯ ///////////////////////////////////////////////////////////////////////////////

		//Очищаем список предупреждений, чтобы заполнить его в следующем цикле.
		warnings.clear();

	}//for (size_t i = 0; window.isOpen() && i < Frames; i++)//Цикл записи.


//УЧАСТОК ЗАПИСИ ДАННЫХ В ФАЙЛЫ ПЕРЕД ЗАВЕРШЕНИЕМ ПРОГРАММЫ //////////////////////////////////////////////////////////////////
	
	
	//Функция выполняет всю работу.
	database_recording(	"Figures\\figures_data.bin",	"Links\\links_data.bin",	"Strings\\strings_data.bin", 
						image_map,						link_map,					string_map);

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


//Создание отрисовываемой формы на основе типа фигуры. Вынесено в отдельную функцию, чтобы не засорять классы зависимостью от графической библиотеки.
unique_ptr<sf::Shape> get_visible_shape(const Figure* fig, float scale)
{
	if (const Square* sq = dynamic_cast<const Square*>(fig))
	{
		size_t side = sq->get_side_length();
		return unique_ptr<sf::Shape>(new sf::RectangleShape(sf::Vector2f(side*scale, side*scale)));
	}

	if (const My::Rectangle* rc = dynamic_cast<const My::Rectangle*>(fig))
	{
		size_t side = rc->get_side_length();
		return unique_ptr<sf::Shape>(new sf::RectangleShape(sf::Vector2f(side*1.6*scale, side*scale)));
	}

	if (const Circle* ccl = dynamic_cast<const Circle*>(fig))
	{
		size_t rad = ccl->get_radius();
		return unique_ptr<sf::Shape>(new sf::CircleShape(rad*scale));
	}

	if (const Rhomb* rb = dynamic_cast<const Rhomb*>(fig))
	{
		size_t diag = rb->get_diagonal();
		return unique_ptr<sf::Shape>(new sf::CircleShape(diag / 2*scale, 4));
	}

	if (const Triangle* tr = dynamic_cast<const Triangle*>(fig))
	{
		size_t cat = tr->get_cathetus();

		sf::ConvexShape triangle(3);
		triangle.setPoint(0, sf::Vector2f(0, 0));
		triangle.setPoint(1, sf::Vector2f(0, cat*scale));
		triangle.setPoint(2, sf::Vector2f(cat*scale, cat*scale));

		return unique_ptr<sf::Shape> (new sf::ConvexShape(triangle)); 
	}

	return nullptr;
}

//Вывести меню выбора типа фигуры.
void display_menu()
{
	cout << "Enter type of figure:\n"
		 << "a) square\t b) rectangle\t c) circle\n"
		 << "d) rhomb\t e) triangle\n";
}

//Обработка цифрового ввода.
size_t only_digits_input()
{
	size_t ln;
	
	while (!(cin>>ln))
	{
		cout << "Only digits!\n";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	
	return ln;
}

//Функция для выбора типа создаваемой фигуры.
unique_ptr<Figure> select_figure()
{
	display_menu();
	char ch;
	while(cin >> ch)
	{
		switch (ch)
		{
		case 'a':
			cout << "Enter side length: ";
			size_t len;
			len = only_digits_input();
			
			return unique_ptr<Figure> { new Square{ 20, 3, len } };
			
		case 'b':
			cout << "Enter side length: ";
			size_t len1;
			len1 = only_digits_input();

			return unique_ptr<Figure> { new My::Rectangle{ 20, 3, len1 }};
			
		case 'c':
			cout << "Enter radius: ";
			size_t rad;
			rad = only_digits_input();

			return unique_ptr<Figure> { new Circle{ 20, 3, rad }};
			

		case 'd':
			cout << "Enter diagonal: ";
			size_t diag;
			diag = only_digits_input();

			return unique_ptr<Figure> { new Rhomb{ 20, 3, diag }};
			
		case 'e':
			cout << "Enter cathetus: ";
			size_t cat;
			cat = only_digits_input();

			return unique_ptr<Figure> { new Triangle{ 20, 3, cat }};

		default:
			cout << "Wrong letter!\n";
			cin.ignore(1000, '\n');
			display_menu();
			break;
		}
	}
	return nullptr;
}
