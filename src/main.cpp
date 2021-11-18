#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "main.hpp"
#include "shared.hpp"

std::string socket_str, ip_str, port_str;
sf::Music  music;
bool play = true;
sf::Font font;
void player(){
    music.openFromFile("../audio/music.wav");
    music.setLoop(true);
    if(play){
        music.play();
    }
}

int main(){
	tetrisInit();
	using namespace sf;
	int i = 0;
	RenderWindow window(VideoMode(1920, 1080), "Tetris");
	window.setFramerateLimit(60);

	font.loadFromFile("../fonts/font.ttf");
	Text titleText("", font, 60), gamemodeText("", font, 25), ipText("", font, 40), ip("", font, 40), portText("", font, 40), port("", font, 40), socketText("", font, 60), socket("", font, 60);
	titleText.setString("Choose gamemode:");
	titleText.setFillColor(Color::Blue);
	titleText.setPosition(200, 200);
	gamemodeText.setString("                            1 - singleplayer,\n\
                            2 - multiplayer on keyboard,\n\
                            3 - multiplayer on network,\n\
                            4 - toggle music");
	gamemodeText.setFillColor(Color::Red);
	gamemodeText.setPosition(200, 270);
	ipText.setString("Enter ip address of the server: ");
	ipText.setFillColor(Color::Green);
	ipText.setPosition(200, 340);
	ip.setFillColor(Color::Yellow);
	ip.setPosition(850, 340);
	portText.setString("Enter port of the server: ");
	portText.setFillColor(Color::Blue);
	portText.setPosition(200, 410);
	port.setFillColor(Color::Cyan);
	port.setPosition(850, 410);
    socketText.setString("Your PC is (c - client, s - server): ");
    socketText.setFillColor(Color::Blue);
    socketText.setPosition(200, 200);
    socket.setFillColor(Color::Red);
    socket.setPosition(1200, 200);
	bool title = true, getSocketType = false, drawSocketText = false, getIpAddress = false, drawIpText = false, getPort = false, drawPortText = false, server = false;
    Thread musicPlayer(&player);
    musicPlayer.launch();
	while(window.isOpen()){
        window.clear(Color::White);

        Event event;
		if(!(getSocketType || getIpAddress || getPort)){
            while(window.pollEvent(event)){
				if(event.type == Event::Closed){
					 window.close();
                }
                if (event.type == Event::KeyPressed){
					if(event.key.code == Keyboard::Num1){
                        if(tetris(window) != 0){
                            if(window.isOpen()){
                                window.close();
                            }
                        }
                    }else if(event.key.code == Keyboard::Num2){
						if(tetris2(window) != 0){
							if(window.isOpen()){
								window.close();
                            }
                        }else{
                            tetrisInit();
                        }
					}else if(event.key.code == Keyboard::Num3){
                        title = false;
                        getSocketType = true;
                        drawSocketText = true;
					}else if(event.key.code == Keyboard::Escape){
                        if(window.isOpen()){
                            window.close();
                        }
                    }else if(event.key.code == Keyboard::Num4){
                        play = !(play);
                        if(play){
                            music.play();
                        }else{
                            music.pause();
                        }
                    }
				}
			}
		}

        if(title){
            window.draw(titleText);
            window.draw(gamemodeText);
        }

        if(getSocketType){
            Event socketEvent;
            while(window.pollEvent(socketEvent)){
                if(socketEvent.type == Event::Closed){
                    window.close();
                }

                if(socketEvent.key.code == Keyboard::C){
                    socket_str = "C";
                    server = false;
                }else if(socketEvent.key.code == Keyboard::S){
                    socket_str = "S";
                    server = true;
                }else if(socketEvent.key.code == Keyboard::Enter){
                    if(server == true && socket_str == "S"){
                        getSocketType = false;
                        getPort = true;
                        drawPortText = true;
                    }else if(server == false && socket_str == "C"){
                        getSocketType = false;
                        getIpAddress = true;
                        drawIpText = true;
                    }
                }else if(socketEvent.key.code == Keyboard::Backspace){
                    socket_str = "";
                }else if(socketEvent.key.code == Keyboard::Escape){
                    title = true;
                    getSocketType = false;
                    drawSocketText = false;
                    socket_str = "";
                    server = false;
                }else if(socketEvent.key.code == Keyboard::Num4){
                        play = !(play);
                        if(play){
                            music.play();
                        }else{
                            music.pause();
                        }
                }
            }
            socket.setString(socket_str);
        }

		if(getIpAddress){
		
			Event ipEvent;
			while(window.pollEvent(ipEvent)){
				
				if(ipEvent.type == Event::Closed){
					 window.close();
                }

				if(ipEvent.type == Event::KeyPressed){
					if(ipEvent.key.code == Keyboard::Num0){
						ip_str += "0";
                        ++i;
					}else if(ipEvent.key.code == Keyboard::Num1){
						ip_str += "1";
                        ++i;
					}else if(ipEvent.key.code == Keyboard::Num2){
						ip_str += "2";
                        ++i;
					}else if(ipEvent.key.code == Keyboard::Num3){
						ip_str += "3";
                        ++i;
					}else if(ipEvent.key.code == Keyboard::Num4){
						ip_str += "4";
                        ++i;
					}else if(ipEvent.key.code == Keyboard::Num5){
						ip_str += "5";
                        ++i;
					}else if(ipEvent.key.code == Keyboard::Num6){
						ip_str += "6";
                        ++i;
					}else if(ipEvent.key.code == Keyboard::Num7){
						ip_str += "7";
                        ++i;
					}else if(ipEvent.key.code == Keyboard::Num8){
						ip_str += "8";
                        ++i;
					}else if(ipEvent.key.code == Keyboard::Num9){
						ip_str += "9";
                        ++i;
					}else if(ipEvent.key.code == Keyboard::Period){
                        ip_str += ".";
                        ++i;
					}else if(ipEvent.key.code == Keyboard::Enter){
						if(i < 7 || i > 15){
							ip_str = "";
							i = 0;
						}else{
							i = 0;
							getIpAddress = false;
							getPort = true;
							drawPortText = true;
						}
					}else if(ipEvent.key.code == Keyboard::Backspace){
						ip_str.pop_back();
                        --i;
					}else if(ipEvent.key.code == Keyboard::Escape){
                        title = true;
                        drawSocketText = false;
                        getIpAddress = false;
                        drawIpText = false;
                        socket_str = "";
                        ip_str = "";
                        i = 0;
                    }else if(ipEvent.key.code == Keyboard::Num4){
                        play = !(play);
                        if(play){
                            music.play();
                        }else{
                            music.pause();
                        }
                    }
				}
			}
			ip.setString(ip_str);
		}
		
		if(getPort){
		
			Event portEvent;
			while(window.pollEvent(portEvent)){
				
				if(portEvent.type == Event::Closed){
					 window.close();
                }

				if(portEvent.type == Event::KeyPressed){
					if(portEvent.key.code == Keyboard::Num0){
						port_str += "0";
                        ++i;
					}else if(portEvent.key.code == Keyboard::Num1){
						port_str += "1";
                        ++i;
					}else if(portEvent.key.code == Keyboard::Num2){
						port_str += "2";
                        ++i;
					}else if(portEvent.key.code == Keyboard::Num3){
						port_str += "3";
                        ++i;
					}else if(portEvent.key.code == Keyboard::Num4){
						port_str += "4";
                        ++i;
					}else if(portEvent.key.code == Keyboard::Num5){
						port_str += "5";
                        ++i;
					}else if(portEvent.key.code == Keyboard::Num6){
						port_str += "6";
                        ++i;
					}else if(portEvent.key.code == Keyboard::Num7){
						port_str += "7";
                        ++i;
					}else if(portEvent.key.code == Keyboard::Num8){
						port_str += "8";
                        ++i;
					}else if(portEvent.key.code == Keyboard::Num9){
						port_str += "9";
                        ++i;
					}else if(portEvent.key.code == Keyboard::Enter){
						if(port_str == "" || i > 6){
							port_str = "";
							i = 0;
						}else{
                            window.clear(Color::White);
							if(tetrisNetwork(window, server) != 0){
								if(window.isOpen()){
									window.close();
                                }
                            }else{
                                title = true;
                                drawSocketText = false;
                                drawIpText = false;
                                getPort = false;
                                drawPortText = false;
                                socket_str = "";
                                ip_str = "";
                                port_str = "";
                            }
						}			
					}else if(portEvent.key.code == Keyboard::Backspace){
						port_str.pop_back();
                        --i;
					}else if(portEvent.key.code == Keyboard::Escape){
                        title = true;
                        drawSocketText = false;
                        drawIpText = false;
                        getPort = false;
                        drawPortText = false;
                        socket_str = "";
                        ip_str = "";
                        port_str = "";
                    }else if(portEvent.key.code == Keyboard::Num4){
                        play = !(play);
                        if(play){
                            music.play();
                        }else{
                            music.pause();
                        }
                    };
				}
			}
			port.setString(port_str);
		}

		if(drawSocketText){
            window.draw(socketText);
            window.draw(socket);
        }
		if(drawIpText){
			window.draw(ipText);
            window.draw(ip);
		}

		if(drawPortText){
			window.draw(portText);
            window.draw(port);
		}

		window.display();	
	}
	musicPlayer.terminate();
	return 0;
}
