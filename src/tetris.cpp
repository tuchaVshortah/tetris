#include <cstdlib>
#include <string>
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
				if(event.key.code == Keyboard::Up || event.key.code == Keyboard::W){
					rotate(blocks, backupBlocks);
				}else if(event.key.code == Keyboard::Down || event.key.code == Keyboard::S){
					verticalDown(blocks, backupBlocks, score);
				}else if(event.key.code == Keyboard::Right || event.key.code == Keyboard::D){
					horizontalRight(blocks, backupBlocks);
				}else if(event.key.code == Keyboard::Left || event.key.code == Keyboard::A){
					horizontalLeft(blocks, backupBlocks);
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
		window.display();
        	
	}
	return 0;
}