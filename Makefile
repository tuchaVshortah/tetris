
all: compile link

compile:
	g++ -I/<path>/include -Iinclude -c src/tetris.cpp -o output/tetris.o
	g++ -I/<path>/include -c src/tetrisLogic.cpp -o output/tetrisLogic.o

link:
	g++ output/tetris.o output/tetrisLogic.o -o output/sfml-tetris -L/usr/lib -lsfml-graphics -lsfml-window -lsfml-system
