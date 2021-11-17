#pragma once
#ifndef TETRIS_H
#define TETRIS_H
#include <SFML/Graphics.hpp>
#include "types.hpp"
extern const int HEIGHT, WIDTH;
extern int blockShape, blockSprite, offset;
extern int inactiveBlockSprites[20][10], inactiveBlockSprites2[20][10];
extern const int allBlockShapes[7][4];
extern double timer, timer2, delay;
extern bool generateNewFigure, generateNewFigure2, gameOver, kill;
extern sf::Text scoreText, scoreText2, score, score2, gameOverText;
extern sf::Sprite sprites[8];
extern struct Block blocks[4], blocks2[4], backupBlocks[4], backupBlocks2[4];
extern int scoreValue, scoreValue2;
extern void checkLine2(int inactiveBlockSprites[][10], sf::Text &score, int inactiveBlockSprites2[][10], sf::Text &score2);
extern void checkLine(int inactiveBlocksSprites[][10], sf::Text &score);
extern void saveBlocks(Block backupBlocks[], Block blocks[]);
extern void repairBlocks(Block blocks[], Block backupBlocks[]);
extern void rotate(Block blocks[], Block backupBlocks[], bool firstPlayer);
extern void verticalDown(Block blocks[], Block backupBlocks[], sf::Text &score, bool firstPlayer);
extern void horizontalRight(Block blocks[], Block backupBlocks[], bool firstPlayer);
extern void horizontalLeft(Block blocks[], Block backupBlocks[], bool firstPlayer);
extern void fallDown2(sf::Clock &clock, Block blocks[], Block backupBlocks[], Block blocks2[], Block backupBlocks2[], sf::Text &score, sf::Text &score2);
extern void fallDown(sf::Clock &clock, Block blocks[], Block backupBlocks[], sf::Text &score);
void listen();
void server();
void connect();
void client();
#endif
