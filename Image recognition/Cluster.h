#pragma once
#include "Warning.h"


using namespace My_names;

struct Cluster
{
	int xC = 0, yC = 0;//Координаты левого верхнего края кластера.
	int s = 5; //Длина стороны квадратного кластера.
	int count = 0;  //Количество точек, признанных отличными от фона.

	//ÊÎÍÑÒÐÓÊÒÎÐÛ

	//Çàäàåò ÷ëåíû. Count çàäàåòñÿ íåÿâíî ïî óìîë÷àíèþ íóëåì.
	Cluster(int x=0, int y=0, int s1=5) :xC(x), yC(y), s(s1) {}


	//Âîçâðàùàåò ðàçìåð êëàñòåðà.
	int size() { return s * s; } 

	//Ôóíêöèÿ ïîäñ÷èòûâàåò êîëè÷åñòâî òî÷åê â êëàñòåðå, ñîäåðæàùèõ îòëè÷íîå îò ôîíà çíà÷åíèå.
	template<size_t W, size_t H>  void counter(array<array<char, W>, H> &ws, char background);

	//Ôóíêöèÿ âûâîäèò çíà÷åíèÿ ÷ëåíîâ.
	void print() const { cout << xC << ", " << yC << ", " << count << endl; }

	//Çàäàòü íîâûå êîîðäèíàòû è ñáðîñèòü ñ÷åò÷èê.
	void assign(int x, int y) { xC = x; yC = y; count = 0; }
};

//Ôóíêöèÿ ïîäñ÷èòûâàåò êîëè÷åñòâî òî÷åê â êëàñòåðå, ñîäåðæàùèõ îòëè÷íîå îò ôîíà çíà÷åíèå.
template<size_t W, size_t H> 
void Cluster::counter(array<array<char, W>, H> &ws, char background)
{
	//cout << "Counting... " << endl;
	for (int y = yC; y != (yC + s); ++y)//Ïåðåáèðàåò âñå ýë-òû ðàáî÷åãî ïðîñòðàíñòâà â ãðàíèöàõ êâàäðàòíîãî êëàñòåðà.
	{
		for (int x = xC; x != (xC + s); ++x)
		{
			if (x >= 0 && x < W && y >= 0 && y < H)//Óñëîâèå, ïðåäîñòåðåãàþùåå îò âûõîäà çà ãðàíèöû ìàññèâà.
			{
				if (ws[y][x] != background)//Åñëè ýë-ò íå ðàâåí ôîíó,
				{
					++count;//òî óâåëè÷èâàåò ñ÷åò÷èê òàêèõ ýë-òîâ.
				}
			}
		}
	}
}


//Ïðîñòåéøàÿ ôóíêöèÿ óïðàâëåíèÿ âíèìàíèåì. Âûäàåò êîîðäèíàòû êëàñòåðà, â êîòîðîì áîëüøå âñåãî òî÷åê, îòëè÷íûõ îò ôîíà. Cluster.h.
template<size_t W, size_t H>
Warning most_filled_cluster(array<array<char, W>, H> &ws, char background)
{
	//Ñîçäàåì êëàñòåðû äëÿ ïîèñêà
	vector<Cluster> vc;

	for (int i = 0; i < H; i += 10)
	{
		for (int j = 0; j < W; j += 10)
		{
			vc.push_back(Cluster(j, i, 10));
		}
	}

	for (auto & e : vc)//Êàæäûé êëàñòåð ïîäñ÷èòûâàåò êîë-âî çíàêîâ, îòëè÷íûõ îò ôîíà.
	{
		e.counter(ws, background);
	}
	cout << "After cluster counting" << endl;

	//Íàéòè íàèáîëåå çàïîëíåííûé êëàñòåð.
	sort(vc.begin(), vc.end(), [](Cluster & c1, Cluster & c2) {return c1.count > c2.count; });

	//Âû÷èñëÿåì êîîðäèíàòû ñåðåäèíû êëàñòåðà.
	int x = vc[0].xC + vc[0].s / 2;
	int y = vc[0].yC + vc[0].s / 2;

	return Warning("Unidentified contrast object!", { x, y }, 10);
}
