
all: compile link

compile:
	g++ -I/usr/include -Iinclude -c src/tetris.cpp -o output/tetris.o
	g++ -I/usr/include -Iinclude -c src/tetrisLogic.cpp -o output/tetrisLogic.o
	g++ -I/usr/include -Iinclude -c src/main.cpp -o output/main.o

link:
	g++ output/tetris.o output/tetrisLogic.o output/main.o -o output/sfml-tetris -L/usr/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
