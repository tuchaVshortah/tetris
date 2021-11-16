#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "tetrisLogic.hpp"
#include "types.hpp"
#include "shared.hpp"

sf::TcpSocket clientSocket, serverSocket;
Block blocks[4], blocks2[4], backupBlocks[4], backupBlocks2[4];

void tetrisInit(){
	using namespace sf;
	srand(time(0));
	tile.loadFromFile("../images/tiles.png");
	font.loadFromFile("../fonts/arial.ttf");

	Sprite tileS(tile);
	
	scoreText.setString("Score:");
	scoreText.setStyle(Text::Bold);
	scoreText.setFillColor(Color::Blue);
	scoreText.setPosition(200, 30);

	scoreText2.setString("Score:");
	scoreText2.setStyle(Text::Bold);
	scoreText2.setFillColor(Color::Blue);
	scoreText2.setPosition(800, 30);

	gameOverText.setString("Game over!");
	gameOverText.setStyle(Text::Bold);
	gameOverText.setFillColor(Color::Red);
	gameOverText.setPosition(500, 500);

	score.setString("0");
	score.setStyle(Text::Bold | Text::Underlined | Text::Italic);
	score.setFillColor(Color::Red);
	score.setPosition(285, 30);

	score2.setString("0");
	score2.setStyle(Text::Bold | Text::Underlined | Text::Italic);
	score2.setFillColor(Color::Red);
	score2.setPosition(885, 30);

    for(int i = 0; i < 8; ++i){
		tileS.setTextureRect(IntRect(18 * i, 0, 18, 18));
		sprites[i] = tileS;
	}
}

void checkLine2(int inactiveBlockSprites[HEIGHT][WIDTH], sf::Text &score, int inactiveBlockSprites2[HEIGHT][WIDTH], sf::Text &score2){
	int k = HEIGHT - 1;
	for(int i = 0; i < WIDTH; ++i){
		if(inactiveBlockSprites[1][i] != 0 || inactiveBlockSprites2[1][i] != 0){
			gameOver = true;
		}
	}
	for (int i = HEIGHT - 1; i > 0; --i){
		int count = 0;
		for (int j = 0; j < WIDTH; ++j){
			if (inactiveBlockSprites[i][j]) ++count;
			inactiveBlockSprites[k][j] = inactiveBlockSprites[i][j];
		}
		if(count < WIDTH){
			--k;
		}else{
			scoreValue += 10;
			score.setString(std::to_string(scoreValue));
		}
	}
	k = HEIGHT - 1;
	for (int i = HEIGHT - 1; i > 0; --i){
		int count = 0;
		for (int j = 0; j < WIDTH; ++j){
			if(inactiveBlockSprites2[i][j]) ++count;
			inactiveBlockSprites2[k][j] = inactiveBlockSprites2[i][j];
		}
		if(count < WIDTH){
			--k;
		}else{
			scoreValue2 += 10;
			score2.setString(std::to_string(scoreValue2));
		}
	}
}

void checkLine(int inactiveBlockSprites[HEIGHT][WIDTH], sf::Text &score){ 
	int k = HEIGHT - 1;
	for(int i = 0; i < WIDTH; ++i){
		if(inactiveBlockSprites[0][i] != 0 || inactiveBlockSprites2[0][i] != 0){
			gameOver = true;
		}
	}
	for (int i = HEIGHT - 1; i > 0; --i){
		int count = 0;
		for (int j = 0; j < WIDTH; ++j){
			if (inactiveBlockSprites[i][j]) ++count;
			inactiveBlockSprites[k][j] = inactiveBlockSprites[i][j];
		}
		if(count < WIDTH){
			--k;
		}else{
			scoreValue += 10;
			score.setString(std::to_string(scoreValue));
		}
	}
	
}

bool checkIfInFrame(Block blocks[], bool firstPlayer){
	for(int i = 0, j = 0; i < 4; ++i){
		if(firstPlayer){
			if(blocks[i].x < 0 || blocks[i].x >= WIDTH || blocks[i].y >= HEIGHT || inactiveBlockSprites[blocks[i].y][blocks[i].x] != 0){
				return false;
			}
		}else{
			if(blocks[i].x < 0 || blocks[i].x >= WIDTH || blocks[i].y >= HEIGHT || inactiveBlockSprites2[blocks[i].y][blocks[i].x] != 0){
				return false;
			}
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

void rotate(Block blocks[], Block backupBlocks[], bool firstPlayer){

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
	
	if(checkIfInFrame(blocks, firstPlayer) == false){
		repairBlocks(blocks, backupBlocks);
	}
}

void verticalDown(Block blocks[], Block backupBlocks[], sf::Text &score, bool firstPlayer){

	for(int i = 0; i < 4; ++i){
		saveBlocks(backupBlocks, blocks);
	}
	
	for(int i = 0; i < 4; ++i){
		++blocks[i].y;
	}

	if(checkIfInFrame(blocks, firstPlayer) == false){
		repairBlocks(blocks, backupBlocks);
		if(firstPlayer){
			generateNewFigure = true;
			--scoreValue;
			score.setString("-" + std::to_string(scoreValue));
		}else{
			generateNewFigure2 = true;
			--scoreValue2;
			score2.setString("-" + std::to_string(scoreValue));
		}
	}
}

void horizontalRight(Block blocks[], Block backupBlocks[], bool firstPlayer){

	saveBlocks(backupBlocks, blocks);
	
	for(int i = 0; i < 4; ++i){
		++blocks[i].x;
	}

	if(checkIfInFrame(blocks, firstPlayer) == false){
		repairBlocks(blocks, backupBlocks);
	}
}

void horizontalLeft(Block blocks[], Block backupBlocks[], bool firstPlayer){

	for(int i = 0; i < 4; ++i){
		saveBlocks(backupBlocks, blocks);
	}
	
	for(int i = 0; i < 4; ++i){
		--blocks[i].x;
	}

	if(checkIfInFrame(blocks, firstPlayer) == false){
		repairBlocks(blocks, backupBlocks);
	}
}

void fallDown2(sf::Clock &clock, Block blocks[], Block backupBlocks[],  Block blocks2[], Block backupBlocks2[], sf::Text &score, sf::Text &score2){
	timer += clock.getElapsedTime().asSeconds();
	if(timer > delay){
		verticalDown(blocks, backupBlocks, score, true);
		verticalDown(blocks2, backupBlocks2, score2, false);
		clock.restart();
		timer = 0;
	}
}


void fallDown(sf::Clock &clock, Block blocks[], Block backupBlocks[], sf::Text &score){
	timer += clock.getElapsedTime().asSeconds();
	if(timer > delay){
		verticalDown(blocks, backupBlocks, score, true);
		clock.restart();
		timer = 0;
	}
}

void listen(){
    sf::TcpListener listener;
    listener.listen((unsigned short)(std::stoi(port_str, nullptr)));
    listener.accept(clientSocket);
}

void server(){
    std::size_t received;
    clientSocket.setBlocking(true);
    while(true){
        if(clientSocket.receive(blocks2, sizeof(blocks2), received) == sf::Socket::Status::Done){
            if(clientSocket.receive(inactiveBlockSprites2, sizeof(inactiveBlockSprites2), received) == sf::Socket::Status::Done){
                if(clientSocket.send(blocks, sizeof(blocks)) == sf::Socket::Status::Done){
                    if(clientSocket.send(inactiveBlockSprites, sizeof(inactiveBlockSprites2)) != sf::Socket::Status::Done){
                        continue;
                    }
                }else{
                    continue;
                }
            }else{
                continue;
            }
        }else{
            continue;
        }
    }
}

void connect(){
    serverSocket.connect(ip_str, (unsigned short)(std::stoi(port_str, nullptr)));
}

void client(){
    std::size_t received;
    serverSocket.setBlocking(true);
    while(true){
        if(timer > delay){
            if(serverSocket.send(blocks, sizeof(blocks)) == sf::Socket::Status::Done){
                if(serverSocket.send(inactiveBlockSprites, sizeof(inactiveBlockSprites2)) == sf::Socket::Status::Done){
                    if(serverSocket.receive(blocks2, sizeof(blocks2), received) == sf::Socket::Status::Done){
                        if(serverSocket.receive(inactiveBlockSprites2, sizeof(inactiveBlockSprites2), received) != sf::Socket::Status::Done){
                            continue;
                        }
                    }else{
                        continue;
                    }
                }else{
                    continue;
                }
            }else{
                continue;
            }
        }
    }
}
