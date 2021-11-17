#include <cstdlib>
#include <string>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "tetris.hpp"
#include "shared.hpp"

int tetris(sf::RenderWindow &window){
	using namespace sf;

	Clock clock;
	while(window.isOpen()){
		window.clear(Color::White);

		Event event;
		while(window.pollEvent(event)){

			if(event.type == Event::Closed){
				window.close();
			}
			if (event.type == Event::KeyPressed){
				if(event.key.code == Keyboard::W){
					rotate(blocks, backupBlocks, true);
				}else if(event.key.code == Keyboard::S){
					verticalDown(blocks, backupBlocks, score, true);
				}else if(event.key.code == Keyboard::D){
					horizontalRight(blocks, backupBlocks, true);
				}else if(event.key.code == Keyboard::A){
					horizontalLeft(blocks, backupBlocks, true);
				}else if(event.key.code == Keyboard::Escape){

                    for(int i = 0; i < 4; ++i){
                        blocks[i].x = 0;
                        blocks[i].y = 0;
                        blocks[i].blockSprite = 0;
                    }

                    for(int i = 0; i < HEIGHT; ++i){
                        for(int j = 0; j < WIDTH; ++j){
                            inactiveBlockSprites[i][j] = 0;
                            inactiveBlockSprites2[i][j] = 0;
                        }
                    }

                    generateNewFigure = true;
                    scoreValue = 0;
                    score.setString("0");
                    kill = true;
                }
			}
		}
        if(kill){
            kill = false;
            break;
        }
		if(generateNewFigure){
			for(int i = 0; i < 4; ++i){
       			     	inactiveBlockSprites[blocks[i].y][blocks[i].x] = blocks[i].blockSprite;
        		}
			blockShape = rand() % 7;
			blockSprite = rand() % 8;
			offset = rand() % 8;
			for(int i = 0; i < 4; ++i){
				blocks[i].x = allBlockShapes[blockShape][i] % 2 + offset;
				blocks[i].y = allBlockShapes[blockShape][i] / 2;
				blocks[i].blockSprite = blockSprite;

			};
			generateNewFigure = false;
		}

		for(int i = 0; i < 4; ++i){
			sprites[blocks[i].blockSprite].setPosition(blocks[i].x * 18, blocks[i].y * 18);
			window.draw(sprites[blocks[i].blockSprite]);
		}

		for(int y = 0; y < HEIGHT; ++y){
			for(int x = 0; x < WIDTH; ++x){
				if(inactiveBlockSprites[y][x] != 0){
					sprites[inactiveBlockSprites[y][x]].setPosition(x * 18, y * 18);
					window.draw(sprites[inactiveBlockSprites[y][x]]);
				}
			}
		}

		window.draw(scoreText);
		window.draw(score);
		fallDown(clock, blocks, backupBlocks, score);
		checkLine(inactiveBlockSprites, score);
		if(gameOver){
			window.draw(gameOverText);
			window.display();
			sleep(seconds(5));

            for(int i = 0; i < 4; ++i){
                blocks[i].x = 0;
                blocks[i].y = 0;
                blocks[i].blockSprite = 0;
            }

            for(int i = 0; i < HEIGHT; ++i){
                for(int j = 0; j < WIDTH; ++j){
                    inactiveBlockSprites[i][j] = 0;
                    inactiveBlockSprites2[i][j] = 0;
                }
            }

            generateNewFigure = true;
            gameOver = false;
            scoreValue = 0;
            score.setString("0");
            break;
			//window.close();
		}
		window.display();
	}
	return 0;

}


int tetris2(sf::RenderWindow &window){
	using namespace sf;
	Clock clock;
	while(window.isOpen()){
		window.clear(Color::White);

		Event event;
		while(window.pollEvent(event)){

			if(event.type == Event::Closed){
				window.close();
			}
			if (event.type == Event::KeyPressed){
				if(event.key.code == Keyboard::W){
					rotate(blocks, backupBlocks, true);
				}else if(event.key.code == Keyboard::S){
					verticalDown(blocks, backupBlocks, score, true);
				}else if(event.key.code == Keyboard::D){
					horizontalRight(blocks, backupBlocks, true);
				}else if(event.key.code == Keyboard::A){
					horizontalLeft(blocks, backupBlocks, true);
				}else if(event.key.code == Keyboard::Up){
					rotate(blocks2, backupBlocks2, false);
				}else if(event.key.code == Keyboard::Down){
					verticalDown(blocks2, backupBlocks2, score2, false);
				}else if(event.key.code == Keyboard::Right){
					horizontalRight(blocks2, backupBlocks2, false);
				}else if(event.key.code == Keyboard::Left){
					horizontalLeft(blocks2, backupBlocks2, false);
				}else if(event.key.code == Keyboard::Escape){

                    for(int i = 0; i < 4; ++i){
                        blocks[i].x = 0;
                        blocks2[i].x = 0;

                        blocks[i].y = 0;
                        blocks2[i].y = 0;

                        blocks[i].blockSprite = 0;
                        blocks2[i].blockSprite = 0;
                    }

                    for(int i = 0; i < HEIGHT; ++i){
                        for(int j = 0; j < WIDTH; ++j){
                            inactiveBlockSprites[i][j] = 0;
                            inactiveBlockSprites2[i][j] = 0;
                        }
                    }

                    generateNewFigure = true;
                    generateNewFigure2 = true;
                    scoreValue = 0;
                    scoreValue2 = 0;
                    score.setString("0");
                    score2.setString("0");
                    kill = true;
                }
			}
		}
		if(kill){
            kill = false;
            break;
        }
		if(generateNewFigure){
			for(int i = 0; i < 4; ++i){
                    inactiveBlockSprites[blocks[i].y][blocks[i].x] = blocks[i].blockSprite;
            }
			blockShape = rand() % 7;
			blockSprite = rand() % 8;
			offset = rand() % 8;
			for(int i = 0; i < 4; ++i){
				blocks[i].x = allBlockShapes[blockShape][i] % 2 + offset;
				blocks[i].y = allBlockShapes[blockShape][i] / 2;
				blocks[i].blockSprite = blockSprite;
                
			};
			generateNewFigure = false;
		}

		if(generateNewFigure2){
			for(int i = 0; i < 4; ++i){
            			inactiveBlockSprites2[blocks2[i].y][blocks2[i].x] = blocks2[i].blockSprite;
        		}
			blockShape = rand() % 7;
			blockSprite = rand() % 8;
			offset = rand() % 8;
			for(int i = 0; i < 4; ++i){
				blocks2[i].x = allBlockShapes[blockShape][i] % 2 + offset;
				blocks2[i].y = allBlockShapes[blockShape][i] / 2;
				blocks2[i].blockSprite = blockSprite;
                
			};
			generateNewFigure2 = false;
		}
		
		for(int i = 0; i < 4; ++i){
			sprites[blocks[i].blockSprite].setPosition(blocks[i].x * 18, blocks[i].y * 18);
			window.draw(sprites[blocks[i].blockSprite]);
		}

		for(int i = 0; i < 4; ++i){
			sprites[blocks2[i].blockSprite].setPosition(blocks2[i].x * 18 + 500, blocks2[i].y * 18);
			window.draw(sprites[blocks2[i].blockSprite]);
		}

		for(int y = 0; y < HEIGHT; ++y){
			for(int x = 0; x < WIDTH; ++x){
				if(inactiveBlockSprites[y][x] != 0){
					sprites[inactiveBlockSprites[y][x]].setPosition(x * 18, y * 18);
					window.draw(sprites[inactiveBlockSprites[y][x]]);
				}
			}
		}

		for(int y = 0; y < HEIGHT; ++y){
			for(int x = 0; x < WIDTH; ++x){
				if(inactiveBlockSprites2[y][x] != 0){
					sprites[inactiveBlockSprites2[y][x]].setPosition(x * 18 + 500, y * 18);
					window.draw(sprites[inactiveBlockSprites2[y][x]]);
				}
			}
		}
		window.draw(scoreText);
		window.draw(score);
		window.draw(scoreText2);
		window.draw(score2);
		fallDown2(clock, blocks, backupBlocks, blocks2, backupBlocks2, score, score2);
		checkLine2(inactiveBlockSprites, score, inactiveBlockSprites2, score2);
		if(gameOver){
			window.draw(gameOverText);
			window.display();
		    sleep(seconds(5));

            for(int i = 0; i < 4; ++i){
                blocks[i].x = 0;
                blocks2[i].x = 0;

                blocks[i].y = 0;
                blocks2[i].y = 0;

                blocks[i].blockSprite = 0;
                blocks2[i].blockSprite = 0;
            }

            for(int i = 0; i < HEIGHT; ++i){
                for(int j = 0; j < WIDTH; ++j){
                    inactiveBlockSprites[i][j] = 0;
                    inactiveBlockSprites2[i][j] = 0;
                }
            }

            generateNewFigure = true;
            generateNewFigure2 = true;
            gameOver = false;
            scoreValue = 0;
            scoreValue2 = 0;
            score.setString("0");
            score2.setString("0");
            break;
			//window.close();
		}
		window.display();
        	
	}
	return 0;
}


void logic(sf::RenderWindow &window){
    using namespace sf;
    Clock clock;
    while(window.isOpen()){
		window.clear(Color::White);

		Event event;
		while(window.pollEvent(event)){

			if(event.type == Event::Closed){
				window.close();
			}
			if (event.type == Event::KeyPressed){
				if(event.key.code == Keyboard::W){
					rotate(blocks, backupBlocks, true);
				}else if(event.key.code == Keyboard::S){
					verticalDown(blocks, backupBlocks, score, true);
				}else if(event.key.code == Keyboard::D){
					horizontalRight(blocks, backupBlocks, true);
				}else if(event.key.code == Keyboard::A){
					horizontalLeft(blocks, backupBlocks, true);
				}else if(event.key.code == Keyboard::Escape){
                    for(int i = 0; i < HEIGHT; ++i){
                        for(int j = 0; j < WIDTH; ++j){
                            inactiveBlockSprites[i][j] = 0;
                            inactiveBlockSprites2[i][j] = 0;
                        }
                    }
                    generateNewFigure = true;
                    scoreValue = 0;
                    scoreValue2 = 0;
                    score.setString("0");
                    score2.setString("0");
                    kill = true;
                }
			}
		}
        if(kill){
            kill = false;
            break;
        }
		if(generateNewFigure){
			for(int i = 0; i < 4; ++i){
                inactiveBlockSprites[blocks[i].y][blocks[i].x] = blocks[i].blockSprite;
            }
			blockShape = rand() % 7;
			blockSprite = rand() % 8;
			offset = rand() % 8;
			for(int i = 0; i < 4; ++i){
				blocks[i].x = allBlockShapes[blockShape][i] % 2 + offset;
				blocks[i].y = allBlockShapes[blockShape][i] / 2;
				blocks[i].blockSprite = blockSprite;

			};
			generateNewFigure = false;
		}

		for(int i = 0; i < 4; ++i){
			sprites[blocks[i].blockSprite].setPosition(blocks[i].x * 18, blocks[i].y * 18);
			window.draw(sprites[blocks[i].blockSprite]);
		}

		for(int i = 0; i < 4; ++i){
			sprites[blocks2[i].blockSprite].setPosition(blocks2[i].x * 18 + 500, blocks2[i].y * 18);
			window.draw(sprites[blocks2[i].blockSprite]);
		}

		for(int y = 0; y < HEIGHT; ++y){
			for(int x = 0; x < WIDTH; ++x){
				if(inactiveBlockSprites[y][x] != 0){
					sprites[inactiveBlockSprites[y][x]].setPosition(x * 18, y * 18);
					window.draw(sprites[inactiveBlockSprites[y][x]]);
				}
			}
		}

		for(int y = 0; y < HEIGHT; ++y){
			for(int x = 0; x < WIDTH; ++x){
				if(inactiveBlockSprites2[y][x] != 0){
					sprites[inactiveBlockSprites2[y][x]].setPosition(x * 18 + 500, y * 18);
					window.draw(sprites[inactiveBlockSprites2[y][x]]);
				}
			}
		}
		window.draw(scoreText);
		window.draw(score);
		window.draw(scoreText2);
		window.draw(score2);
		fallDown(clock, blocks, backupBlocks, score);

		checkLine2(inactiveBlockSprites, score, inactiveBlockSprites2, score2);
		if(gameOver){
			window.draw(gameOverText);
			window.display();
		    sleep(seconds(5));
            for(int i = 0; i < HEIGHT; ++i){
                for(int j = 0; j < WIDTH; ++j){
                    inactiveBlockSprites[i][j] = 0;
                    inactiveBlockSprites2[i][j] = 0;
                }
            }

            generateNewFigure = true;
            gameOver = false;
            scoreValue = 0;
            scoreValue2 = 0;
            score.setString("0");
            score2.setString("0");
            break;
			//window.close();
		}
		window.display();
    }
}

int tetrisNetwork(sf::RenderWindow &window, bool &serverState){
	using namespace sf;

    if(serverState){
        Thread thread(&listen);
        thread.launch();
        thread.wait();

        Thread netWorker(&server);
        netWorker.launch();
        logic(window);
        netWorker.terminate();
    }else{
        Thread thread(&connect);
        thread.launch();
        thread.wait();

        Thread netWorker(&client);
        netWorker.launch();
        logic(window);
        netWorker.terminate();
    }

	return 0;
}

