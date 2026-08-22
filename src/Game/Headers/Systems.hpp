#ifndef SYSTEMS_HPP
#define SYSTEMS_HPP

#include <SFML/Graphics.hpp>
#include "../../Engine/NacreCoordinator.hpp"
#include "Components.hpp"

namespace Start
{
	void setText(sf::Font& font);
	void setTextOrigin();
	void setSpriteOrigin();
	void loadTextures(Entity loadedTextures);
	void loadSprites(Entity loadedTextures);
	void setColor();
	void getPlayerEntity
	(
		const int8_t playerID,
		Entity& playerEntity
	);
}

namespace Control
{
	void doPlayerControl
	(
		sf::Packet& playerControl,
		const bool isHost,
		const Entity playerEntity,
		const uint8_t playerID,
		const DeltaTime dt,
		const std::unordered_map<uint8_t, std::unique_ptr<sf::TcpSocket>>& connections
	);
	void buttonClicks
	(
		const sf::Vector2i mouseVector,
		const DeltaTime dt
	);
}

namespace Update
{
	void applySpeed
	(
		sf::Packet& playerControl,
		sf::Packet& applySpeed,
		const bool isHost,
		const Entity playerEntity,
		const uint8_t playerID,
		const std::unordered_map<uint8_t, std::unique_ptr<sf::TcpSocket>>& connections
	);
	void doButtons
	(
		const sf::Vector2i mouseVector,
		const DeltaTime dt
	);
	void move(const DeltaTime dt);
	void drag(const DeltaTime dt);
}

namespace Render
{
	void doZIndex(std::queue<Entity>& renderQueue);
	void render
	(
		sf::RenderWindow& window,
		std::queue<Entity>& renderQueue
	);
}

#endif
