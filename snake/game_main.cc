#include <cstdlib>
#include <iostream>
#include <conio.h>
#include "snake.hpp"
#include "game.hpp"

int main()
{
	int ch = ESC;
	while ((ch = menu()) != ESC)
	{
		switch (ch)
		{
			case snake_game: 	play_snake_game();			break;
			case snake_ai:		play_snake_ai(); 			break;
			case exit_game: 	exit(0);
		}
		system("cls");
	}
	return 0;
}
