#include <iostream>
#include <windows.h>
#include <conio.h>
#include "snake.hpp"
#include "game.hpp"
#include "base.hpp"
#include "snakeGame.hpp"
static HANDLE hOut;
static COORD coordinate;

int get_key()
{
	char ch;
	ch = _getch();
	if (ch == ENTER || ch == ESC || ch == SPACE)
		return ch;
	else if (ch == -32)
		return _getch();
	else
		return 0;
}
void HideCursor(void)
{
	CONSOLE_CURSOR_INFO cur_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur_info);
}
void gotoxy(const int x, const int y, const color c)
{
	coordinate.X = 2 * x;
	coordinate.Y = y;
	hOut == NULL ?
		(hOut = GetStdHandle(STD_OUTPUT_HANDLE)) : hOut;
	SetConsoleCursorPosition(hOut, coordinate);
	SetConsoleTextAttribute(hOut, static_cast<int>(c));
}

int menu()
{
	int games = 8;
	int ch = 0;
	gotoxy(12, 8, color::RED);
	std::cout << "1.贪吃蛇";
	gotoxy(12, 9, color::RED);
	std::cout << "2.贪吃蛇AI";
	gotoxy(12, 10, color::RED);
	std::cout << "3.退出";
	gotoxy(11, 8, color::WHITE);
	std::cout << "→";
	while ((ch = _getch()) != ENTER)
	{
		if (ch == UP)
		{
			gotoxy(11, games, color::WHITE);
			std::cout << " ";
			--games;
			if (games < snake_game)
			{
				gotoxy(11, games, color::WHITE);
				std::cout << " ";
				games = exit_game;
			}
		}
		else if (ch == DOWN)
		{
			gotoxy(11, games, color::WHITE);
			std::cout << " ";
			++games;
			if (games > exit_game)
				games = snake_game;
		}
		gotoxy(11, games, color::WHITE);
		std::cout << "→";
	}
	return games;
}
void play_snake_game()
{
	SnakeGame sn;
	sn.play();
}
void play_snake_ai()
{
	std::cout << " 暂缺， 任意键返回";
	_getch();
}
