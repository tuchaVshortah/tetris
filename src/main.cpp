#include <SFML/Graphics.hpp>

using namespace sf;

int x(0), y(0), i(0);
float delay = 4.5, timer(0.0);

bool blockIsNotFalling = true;

const int HEIGHT = 20;
const int WIDTH = 10;

const int figures[7][4]=
{
	1,3,5,7, // I
	2,4,5,7, // S
	3,5,4,6, // Z
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};

struct Point
{
	int x, y;
} blocks[4], backupBlocks[4];

bool check(){
	for(i = 0; i < 4; ++i){
		if(blocks[i].y == HEIGHT){
			blockIsNotFalling = true;
			return true;
		}
	}
	return false;
}


bool checkIfInFrame(int &x, int &y){
	if(x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT){
		return true;
	}
	return false;
}

void saveBlocks(){
	backupBlocks[i].x = blocks[i].x;
	backupBlocks[i].y = blocks[i].y;
}

void repairBlocks(){
	for(i = 0; i < 4; ++i){
		blocks[i].x = backupBlocks[i].x;
		blocks[i].y = backupBlocks[i].y;
	}
}

void rotate(){

	for(i = 0; i < 4; ++i){
		saveBlocks();
	}

	Point center = blocks[1];
	for(i = 0; i < 4; ++i){

		int x = blocks[i].y - center.y;
		int y = blocks[i].x - center.x;
		blocks[i].x = center.x - x;
		blocks[i].y = center.y + y;
	}
	
	for(i = 0; i < 4; ++i){
		if(checkIfInFrame(blocks[i].x, blocks[i].y) == false){
			repairBlocks();
			break;
		}
	}
}

void verticalDown(){

	for(i = 0; i < 4; ++i){
		saveBlocks();
	}
	
	for(i = 0; i < 4; ++i){
		++blocks[i].y;
	}

	for(i = 0; i < 4; ++i){
		if(checkIfInFrame(blocks[i].x, blocks[i].y) == false){
			repairBlocks();
			break;
		}
	}
}

void horizontalRight(){

	for(i = 0; i < 4; ++i){
		saveBlocks();
	}
	
	for(i = 0; i < 4; ++i){
		++blocks[i].x;
	}

	for(i = 0; i < 4; ++i){
		if(checkIfInFrame(blocks[i].x, blocks[i].y) == false){
			repairBlocks();
			break;
		}
	}
}

void horizontalLeft(){

	for(i = 0; i < 4; ++i){
		saveBlocks();
	}
	
	for(i = 0; i < 4; ++i){
		--blocks[i].x;
	}

	for(i = 0; i < 4; ++i){
		if(checkIfInFrame(blocks[i].x, blocks[i].y) == false){
			repairBlocks();
			break;
		}
	}
}

void fallDown(Clock &clock){
	timer += clock.getElapsedTime().asSeconds();
	if(timer > delay){
		verticalDown();
		clock.restart();
		timer = 0;
	}
}

int main(){
	
	srand(time(0));
	
	RenderWindow window(VideoMode(320, 480), "tetris");
	window.setFramerateLimit(60);

	Texture tile, frame, background;

	tile.loadFromFile("../images/tiles.png");
	//frame.loadFromFile("/home/zeus/C++/Projects/Tetris_game/images/frame.png");
	//background.loadFromFile("/home/zeus/C++/Projects/Tetris_game/images/background.png");

	Sprite tileS(tile);
	//Sprite frameS(frame);
	//Sprite backgroundS(background);

	int n = rand() % 7;
	int colorTextureOffset = 18 * (rand() % 7);
	tileS.setTextureRect(IntRect(colorTextureOffset, 0, 18, 18));

	Clock clock;

	while(window.isOpen()){
		
		window.clear(Color::White);

		Event event;
		while(window.pollEvent(event)){

			if(event.type == Event::Closed){
				window.close();
			}
			if (event.type == Event::KeyPressed){
				if(event.key.code == Keyboard::Up){
					rotate();
				}else if(event.key.code == Keyboard::Down){
					verticalDown();
				}else if(event.key.code == Keyboard::Right || event.key.code == Keyboard::D){
					horizontalRight();
				}else if(event.key.code == Keyboard::Left || event.key.code == Keyboard::A){
					horizontalLeft();
				}
			}
		}
		
		if(blockIsNotFalling){
			for(int i = 0; i < 4; ++i){
				blocks[i].x = figures[n][i] % 2;
				blocks[i].y = figures[n][i] / 2;
			};
			blockIsNotFalling = false;
		}

		//window.draw(backgroundS);
		//window.draw(frameS);
		
		for(i = 0; i < 4; ++i){
			tileS.setPosition(blocks[i].x * 18, blocks[i].y * 18);
			window.draw(tileS);
		}

		window.display();

		fallDown(clock);

		if(check()){
			n = rand() % 7;
			colorTextureOffset = 18 * (rand() % 7);
			tileS.setTextureRect(IntRect(colorTextureOffset, 0, 18, 18));
		}
	}
	return 0;
}