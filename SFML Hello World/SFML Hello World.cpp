// SFML Hello World.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <SFML/Graphics.hpp>


int main()
{
	

	//Создание окна
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
	window.setPosition(sf::Vector2i(50, 50));

	//Включение вертикальной синхронизации.
	window.setVerticalSyncEnabled(true);

	sf::CircleShape shape(200.f, 50);
	shape.setPosition(20.f, 20.f);
	shape.setFillColor(sf::Color::White);
	
	
	// define a 120x50 rectangle
	sf::RectangleShape rectangle(sf::Vector2f(220.f, 150.f));
	rectangle.setFillColor(sf::Color::Red);
	rectangle.setPosition(400, 400);
	


	sf::Clock clock;//Стартует счетчик времени.

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			

			

			

			
		}

		sf::Time elapsed1 = clock.restart();//Получаем прошедшее время. Обнуляем счетчик.
		std::cout << elapsed1.asMicroseconds() << std::endl;
		
		

		window.clear(sf::Color::Black);
		window.draw(shape);
		window.draw(rectangle);
		window.display();

		
	}

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
