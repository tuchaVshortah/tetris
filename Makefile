all: compile link

compile:
	g++ -I<path_to_the_include_folder_of_sfml_directory>/include -c src/main.cpp -o output/main.o

link:
	g++ output/main.o -o output/tetris -L<path_to_the_include_folder_of_sfml_directory>/lib -lsfml-graphics -lsfml-window -lsfml-system
