#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <random>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include "snake.hpp"
#include "game.hpp"
#include "base/base.hpp"
#include "SnakeGame.hpp"
#define LV_MAX 7			//
#define WIDTH 40			//game width
#define HEIGHT 24			//game height
#define SCORE_FOOD 20		//eat a food score
#define LV_UP 66	


static const int DEFAULT_SLEEP_TIME = 400;
static void create_map();
SnakeGame::SnakeGame()
{
	system("title esurient 1.0(for c++)");
	system("cls");
	HideCursor();
	s = nullptr;
}
SnakeGame::~SnakeGame()
{
	system("cls");
	delete s;
}
void SnakeGame::play()
{
	create_map();
	level = 1;
	score = 0;
	gotoxy(35, 11, color::RED);
	std::cout << level;
	gotoxy(34, 15, color::RED);
	std::cout << std::right << std::setw(5) << score;
	if (!start())
	{
		system("cls");
		return;
	}
	std::size_t sleep_time = DEFAULT_SLEEP_TIME - (level-1)*50;
	s = new snake(15,15);
	create_food();
	while (true)
	{
		if (_kbhit())
		{
			change_stat(get_key());
			while(_kbhit())
			 	_getch();
		}
		if (level == LV_MAX + 1)
		{
			gotoxy(10, 10, color::RED);
			std::cout << "congratulation pase";
			if (!exit_game())
				init_data();
			else
				return;
		}
		move_snake();
		Sleep(sleep_time);
		if (is_dead())
		{
			gotoxy(10, 10, color::RED);
			std::cout << "You are dead";
			if (exit_game())
				return;
			else
				init_data();
		}
	}
}

void SnakeGame::change_stat(int key){
	switch(key){
		case UP:
			s->change_direction(direction::UP);
			break;
		case DOWN:
			s->change_direction(direction::DOWN);
			break;
		case LEFT:
			s->change_direction(direction::LEFT);
			break;
		case RIGHT:
			s->change_direction(direction::RIGHT);
			break;
		case ESC:
			exit_game();
			break;
		case SPACE:
			_getch();
	}
}

bool SnakeGame::start()
{
	int ch;
	gotoxy(10, 10, color::BLUE);
	std::cout << "                       ";
	gotoxy(10, 11, color::BLUE);
	std::cout << "Enter start game ESC exit";
	gotoxy(10, 12, color::BLUE);
	std::cout << "¡ûLv Up Lv Down ¡ú";
	gotoxy(35, 11, color::RED);
	std::cout << level;
	gotoxy(34, 15, color::RED);
	std::cout << std::right << std::setw(5) << score;
	while ((ch = get_key()) != ENTER && ch != ESC)
	{
		if (ch == LEFT)
		{
			--level;
			if (level < 1)
				level = LV_MAX;
		}
		else if (ch == RIGHT)
		{
			++level;
			if (level > LV_MAX)
				level = 1;
		}
		gotoxy(35, 11, color::RED);
		std::cout << level;
	}
	if (ch == ESC)
	{
		return false;
	}
	gotoxy(10, 11, color::BLUE);
	std::cout << "                                  ";
	gotoxy(10, 12, color::BLUE);
	std::cout << "                                   ";
	return true;
}

void create_map(void)
{
	int w;	//weight
	int h; //height
	//first line
	for (w = 0; w < WIDTH; w++)
	{
		gotoxy(w, 0, color::BLUE);
		std::cout << "¡ö";
	}
	//map center
	for (h = 1; h < HEIGHT - 1; h++)
	{
		gotoxy(0, h, color::BLUE);
		std::cout << "¡ö";
		gotoxy(31, h, color::BLUE);
		std::cout << "¡ö";
		gotoxy(WIDTH - 1, h, color::BLUE);
		std::cout << "¡ö";
	}
	//bottom
	for (w = 0; w < WIDTH; w++)
	{
		gotoxy(w, HEIGHT - 1, color::BLUE);
		std::cout << "¡ö";
	}
	gotoxy(34, 2, color::GREEN);
	std::cout << "esurient";
	gotoxy(35, 3, color::GREEN);
	std::cout << "by sora";
	gotoxy(34, 5, color::GREEN);
	std::cout << "operation";
	gotoxy(33, 7, color::GREEN);
	std::cout << "¡û ¡ü ¡ý ¡ú";
	gotoxy(34, 10, color::GREEN);
	std::cout << "level";
	gotoxy(34, 13, color::GREEN);
	std::cout << "score";
	gotoxy(33, 16, color::GREEN);
	std::cout << "eat foods";
	gotoxy(33, 19, color::GREEN);
	std::cout << "space pause";
	gotoxy(33, 21, color::GREEN);
	std::cout << "anykey run";
}

void SnakeGame::create_food(void)
{
	std::default_random_engine ex;
	std::default_random_engine ey;
	ex.seed(std::time(0));
	ey.seed(std::time(0));
	do
	{
		int x = 1 + ex() % (WIDTH - 12);
		int y = 1 + ey() % (HEIGHT - 2);
		food_position = postion(x,y);
	} while (s->on_snake(food_position));
	
	//disply food
	gotoxy(food_position.get_x(), food_position.get_y(), color::RED);
	std::cout << "¡ñ";
}

void SnakeGame::move_snake()
{
	postion next = s->next();
	if(next == food_position)
	{
		s->eat_food();
		create_food();
		++eat_food_count;
		score += SCORE_FOOD;
		if(eat_food_count > 0 && eat_food_count%LV_UP == 0){
			++level;
		}

	}
	s->move();
	gotoxy(35, 11, color::RED);
	std::cout << level;
	gotoxy(34, 15, color::RED);
	std::cout << std::right << std::setw(5) << score;
	gotoxy(34, 17, color::RED);
	std::cout << std::right << std::setw(4) << score / SCORE_FOOD;
}
bool SnakeGame::is_dead()
{
	postion head = s->head();
	if(s->is_eatself()){
		return true;
	}

	if (head.get_x() == 0 || head.get_y()  == 0 || 
		head.get_x() == WIDTH - 9 || head.get_y() == HEIGHT - 1)
	{
		gotoxy(head.get_x(), head.get_y(), color::BLUE);
		std::cout << "¡ö";
		return true;
	}
	return false;
}

void SnakeGame::init_data()
{
	system("cls");
	delete s;
	play();
}
bool SnakeGame::exit_game()
{
	gotoxy(2, HEIGHT, color::RED);
	std::cout << "ÍË³ö?";
	
	while(true)
	{
		switch(get_key())
		{
			case static_cast<int>(ENTER): return true;
			break;
			case static_cast<int>(ESC)  : return false;
				gotoxy(2, HEIGHT, color::RED);
				std::cout << "           ";
		}
	}
}