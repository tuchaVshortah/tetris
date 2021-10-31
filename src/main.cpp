#include <cstdlib>
#include <string>
#include "SFML/Graphics.hpp"

using namespace sf;

int scoreValue = 0, offset = 0;
float delay = 4.5, timer(0.0);

bool generateNewFigure = true;

const int HEIGHT = 20;
const int WIDTH = 10;

const int allBlockShapes[7][4] = {
	1,3,5,7, // I
	2,4,5,7, // S
	3,5,4,6, // Z
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};

struct Block{
	int x = 0, y = 0, blockSprite = 0;
} blocks[4], backupBlocks[4];
int inactiveBlockSprites[HEIGHT][WIDTH] = { 0 };

sf::Sprite sprites[8];

void checkLine(Text &score){
	int k = HEIGHT - 1;
	for (int i = HEIGHT - 1; i > 0; --i){
		int count = 0;
		for (int j = 0; j < WIDTH; ++j){
			if (inactiveBlockSprites[i][j]) ++count;
			inactiveBlockSprites[k][j] = inactiveBlockSprites[i][j];
		}
		if (count < WIDTH){
			--k;
		}else{
			scoreValue += 10;
			score.setString("+" + std::to_string(scoreValue));
		}
	}
}

bool checkIfInFrame(){
	for(int i = 0, j = 0; i < 4; ++i){
		if(blocks[i].x < 0 || blocks[i].x >= WIDTH || blocks[i].y >= HEIGHT || inactiveBlockSprites[blocks[i].y][blocks[i].x] != 0){
			return false;
		}
	}
	return true;
}

void saveBlocks(){
	for(int i = 0; i < 4; ++i){
		backupBlocks[i].x = blocks[i].x;
		backupBlocks[i].y = blocks[i].y;
		backupBlocks[i].blockSprite = blocks[i].blockSprite;
	}
}

void repairBlocks(){
	for(int i = 0; i < 4; ++i){
		blocks[i].x = backupBlocks[i].x;
		blocks[i].y = backupBlocks[i].y;
		blocks[i].blockSprite = backupBlocks[i].blockSprite;
	}
}

void rotate(){

	for(int i = 0; i < 4; ++i){
		saveBlocks();
	}

	Block center = blocks[1];
	for(int i = 0; i < 4; ++i){
		int x = blocks[i].y - center.y;
		int y = blocks[i].x - center.x;
		blocks[i].x = center.x - x;
		blocks[i].y = center.y + y;
	}
	
	if(checkIfInFrame() == false){
		repairBlocks();
	}
}

void verticalDown(Text &score){

	for(int i = 0; i < 4; ++i){
		saveBlocks();
	}
	
	for(int i = 0; i < 4; ++i){
		++blocks[i].y;
	}

	if(checkIfInFrame() == false){
		repairBlocks();
		generateNewFigure = true;
		--scoreValue;
		score.setString("-" + std::to_string(scoreValue));
	}
}

void horizontalRight(){

	saveBlocks();
	
	for(int i = 0; i < 4; ++i){
		++blocks[i].x;
	}

	if(checkIfInFrame() == false){
		repairBlocks();
	}
}

void horizontalLeft(){

	for(int i = 0; i < 4; ++i){
		saveBlocks();
	}
	
	for(int i = 0; i < 4; ++i){
		--blocks[i].x;
	}

	if(checkIfInFrame() == false){
		repairBlocks();
	}
}

void fallDown(Clock &clock, Text &score){
	timer += clock.getElapsedTime().asSeconds();
	if(timer > delay){
		verticalDown(score);
		clock.restart();
		timer = 0;
	}
}

int main(){
	
	srand(time(0));
	RenderWindow window(VideoMode(1920, 1080), "Tetris");
	window.setFramerateLimit(60);
	int blockShape = rand() % 7;
	int blockSprite = rand() % 8;

	//create Texture type variables
	Texture tile;
	Font font;
	//load tile scoreTexture from file
	tile.loadFromFile("../images/tiles.png");
	font.loadFromFile("../fonts/arial.ttf");
	//frame.loadFromFile("../images/frame.png");
	//background.loadFromFile("../images/background.png");

	//cache 8 tile sprites in memory to avoid file access
	Sprite tileS(tile);
	Text scoreText("", font, 25), score("", font, 25), timeText("", font, 35);
	scoreText.setString("Score:");
	scoreText.setStyle(Text::Bold);
	scoreText.setFillColor(sf::Color::Blue);
	scoreText.setPosition(200, 30);
	score.setString("0");
	score.setStyle(Text::Bold | Text::Underlined | Text::Italic);
	score.setFillColor(sf::Color::Red);
	score.setPosition(285, 30);
	
	//create and save tiles
	for(int i = 0; i < 8; ++i){
		tileS.setTextureRect(IntRect(18 * i, 0, 18, 18));
		sprites[i] = tileS;
	}

	
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
					rotate();
				}else if(event.key.code == Keyboard::Down || event.key.code == Keyboard::S){
					verticalDown(score);
				}else if(event.key.code == Keyboard::Right || event.key.code == Keyboard::D){
					horizontalRight();
				}else if(event.key.code == Keyboard::Left || event.key.code == Keyboard::A){
					horizontalLeft();
				}
			}
		}
		
		if(generateNewFigure){
			//save blocks that can not move
			for(int i = 0; i < 4; ++i){
            	inactiveBlockSprites[blocks[i].y][blocks[i].x] = blocks[i].blockSprite;
        	}
			//select a random shape and and sprite
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
		fallDown(clock, score);
		checkLine(score);
		window.display();
        	
	}
	return 0;
}