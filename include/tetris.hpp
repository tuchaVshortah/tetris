#pragma once
#ifndef TETRIS_H
#define TETRIS_H
#include <SFML/Graphics.hpp>
#include "types.hpp"
extern const int HEIGHT, WIDTH;
extern int blockShape, blockSprite, offset;
extern int inactiveBlockSprites[20][10];
extern const int allBlockShapes[7][4];
extern double timer, delay;
extern bool generateNewFigure;
extern sf::Text scoreText, score;
extern sf::Sprite sprites[8];
extern struct Block blocks[4], backupBlocks[4];
extern void tetrisInit();
extern void checkLine(int inactiveBlockSprites[][10], sf::Text &score);
extern bool checkIfInFrame(Block blocks[]);
extern void saveBlocks(Block backupBlocks[], Block blocks[]);
extern void repairBlocks(Block blocks[], Block backupBlocks[]);
extern void rotate(Block blocks[], Block backupBlocks[]);
extern void verticalDown(Block blocks[], Block backupBlocks[], sf::Text &score);
extern void horizontalRight(Block blocks[], Block backupBlocks[]);
extern void horizontalLeft(Block blocks[], Block backupBlocks[]);
extern void fallDown(sf::Clock &clock, Block blocks[], Block backupBlocks[], sf::Text &score);
#endif