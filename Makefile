all: compile link

compile:
	g++ -I/usr/include -c src/main.cpp -o output/main.o

link:
	g++ output/main.o -o output/sfml-app -L/usr/lib -lsfml-graphics -lsfml-window -lsfml-system