#ifndef SNAKE_H
#define SNAKE_H
#include <list>
#include "base.hpp"

class snake
{
	direction dire;
	std::list<postion> pos;
	bool is_eat_food;
	postion move_up();
	postion move_down();
	postion move_left();
	postion move_right();
	void draw(const postion& p);
	void wipe(const postion& p);
public:
	snake() = delete;
	snake(int xx, int yy);
	snake(postion &p);
	~snake();
	void eat_food();
	bool is_eatself();
	bool on_snake(const postion& p);
	void move();
	void change_direction(direction d);
	postion head()const {return pos.front();}
	postion next();
};

#endif
