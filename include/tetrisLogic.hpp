#pragma once 
#ifndef TETRIS_LOGIC_H
#define TETRIS_LOGIC_H
extern const int allBlockShapes[7][4] = {
	1,3,5,7, // I
	2,4,5,7, // S
	3,5,4,6, // Z
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};
extern const int HEIGHT = 20, WIDTH = 10;
int inactiveBlockSprites[HEIGHT][WIDTH] = { 0 }, inactiveBlockSprites2[HEIGHT][WIDTH] = { 0 };
int blockShape = rand() % 7, blockSprite = rand() % 8;
int scoreValue = 0, scoreValue2 = 0, offset = 0;
double timer = 0.0, timer2 = 0.0, delay = 4.5;
bool generateNewFigure = true, generateNewFigure2 = true, gameOver = false;

sf::Texture tile;
sf::Font font;
sf::Sprite sprites[8];
sf::Text scoreText("", font, 25), scoreText2("", font, 25),score("", font, 25), score2("", font, 25), gameOverText("", font, 80);
#endif