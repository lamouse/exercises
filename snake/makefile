CXXFLG=-Wall -std=c++1z 
game.exe: game.o game_main.o snake.o snakeGame.o
	g++ -o game.exe game.o game_main.o snake.o snakeGame.o $(CXXFLG)
snake.o: snake.hpp snake.cc
	g++ -c snake.cc -o snake.o $(CXXFLG)
game.o: game.hpp snake.hpp game.cc
	g++ -c game.cc -o game.o $(CXXFLG)
game_main.o: game.hpp snake.hpp game_main.cc
	g++ -c game_main.cc -o game_main.o $(CXXFLG)
snakeGame.o: game.hpp snake.hpp snakeGame.cc
	g++ -c snakeGame.cc -o snakeGame.o $(CXXFLG)
clear:
	del *.o