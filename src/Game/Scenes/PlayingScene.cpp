#include <SFML/Graphics.hpp>
#include "../src/Game/Headers/GameManager.hpp"
#include "../src/Game/Headers/Scenes.hpp"

void PlayingScene
(
	const bool isHost,
	sf::RenderWindow& window,
	sf::Font& font,
	std::unordered_map<uint8_t, std::unique_ptr<sf::TcpSocket>>& connections
)
{
	NacreCoordinator& nc = NacreCoordinator::getInstance();

	// game state variables
	sf::Clock clock;
	std::queue<Entity> renderQueue;

	Entity loadedTextures = makeLoadedTexturesContainer();

	// entity instantiation
	Entity player1 = makePlayer
	(
		1,
		ETexture::TEXTURE_PLACEHOLDER,
		{
			window.getSize().x / 2.f,
			window.getSize().y / 2.f
		},
		{
			40.f,
			40.f
		},
		{
			-300.f,
			-300.f
		},
		{
			300.f,
			300.f
		},
		{
			500.f,
			500.f
		},
		{
			50.f,
			50.f
		},
		sf::Color::Red
	);

	Entity player2 = makePlayer
	(
		2,
		ETexture::TEXTURE_PLACEHOLDER,
		{
			window.getSize().x / 2.f - 75.f,
			window.getSize().y / 2.f
		},
		{
			40.f,
			40.f
		},
		{
			-300.f,
			-300.f
		},
		{
			300.f,
			300.f
		},
		{
			500.f,
			500.f
		},
		{
			50.f,
			50.f
		},
		sf::Color::Green
	);

	Entity player3 = makePlayer
	(
		3,
		ETexture::TEXTURE_PLACEHOLDER,
		{
			window.getSize().x / 2.f + 75.f,
			window.getSize().y / 2.f
		},
		{
			40.f,
			40.f
		},
		{
			-300.f,
			-300.f
		},
		{
			300.f,
			300.f
		},
		{
			500.f,
			500.f
		},
		{
			50.f,
			50.f
		},
		sf::Color::Blue
	);

	// onstart systems
	Start::setText(font); // font system is limited to one font
	Start::setTextOrigin();

	Start::loadTextures(loadedTextures);
	Start::loadSprites(loadedTextures);
	Start::setSpriteOrigin();
	Start::setColor();

	sf::Packet playerControl;
	sf::Packet applySpeed;

	const uint8_t playerID = isHost ? 1 : connections.begin()->first;
	Entity playerEntity;

	Start::getPlayerEntity
	(
		playerID,
		playerEntity
	);

	while (window.isOpen())
	{
		DeltaTime dt = clock.restart().asSeconds();

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}

			if (event->is<sf::Event::KeyPressed>())
			{
				Control::doPlayerControl
				(
					playerControl,
					isHost,
					playerEntity,
					playerID,
					dt,
					connections
				);
			}
		}

		// systems
		Update::applySpeed
		(
			playerControl,
			applySpeed,
			isHost,
			playerEntity,
			playerID,
			connections
		);
		Update::move(dt);
		Update::drag(dt);

		window.clear();
		// render systems
		Render::doZIndex(renderQueue);
		Render::render
		(
			window,
			renderQueue
		);
		window.display();
	}
}