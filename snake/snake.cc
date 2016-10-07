#include <iostream>
#include <algorithm>
#include "base.hpp"
#include "snake.hpp"
#include "game.hpp"

snake::snake(int xx, int yy){
	pos.push_front(postion(xx,yy));
	draw(pos.front());
	is_eat_food = false;
	dire = direction::RIGHT;
}
snake::snake(postion &p){
	pos.push_front(postion(p));
	draw(pos.front());
	is_eat_food = false;
	dire = direction::RIGHT;
}

void snake::eat_food(){
	is_eat_food=true;
	move();
}
void snake::move(){
	auto p = next();
	gotoxy(p.get_x(), p.get_y(),color::YELLO);
	std::cout << "¡ñ";
	draw(pos.front());
	pos.push_front(p);
	if(!is_eat_food){
		if(pos.front() != pos.back()){
			wipe(pos.back());
			pos.pop_back();
		}else{
			pos.pop_back();
		}
	}
	is_eat_food = false;
}

void snake::draw(const postion& p){
	gotoxy(p.get_x(), p.get_y(),color::WHITE);
	std::cout << "¡ö";
}

void snake::wipe(const postion& p){
	gotoxy(p.get_x(), p.get_y(),color::WHITE);
	std::cout << " ";
}

bool snake::is_eatself(){
	auto head = pos.begin();
	return find(++head,pos.end(), *head) != pos.end();
}

bool snake::on_snake(const postion& p){
	return find(pos.begin(), pos.end(), p) != pos.end();
}

postion snake::move_up(){
	auto &p = pos.front();
	return postion(p.get_x(), p.get_y() - 1);
}
postion snake::move_down(){
	auto &p = pos.front();
	return postion(p.get_x(), p.get_y() + 1);
}
postion snake::move_left(){
	auto &p = pos.front();
	return postion(p.get_x()-1, p.get_y());
}
postion snake::move_right(){
	auto &p = pos.front();
	return postion(p.get_x()+1, p.get_y());
}

postion snake::next(){
		switch(dire){
		case direction::UP:
			return move_up();
		case direction::DOWN:
			return move_down();
		case direction::LEFT:
			return move_left();
		case direction::RIGHT:
			return move_right();
	}
	throw int(1);
}

snake::~snake(){
	for(auto &p : pos)
		wipe(p);
}

void snake::change_direction(direction d){
	if(dire == direction::UP &&d != direction::DOWN)
		dire = d;
	if(dire == direction::DOWN && d != direction::UP)
		dire = d;
	if(dire == direction::LEFT && d != direction::RIGHT)
		dire = d;
	if(dire == direction::RIGHT && d != direction::LEFT)
		dire = d;
}
