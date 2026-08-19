#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Headers/GameManager.hpp"
#include "Headers/Scenes.hpp"

#include <iostream>
#include <stdexcept>
#include <optional>
#include <memory>
#include <unordered_map>

using sf::RenderWindow;
using sf::VideoMode;

constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;

constexpr int MAX_FPS = 60;

const std::string FONT_FILEPATH = RESOURCES_PATH "arial.ttf";

const int PORT_NUMBER = 17316;

enum class PacketType : uint8_t
{
	ASSIGN_PLAYER_ID = 1,
	START_GAME = 2,
	PLAYER_STATE = 3
};

// TODO: player controls
// TOOD: borders
// TODO: hearts display
// TODO: hit player and lose a heart
// TODO: score system

void main()
{
	std::unordered_map<uint8_t, std::unique_ptr<sf::TcpSocket>> connections;
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
				connections[playerId] = std::move(newPlayer);
				std::cout << "Player " << static_cast<int>(playerId) << " connected!" << "\n";
			}

			if (connections.size() != 2)
			{
				continue;
			}

			for (auto& [id, socket] : connections)
			{
				sf::Packet idPacket;
				idPacket << static_cast<uint8_t>(PacketType::ASSIGN_PLAYER_ID) << static_cast<uint8_t>(id);
				
				if (socket->send(idPacket) != sf::Socket::Status::Done)
				{
					std::cerr << "Error: Failed to send ID to Player " << static_cast<int>(id) << "\n";
				}

				sf::Packet startPacket;
				startPacket << static_cast<uint8_t>(PacketType::START_GAME);
				if (socket->send(startPacket) != sf::Socket::Status::Done)
				{
					std::cerr << "Error: Failed to send Start signal to Player " << static_cast<int>(id) << "\n";
				}
			}

			std::cout << "Lobby full! Starting game..." << "\n";
			break;
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

			std::cout << "Connected to host!" << "\n";

			uint8_t myPlayerID = 0;
			bool gameStarted = false;

			std::cout << "Waiting for host to start the game..." << "\n";

			while (!gameStarted)
			{
				sf::Packet packet;

				if (hostPlayer->receive(packet) == sf::Socket::Status::Done)
				{
					uint8_t rawType;
					if (packet >> rawType)
					{
						auto type = static_cast<PacketType>(rawType);

						if (type == PacketType::ASSIGN_PLAYER_ID)
						{
							uint8_t assignedID;
							packet >> assignedID;
							myPlayerID = assignedID;
							std::cout << "Assigned Player ID: " << static_cast<int>(myPlayerID) << "\n";
						}
						else if (type == PacketType::START_GAME)
						{
							gameStarted = true;
							std::cout << "Host started the game!" << "\n";
						}
					}
				}

				sf::sleep(sf::milliseconds(10));
			}

			connections[myPlayerID] = std::move(hostPlayer);
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

	playScene
	(
		isHost,
		window,
		Scene::PLAYING,
		font,
		connections
	);
}