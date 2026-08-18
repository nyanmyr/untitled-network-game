#ifndef SCENES_HPP
#define SCENES_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <stdexcept>

enum Scene {
	MENU,
	PLAYING
};

void playScene
(
	sf::RenderWindow& window,
	Scene scene,
	sf::Font& font,
	std::unordered_map<uint8_t,
	std::unique_ptr<sf::TcpSocket>> connections
);
void MenuScene(sf::RenderWindow& window, sf::Font& font);
void PlayingScene(sf::RenderWindow& window, sf::Font& font);


#endif