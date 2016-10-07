#ifndef _SNAKE_BASE_HPP
#define _SNAKE_BASE_HPP

class postion{
private:
	int x;
	int y;
public:
	postion():x(0),y(0){}
	postion(int xx, int yy):x(xx), y(yy){};
	int get_x() const {return x; }
	int get_y() const {return y; }
	bool operator!=(const postion& rhs){
		return this->x != rhs.x || this->y != rhs.y;
	}
	bool operator==(const postion& rhs){
		return this->x == rhs.x && this->y == rhs.y;
	}
};

enum class direction{RIGHT, UP, DOWN, LEFT};

#endif