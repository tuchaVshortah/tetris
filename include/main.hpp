#pragma once
#ifndef MAIN_H
#define MAIN_H
#include <SFML/Graphics.hpp>
extern int tetris(sf::RenderWindow &window);
extern int tetris2(sf::RenderWindow &window);
extern int tetrisNetwork(sf::RenderWindow &window, bool &serverState);
extern int tetrisInit();
#endif
