#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Headers/GameManager.hpp"
#include "Headers/Scenes.hpp"

#include <iostream>
#include <stdexcept>
#include <optional>
#include <memory>

using sf::RenderWindow;
using sf::VideoMode;

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

constexpr int MAX_FPS = 60;

const std::string FONT_FILEPATH = RESOURCES_PATH "arial.ttf";

const int PORT_NUMBER = 17316;

void main()
{
	std::vector< std::pair<uint8_t, std::unique_ptr<sf::TcpSocket>> > connections;
	bool isHost = false;

	while (true)
	{
		std::cout << "Enter 'h' to host or 'c' to connect: ";
		char role;
		if (!(std::cin >> role)) break;

		if (role == 'h')
		{
			isHost = true;
			sf::TcpListener listener;

			if (listener.listen(PORT_NUMBER) != sf::Socket::Status::Done)
			{
				std::cerr << "Error: Failed to bind listener on port " << PORT_NUMBER << ". Retrying..." << "\n";
				continue;
			}

			std::cout << "Hosting!" << "\n";
			std::cout << "Waiting for player2 to connect to port " << std::to_string(PORT_NUMBER) << "..." << "\n";

			for (uint8_t playerId = 2; playerId <= 3; ++playerId)
			{
				std::unique_ptr<sf::TcpSocket> newPlayer = std::make_unique<sf::TcpSocket>();
				std::cout << "Waiting for Player " << static_cast<int>(playerId) << "..." << "\n";

				if (listener.accept(*newPlayer) != sf::Socket::Status::Done)
				{
					std::cerr << "Error: Failed to accept Player " << static_cast<int>(playerId) << ". Retrying..." << "\n";
					break;
				}

				newPlayer->setBlocking(false);
				connections.push_back({ playerId, std::move(newPlayer) });
				std::cout << "Player " << static_cast<int>(playerId) << " connected!" << "\n";
			}

			if (connections.size() == 2)
			{
				std::cout << "Lobby full! Starting game..." << "\n";
				break;
			}
		}
		else if (role == 'c')
		{
			isHost = false;

			std::cout << "Enter host IP address: ";
			std::string ipStr;
			std::cin >> ipStr;

			std::unique_ptr<sf::TcpSocket> hostPlayer = std::make_unique<sf::TcpSocket>();
			std::optional<sf::IpAddress>  ip = sf::IpAddress::resolve(ipStr);

			if (!ip || hostPlayer->connect(*ip, PORT_NUMBER) != sf::Socket::Status::Done)
			{
				std::cerr << "Error: Failed to connect to host! Try again." << "\n";
				break;
			}

			hostPlayer->setBlocking(false);
			connections.push_back(std::make_pair(1, std::move(hostPlayer)));

			std::cout << "Connected to host!" << "\n";
			break;
		}
	}

	RenderWindow window(VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }), "Nacre Engine", sf::Style::Close);
	window.setFramerateLimit(MAX_FPS);

	NacreCoordinator& nc = NacreCoordinator::getInstance();

	// components registration
	nc.registerComponent<CPosition>();
	nc.registerComponent<CTransform>();
	nc.registerComponent<COrigin>();
	nc.registerComponent<CButton>();
	nc.registerComponent<CText>();
	nc.registerComponent<CNextScene>();
	nc.registerComponent<CZIndex>();
	nc.registerComponent<CVelocity>();
	nc.registerComponent<CSpeed>();
	nc.registerComponent<CPlayerController>();
	nc.registerComponent<CDrag>();
	nc.registerComponent<CSprite>();
	nc.registerComponent<CTexture>();
	nc.registerComponent<CTexturesContainer>();
	nc.registerComponent<CColor>();

	sf::Font font;
	if (!font.openFromFile(FONT_FILEPATH))
	{
		throw std::runtime_error("Font not found.");
	}

	playScene(window, Scene::MENU, font);
}