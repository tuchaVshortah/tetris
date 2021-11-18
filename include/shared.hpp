#pragma once
#ifndef SHARED_H
#define SHARED_H
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <string>
extern std::string ip_str, port_str;
extern sf::TcpSocket clientSocket, serverSocket;
extern sf::Music music;
extern sf::Font font;
extern bool play;
#endif
