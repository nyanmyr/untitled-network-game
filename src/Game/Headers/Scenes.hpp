#ifndef SCENES_HPP
#define SCENES_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <stdexcept>

enum Scene {
	PLAYING
};

void playScene
(
	const bool isHost,
	sf::RenderWindow& window,
	Scene scene,
	sf::Font& font,
	std::unordered_map<uint8_t, std::unique_ptr<sf::TcpSocket>>& connections
);
void PlayingScene
(
	const bool isHost,
	sf::RenderWindow& window,
	sf::Font& font,
	std::unordered_map<uint8_t, std::unique_ptr<sf::TcpSocket>>& connections
);


#endif