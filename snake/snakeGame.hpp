#ifndef SnakeGame_H
#define SnakeGame_H
#include <deque>
#include "snake.hpp"
#include "base.hpp"
/**
 *snake game class
 *
 *
 *
 *
 *
**/
class SnakeGame
{
	snake *s;
	postion food_position;
	int level;
	int score;
	int eat_food_count;
	direction direct;
	void move_snake();
	void create_food();
	void change_stat(int key);
	bool is_dead();
	bool start();
	void init_data();
	bool exit_game();

public:
	SnakeGame();
	SnakeGame(const SnakeGame&) = delete;
	~SnakeGame();
	void play();
};

#endif
