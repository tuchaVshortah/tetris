#include <SFML/Graphics.hpp>
#include "../include/tetrisLogic.hpp"
#include "../include/types.hpp"
void tetrisInit(){
	using namespace sf;

	tile.loadFromFile("../images/tiles.png");
	font.loadFromFile("../fonts/arial.ttf");

	Sprite tileS(tile);
	
	scoreText.setString("Score:");
	scoreText.setStyle(Text::Bold);
	scoreText.setFillColor(Color::Blue);
	scoreText.setPosition(200, 30);

	score.setString("0");
	score.setStyle(Text::Bold | Text::Underlined | Text::Italic);
	score.setFillColor(Color::Red);
	score.setPosition(285, 30);

    for(int i = 0; i < 8; ++i){
		tileS.setTextureRect(IntRect(18 * i, 0, 18, 18));
		sprites[i] = tileS;
	}
}

Block blocks[4], backupBlocks[4];

void checkLine(int inactiveBlockSprites[HEIGHT][WIDTH], sf::Text &score){
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

bool checkIfInFrame(Block blocks[]){
	for(int i = 0, j = 0; i < 4; ++i){
		if(blocks[i].x < 0 || blocks[i].x >= WIDTH || blocks[i].y >= HEIGHT || inactiveBlockSprites[blocks[i].y][blocks[i].x] != 0){
			return false;
		}
	}
	return true;
}

void saveBlocks(Block backupBlocks[], Block blocks[]){
	for(int i = 0; i < 4; ++i){
		backupBlocks[i].x = blocks[i].x;
		backupBlocks[i].y = blocks[i].y;
		backupBlocks[i].blockSprite = blocks[i].blockSprite;
	}
}

void repairBlocks(Block blocks[], Block backupBlocks[]){
	for(int i = 0; i < 4; ++i){
		blocks[i].x = backupBlocks[i].x;
		blocks[i].y = backupBlocks[i].y;
		blocks[i].blockSprite = backupBlocks[i].blockSprite;
	}
}

void rotate(Block blocks[], Block backupBlocks[]){

	for(int i = 0; i < 4; ++i){
		saveBlocks(backupBlocks, blocks);
	}

	Block center = blocks[1];
	for(int i = 0; i < 4; ++i){
		int x = blocks[i].y - center.y;
		int y = blocks[i].x - center.x;
		blocks[i].x = center.x - x;
		blocks[i].y = center.y + y;
	}
	
	if(checkIfInFrame(blocks) == false){
		repairBlocks(blocks, backupBlocks);
	}
}

void verticalDown(Block blocks[], Block backupBlocks[], sf::Text &score){

	for(int i = 0; i < 4; ++i){
		saveBlocks(backupBlocks, blocks);
	}
	
	for(int i = 0; i < 4; ++i){
		++blocks[i].y;
	}

	if(checkIfInFrame(blocks) == false){
		repairBlocks(blocks, backupBlocks);
		generateNewFigure = true;
		--scoreValue;
		score.setString("-" + std::to_string(scoreValue));
	}
}

void horizontalRight(Block blocks[], Block backupBlocks[]){

	saveBlocks(backupBlocks, blocks);
	
	for(int i = 0; i < 4; ++i){
		++blocks[i].x;
	}

	if(checkIfInFrame(blocks) == false){
		repairBlocks(blocks, backupBlocks);
	}
}

void horizontalLeft(Block blocks[], Block backupBlocks[]){

	for(int i = 0; i < 4; ++i){
		saveBlocks(backupBlocks, blocks);
	}
	
	for(int i = 0; i < 4; ++i){
		--blocks[i].x;
	}

	if(checkIfInFrame(blocks) == false){
		repairBlocks(blocks, backupBlocks);
	}
}

void fallDown(sf::Clock &clock, Block blocks[], Block backupBlocks[], sf::Text &score){
	timer += clock.getElapsedTime().asSeconds();
	if(timer > delay){
		verticalDown(blocks, backupBlocks, score);
		clock.restart();
		timer = 0;
	}
}

