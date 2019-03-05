#include "pch.h"
#include "Inspector.h"


const Borders Inspector::left_inspect(const Inner_frame & ws, bool clockwise)
{
	set<int> xset, yset; //Списки координат, пройденных инспектором.

	bool is_finished = false; //Переменная, сообщающая о том, завершен ли обход.
	bool is_started = false; //Переменная, сообщающая о том, начат ли обход.

	int start_x, start_y; //Переменные для хранения координат начала поиска.


	while (!is_finished)//Пока обход не закончен.
	{

		//Если все эл-ты вокруг инспектора принадлежат объекту, то сдвигаем его влево.
		if (ws[loc_.y_ - 1][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_] == obj_ && ws[loc_.y_ - 1][loc_.x_ + 1] == obj_ && ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_] == obj_
			&& ws[loc_.y_ + 1][loc_.x_ - 1] == obj_ && ws[loc_.y_][loc_.x_ - 1] == obj_)
		{
			//cout << " moveLeft... " << loc_.x_ << " " << loc_.y_;
			moveLeft();
			//continue;
		}
		else
		if (ws[loc_.y_ + 1][loc_.x_ - 1] == bg_ && ws[loc_.y_][loc_.x_ - 1] == bg_ && ws[loc_.y_ - 1][loc_.x_ - 1] == bg_ //Граница слева
				&& ws[loc_.y_ - 1][loc_.x_] == obj_ && ws[loc_.y_ - 1][loc_.x_ + 1] == obj_ && ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_] == obj_)
		{

			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);//Заносим координаты в списки.
			yset.insert(loc_.y_);

			(clockwise) ? moveUp() : moveDown();
				//continue;
		}
		else
		if (ws[loc_.y_ + 1][loc_.x_ - 1] == bg_ && ws[loc_.y_][loc_.x_ - 1] == bg_ && ws[loc_.y_ - 1][loc_.x_ - 1] == bg_ && ws[loc_.y_ - 1][loc_.x_] == bg_ && ws[loc_.y_ - 1][loc_.x_ + 1] == bg_
					&& ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_] == obj_)//В верхнем левом углу.
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

				(clockwise) ? moveRight() : moveDown();
					//continue;
		}
		else
		if (ws[loc_.y_ - 1][loc_.x_ - 1] == bg_ && ws[loc_.y_ - 1][loc_.x_] == bg_ && ws[loc_.y_ - 1][loc_.x_ + 1] == bg_ //Граница сверху.
				&& ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_] == obj_ && ws[loc_.y_ + 1][loc_.x_ - 1] == obj_ && ws[loc_.y_][loc_.x_ - 1] == obj_)
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveRight() : moveLeft();
				//continue;
		}
		else
		if (ws[loc_.y_ - 1][loc_.x_ - 1] == bg_ && ws[loc_.y_ - 1][loc_.x_] == bg_ && ws[loc_.y_ - 1][loc_.x_ + 1] == bg_ && ws[loc_.y_][loc_.x_ + 1] == bg_ && ws[loc_.y_ + 1][loc_.x_ + 1] == bg_
				&& ws[loc_.y_ + 1][loc_.x_] == obj_ && ws[loc_.y_ + 1][loc_.x_ - 1] == obj_ && ws[loc_.y_][loc_.x_ - 1] == obj_)//В верхнем правом углу.
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveDown() : moveLeft();
				//continue;
		}
		else
		if (ws[loc_.y_ - 1][loc_.x_ + 1] == bg_ && ws[loc_.y_][loc_.x_ + 1] == bg_ && ws[loc_.y_ + 1][loc_.x_ + 1] == bg_ //Граница справа
				&& ws[loc_.y_ + 1][loc_.x_] == obj_ && ws[loc_.y_ + 1][loc_.x_ - 1] == obj_ && ws[loc_.y_][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_] == obj_)
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveDown() : moveUp();
				//continue;
		}
		else
		if (ws[loc_.y_ - 1][loc_.x_ + 1] == bg_ && ws[loc_.y_][loc_.x_ + 1] == bg_ && ws[loc_.y_ + 1][loc_.x_ + 1] == bg_ && ws[loc_.y_ + 1][loc_.x_] == bg_ && ws[loc_.y_ + 1][loc_.x_ - 1] == bg_
				&& ws[loc_.y_][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_] == obj_)//В нижнем правом углу.
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveLeft() : moveUp();
				//continue;
		}
		else
		if (ws[loc_.y_ + 1][loc_.x_ + 1] == bg_ && ws[loc_.y_ + 1][loc_.x_] == bg_ && ws[loc_.y_ + 1][loc_.x_ - 1] == bg_ //Граница снизу.
				&& ws[loc_.y_][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_] == obj_ && ws[loc_.y_ - 1][loc_.x_ + 1] == obj_ && ws[loc_.y_][loc_.x_ + 1] == obj_)
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveLeft() : moveRight();
				//continue;
		}
		else
		if (ws[loc_.y_ + 1][loc_.x_ + 1] == bg_ && ws[loc_.y_ + 1][loc_.x_] == bg_ && ws[loc_.y_ + 1][loc_.x_ - 1] == bg_ && ws[loc_.y_][loc_.x_ - 1] == bg_ && ws[loc_.y_ - 1][loc_.x_ - 1] == bg_
				&& ws[loc_.y_ - 1][loc_.x_] == obj_ && ws[loc_.y_ - 1][loc_.x_ + 1] == obj_ && ws[loc_.y_][loc_.x_ + 1] == obj_)//В нижнем левом углу.
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveUp() : moveRight();
				//continue;
		}
		else
		if (ws[loc_.y_ + 1][loc_.x_ - 1] == bg_ && ws[loc_.y_][loc_.x_ - 1] == bg_
				&& ws[loc_.y_ - 1][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_] == obj_ && ws[loc_.y_ - 1][loc_.x_ + 1] == obj_ && ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_] == obj_)
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveUp() : moveDown();
				//continue;
		}
		else
		if (ws[loc_.y_ + 1][loc_.x_ - 1] == bg_ && ws[loc_.y_ - 1][loc_.x_ - 1] == bg_
				&& ws[loc_.y_][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_] == obj_ && ws[loc_.y_ - 1][loc_.x_ + 1] == obj_ && ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_] == obj_)
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_ - 1);
			yset.insert(loc_.y_);

			(clockwise) ? moveUp() : moveDown();
				//continue;
		}
		else
		if (ws[loc_.y_][loc_.x_ - 1] == bg_ && ws[loc_.y_ - 1][loc_.x_ - 1] == bg_
				&& ws[loc_.y_ - 1][loc_.x_] == obj_ && ws[loc_.y_ - 1][loc_.x_ + 1] == obj_ && ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_] == obj_ && ws[loc_.y_ + 1][loc_.x_ - 1] == obj_)
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveUp() : moveDown();
				//continue;
		}
		else
		if (ws[loc_.y_ + 1][loc_.x_ - 1] == bg_ && ws[loc_.y_][loc_.x_ - 1] == bg_ && ws[loc_.y_ - 1][loc_.x_ - 1] == bg_ && ws[loc_.y_ - 1][loc_.x_] == bg_
				&& ws[loc_.y_ - 1][loc_.x_ + 1] == obj_ && ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_] == obj_)
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveRight() : moveDown();
				//continue;
		}
		else
		if (ws[loc_.y_ - 1][loc_.x_ - 1] == bg_
				&& ws[loc_.y_ - 1][loc_.x_] == obj_ && ws[loc_.y_ - 1][loc_.x_ + 1] == obj_ && ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_] == obj_
				&& ws[loc_.y_ + 1][loc_.x_ - 1] == obj_ && ws[loc_.y_][loc_.x_ - 1] == obj_)
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveUp() : moveLeft();
				//continue;
		}
		else
		if (ws[loc_.y_][loc_.x_ - 1] == bg_ && ws[loc_.y_ - 1][loc_.x_ - 1] == bg_ && ws[loc_.y_ - 1][loc_.x_] == bg_ && ws[loc_.y_ - 1][loc_.x_ + 1] == bg_
				&& ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_] == obj_ && ws[loc_.y_ + 1][loc_.x_ - 1] == obj_)
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveRight() : moveDown();
				//continue;
		}
		else
		if (ws[loc_.y_ - 1][loc_.x_ - 1] == bg_ && ws[loc_.y_ - 1][loc_.x_] == bg_
				&& ws[loc_.y_ - 1][loc_.x_ + 1] == obj_ && ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_] == obj_ && ws[loc_.y_ + 1][loc_.x_ - 1] == obj_ && ws[loc_.y_][loc_.x_ - 1] == obj_)
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveRight() : moveLeft();
				//continue;
		}
		else
		if (ws[loc_.y_ - 1][loc_.x_ - 1] == bg_ && ws[loc_.y_ - 1][loc_.x_] == obj_ && ws[loc_.y_ - 1][loc_.x_ + 1] == bg_
				&& ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_] == obj_ && ws[loc_.y_ + 1][loc_.x_ - 1] == obj_ && ws[loc_.y_][loc_.x_ - 1])
		{
			//cout << "pos 8, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_ - 1);

			(clockwise) ? moveRight() : moveLeft();
				//continue;
		}
		else
		if (ws[loc_.y_ - 1][loc_.x_] == bg_ && ws[loc_.y_ - 1][loc_.x_ + 1] == bg_
				&& ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_] == obj_ && ws[loc_.y_ + 1][loc_.x_ - 1] == obj_ && ws[loc_.y_][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_ - 1] == obj_)
		{
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveRight() : moveLeft();
				//continue;
		}
		else
		if (ws[loc_.y_ - 1][loc_.x_ - 1] == bg_ && ws[loc_.y_ - 1][loc_.x_] == bg_ && ws[loc_.y_ - 1][loc_.x_ + 1] == bg_ && ws[loc_.y_][loc_.x_ + 1] == bg_
				&& ws[loc_.y_ + 1][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_] == obj_ && ws[loc_.y_ + 1][loc_.x_ - 1] == obj_ && ws[loc_.y_][loc_.x_ - 1] == obj_)
		{
			//cout << "pos 10, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveDown() : moveLeft();
				//continue;
		}
		else
		if (ws[loc_.y_ - 1][loc_.x_ + 1] == bg_
				&& ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_] == obj_ && ws[loc_.y_ + 1][loc_.x_ - 1] == obj_ && ws[loc_.y_][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_ - 1] == obj_
				&& ws[loc_.y_ - 1][loc_.x_] == obj_)
		{
			//cout << "pos 11, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveRight() : moveUp();
				//continue;
		}
		else
		if (ws[loc_.y_ - 1][loc_.x_] == bg_ && ws[loc_.y_ - 1][loc_.x_ + 1] == bg_ && ws[loc_.y_][loc_.x_ + 1] == bg_ && ws[loc_.y_ + 1][loc_.x_ + 1] == bg_
				&& ws[loc_.y_ + 1][loc_.x_] == obj_ && ws[loc_.y_ + 1][loc_.x_ - 1] == obj_ && ws[loc_.y_][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_ - 1] == obj_)
		{
			//cout << "pos 12, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveDown() : moveLeft();
				//continue;
		}
		else
		if (ws[loc_.y_ - 1][loc_.x_ + 1] == bg_ && ws[loc_.y_][loc_.x_ + 1] == bg_
				&& ws[loc_.y_ + 1][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_] == obj_ && ws[loc_.y_ + 1][loc_.x_ - 1] == obj_ && ws[loc_.y_][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_] == obj_)
		{
			//cout << "pos 13, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveDown() : moveUp();
				//continue;
		}
		else
		if (ws[loc_.y_ - 1][loc_.x_ + 1] == bg_ && ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_ + 1] == bg_
				&& ws[loc_.y_ + 1][loc_.x_] == obj_ && ws[loc_.y_ + 1][loc_.x_ - 1] == obj_ && ws[loc_.y_][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_] == obj_)
		{
			//cout << "pos 14, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_ + 1);
			yset.insert(loc_.y_);

			(clockwise) ? moveDown() : moveUp();
				//continue;
		}
		else
		if (ws[loc_.y_][loc_.x_ + 1] == bg_ && ws[loc_.y_ + 1][loc_.x_ + 1] == bg_
				&& ws[loc_.y_ + 1][loc_.x_] == obj_ && ws[loc_.y_ + 1][loc_.x_ - 1] == obj_ && ws[loc_.y_][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_] == obj_ && ws[loc_.y_ - 1][loc_.x_ + 1] == obj_)
		{
			//cout << "pos 15, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveDown() : moveUp();
				//continue;
		}
		else
		if (ws[loc_.y_ - 1][loc_.x_ + 1] == bg_ && ws[loc_.y_][loc_.x_ + 1] == bg_ && ws[loc_.y_ + 1][loc_.x_ + 1] == bg_ && ws[loc_.y_ + 1][loc_.x_] == bg_
				&& ws[loc_.y_ + 1][loc_.x_ - 1] == obj_ && ws[loc_.y_][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_] == obj_)
		{
			//cout << "pos 16, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveLeft() : moveUp();
				//continue;
		}
		else
		if (ws[loc_.y_ + 1][loc_.x_ + 1] == bg_
				&& ws[loc_.y_ + 1][loc_.x_] == obj_ && ws[loc_.y_ + 1][loc_.x_ - 1] == obj_ && ws[loc_.y_][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_] == obj_ && ws[loc_.y_ - 1][loc_.x_ + 1] == obj_
				&& ws[loc_.y_][loc_.x_ + 1] == obj_)
		{
			//cout << "pos 17, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveDown() : moveRight();
				//continue;
		}

		else
		if (ws[loc_.y_][loc_.x_ + 1] == bg_ && ws[loc_.y_ + 1][loc_.x_ + 1] == bg_ && ws[loc_.y_ + 1][loc_.x_] == bg_ && ws[loc_.y_ + 1][loc_.x_ - 1] == bg_
				&& ws[loc_.y_][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_] == obj_ && ws[loc_.y_ - 1][loc_.x_ + 1] == obj_)
		{
			//cout << "pos 18, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveLeft() : moveUp();
				//continue;
		}
		else
		if (ws[loc_.y_ + 1][loc_.x_ + 1] == bg_ && ws[loc_.y_ + 1][loc_.x_] == bg_
				&& ws[loc_.y_ + 1][loc_.x_ - 1] == obj_ && ws[loc_.y_][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_] == obj_ && ws[loc_.y_ - 1][loc_.x_ + 1] == obj_ && ws[loc_.y_][loc_.x_ + 1] == obj_)
		{
			//cout << "pos 19, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveLeft() : moveRight();
				//continue;
		}
		else
		if (ws[loc_.y_ + 1][loc_.x_ + 1] == bg_ && ws[loc_.y_ + 1][loc_.x_] == obj_ && ws[loc_.y_ + 1][loc_.x_ - 1] == bg_
				&& ws[loc_.y_][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_] == obj_ && ws[loc_.y_ - 1][loc_.x_ + 1] == obj_ && ws[loc_.y_][loc_.x_ + 1] == obj_)
		{
			//cout << "pos 20, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_ + 1);

			(clockwise) ? moveLeft() : moveRight();
				//continue;
		}
		else
		if (ws[loc_.y_ + 1][loc_.x_] == bg_ && ws[loc_.y_ + 1][loc_.x_ - 1] == bg_
				&& ws[loc_.y_][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_] == obj_ && ws[loc_.y_ - 1][loc_.x_ + 1] == obj_ && ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_ + 1] == obj_)
		{
			//cout << "pos 21, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveLeft() : moveRight();
				//continue;
		}
		else
		if (ws[loc_.y_ + 1][loc_.x_ + 1] == bg_ && ws[loc_.y_ + 1][loc_.x_] == bg_ && ws[loc_.y_ + 1][loc_.x_ - 1] == bg_ && ws[loc_.y_][loc_.x_ - 1] == bg_
				&& ws[loc_.y_ - 1][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_] == obj_ && ws[loc_.y_ - 1][loc_.x_ + 1] == obj_ && ws[loc_.y_][loc_.x_ + 1] == obj_)
		{
			//cout << "pos 22, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveUp() : moveRight();
				//continue;
		}
		else
		if (ws[loc_.y_ + 1][loc_.x_ - 1] == bg_
				&& ws[loc_.y_][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_] == obj_ && ws[loc_.y_ - 1][loc_.x_ + 1] == obj_ && ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_ + 1] == obj_
				&& ws[loc_.y_ + 1][loc_.x_] == obj_)
		{
			//cout << "pos 23 ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveLeft() : moveDown();
				//continue;
		}
		else
		if (ws[loc_.y_ + 1][loc_.x_] == bg_ && ws[loc_.y_ + 1][loc_.x_ - 1] == bg_ && ws[loc_.y_][loc_.x_ - 1] == bg_ && ws[loc_.y_ - 1][loc_.x_ - 1] == bg_
				&& ws[loc_.y_ - 1][loc_.x_] == obj_ && ws[loc_.y_ - 1][loc_.x_ + 1] == obj_ && ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_ + 1] == obj_)
		{
			//cout << "pos 24, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveUp() : moveRight();
				//continue;
		}
		else
		if (ws[loc_.y_][loc_.x_ - 1] == bg_ && ws[loc_.y_ - 1][loc_.x_ - 1] == bg_ && ws[loc_.y_ - 1][loc_.x_] == bg_
				&& ws[loc_.y_ - 1][loc_.x_ + 1] == obj_ && ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_] == obj_ && ws[loc_.y_ + 1][loc_.x_ - 1] == obj_)
		{
			//cout << "pos 25, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveRight() : moveDown();
				//continue;
		}
		else
		if (ws[loc_.y_ - 1][loc_.x_] == bg_ && ws[loc_.y_ - 1][loc_.x_ + 1] == bg_ && ws[loc_.y_][loc_.x_ + 1] == bg_
				&& ws[loc_.y_ + 1][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_] == obj_ && ws[loc_.y_ + 1][loc_.x_ - 1] == obj_ && ws[loc_.y_][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_ - 1] == obj_)
		{
			//cout << "pos 26, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveDown() : moveLeft();
				//continue;
		}
		else
		if (ws[loc_.y_][loc_.x_ + 1] == bg_ && ws[loc_.y_ + 1][loc_.x_ + 1] == bg_ && ws[loc_.y_ + 1][loc_.x_] == bg_
				&& ws[loc_.y_ + 1][loc_.x_ - 1] == obj_ && ws[loc_.y_][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_] == obj_ && ws[loc_.y_ - 1][loc_.x_ + 1] == obj_)
		{
			//cout << "pos 27, ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveLeft() : moveUp();
				//continue;
		}
		else
		if (ws[loc_.y_ + 1][loc_.x_] == bg_ && ws[loc_.y_ + 1][loc_.x_ - 1] == bg_ && ws[loc_.y_][loc_.x_ - 1] == bg_
				&& ws[loc_.y_ - 1][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_] == obj_ && ws[loc_.y_ - 1][loc_.x_ + 1] == obj_ && ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_ + 1] == obj_)
		{
			//cout << "pos 28.";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveUp() : moveRight();
				//continue;
		}
		else
		if (ws[loc_.y_][loc_.x_ - 1] == bg_ && ws[loc_.y_ - 1][loc_.x_ - 1] == bg_ && ws[loc_.y_ - 1][loc_.x_] == bg_ && ws[loc_.y_ - 1][loc_.x_ + 1] == bg_ && ws[loc_.y_][loc_.x_ + 1] == bg_
				&& ws[loc_.y_ + 1][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_] == obj_ && ws[loc_.y_ + 1][loc_.x_ - 1] == obj_)
		{
			//cout << "pos 29 ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			start_y = loc_.y_ + 1;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_);

			(clockwise) ? moveDown() : moveDown();
				//continue;
		}
		else
		if (ws[loc_.y_ - 1][loc_.x_ + 1] == bg_ && ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_ + 1] == bg_ && ws[loc_.y_ + 1][loc_.x_] == bg_ && ws[loc_.y_ + 1][loc_.x_ - 1] == bg_
				&& ws[loc_.y_][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_] == obj_)
		{
			//cout << "pos 30 ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_ + 1);
			yset.insert(loc_.y_);

			(clockwise) ? moveLeft() : moveUp();
				//continue;
		}
		else
		if (ws[loc_.y_ + 1][loc_.x_ - 1] == bg_ && ws[loc_.y_][loc_.x_ - 1] == bg_ && ws[loc_.y_ - 1][loc_.x_ - 1] == bg_ && ws[loc_.y_ - 1][loc_.x_] == obj_ && ws[loc_.y_ - 1][loc_.x_ + 1] == bg_
				&& ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_] == obj_)
		{
			//cout << "pos 31 ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_);
			yset.insert(loc_.y_ - 1);

			(clockwise) ? moveRight() : moveDown();
				//continue;
		}
		else
		if (ws[loc_.y_ + 1][loc_.x_ + 1] == bg_ && ws[loc_.y_ + 1][loc_.x_] == bg_ && ws[loc_.y_ + 1][loc_.x_ - 1] == bg_ && ws[loc_.y_][loc_.x_ - 1] == obj_ && ws[loc_.y_ - 1][loc_.x_ - 1] == bg_
				&& ws[loc_.y_ - 1][loc_.x_] == obj_ && ws[loc_.y_ - 1][loc_.x_ + 1] == obj_ && ws[loc_.y_][loc_.x_ + 1] == obj_)
		{
			//cout << "pos 32 ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_ - 1);
			yset.insert(loc_.y_);

			(clockwise) ? moveUp() : moveRight();
				//continue;
		}
		else
		if (ws[loc_.y_ - 1][loc_.x_ - 1] == bg_ && ws[loc_.y_ - 1][loc_.x_] == obj_ && ws[loc_.y_ - 1][loc_.x_ + 1] == bg_ && ws[loc_.y_][loc_.x_ + 1] == obj_ && ws[loc_.y_ + 1][loc_.x_ + 1] == bg_ && ws[loc_.y_ + 1][loc_.x_] == obj_
				&& ws[loc_.y_ + 1][loc_.x_ - 1] == bg_ && ws[loc_.y_][loc_.x_ - 1] == obj_)
		{
			//cout << "pos 33 ";
			if (start_stop(is_started, is_finished, start_x, start_y))
				continue;

			xset.insert(loc_.x_ - 1), xset.insert(loc_.x_), xset.insert(loc_.x_ + 1);
			yset.insert(loc_.y_ - 1), yset.insert(loc_.y_), yset.insert(loc_.y_ + 1);
				//continue;
		}
																																									
																																										
	}//while (!is_finished)//Пока обход не закончен.

	//Возвращаем сконструированную на месте стр-ру, содержащую наименьшие и наибольшие координаты, пройденные инспектором.
	return { *xset.begin(), *xset.rbegin(), *yset.begin(), *yset.rbegin() }; 																		
}


//Функция определит, когда пора завершать обход.
int Inspector::start_stop(bool & is_started, bool & is_finished, int & start_x, int & start_y)
{
	if (is_started == true && loc_.x_ == start_x && loc_.y_ == start_y)	// Если обход начат ранее, и координаты инспектора равны координатам старта обхода, то значит он 
																	// сделал круг, и обход можно считать завершенным.
	{
		is_finished = true;
		return 1;
	}
	if (is_started == false)	//Если обход еще не стартовал,
	{
		is_started	= true;		// то объявляем старт
		start_x		= loc_.x_;	// и запоминаем координаты старта.
		start_y		= loc_.y_;
		
	}
	
	return 0;
}


