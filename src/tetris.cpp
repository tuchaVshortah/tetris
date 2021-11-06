#include <cstdlib>
#include <string>
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "../include/tetris.hpp"
int main(){
	using namespace sf;
	tetrisInit();
	srand(time(0));
	RenderWindow window(VideoMode(1920, 1080), "Tetris");
	window.setFramerateLimit(60);
	
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
				}
			}
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
		fallDown(clock, blocks, backupBlocks, blocks2, backupBlocks2, score);
		checkLine(inactiveBlockSprites, score, inactiveBlockSprites2, score2);
		if(gameOver){
			window.draw(gameOverText);
			window.display();
		    std::this_thread::sleep_for(std::chrono::seconds(5));
			window.close();
		}
		window.display();
        	
	}
	return 0;
}