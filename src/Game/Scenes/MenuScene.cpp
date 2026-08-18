#include <SFML/Graphics.hpp>
#include "../src/Game/Headers/GameManager.hpp"
#include "../src/Game/Headers/Scenes.hpp"

void MenuScene(sf::RenderWindow& window, sf::Font& font) {
	NacreCoordinator& nc = NacreCoordinator::getInstance();

	// game state variables
	sf::Clock clock;
	std::queue<Entity> renderQueue;

	Entity loadedTextures = makeLoadedTexturesContainer();

	// entity instantiation
	Entity playButton = makeButton
	(
		ETexture::TEXTURE_PLACEHOLDER,
		{
			window.getSize().x / 2.f,
			window.getSize().y / 2.f
		},
		{
			200.f,
			100.f
		},
		Scene::PLAYING,
		"Play",
		font,
		sf::Color::Red
	);

	// onstart systems
	Start::setText(font); // font system is limited to one font
	Start::setTextOrigin();

	Start::loadTextures(loadedTextures);
	Start::loadSprites(loadedTextures);
	Start::setSpriteOrigin();
	Start::setColor();

	while (window.isOpen())
	{
		DeltaTime dt = clock.restart().asSeconds();

		auto& pixelPos = sf::Mouse::getPosition(window);
		auto& worldPos = window.mapPixelToCoords(pixelPos);

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}

			if (const auto& mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (mousePressed->button == sf::Mouse::Button::Left)
				{
					Control::buttonClicks
					(
						{ 
							static_cast<int>(worldPos.x),
							static_cast<int>(worldPos.y)
						},
						dt
					);
				}
			}
		}

		// update systems
		Update::doButtons
		(
			{
				static_cast<int>(worldPos.x),
				static_cast<int>(worldPos.y)
			},
			dt
		);

		window.clear();
		// render systems
		Render::doZIndex(renderQueue);
		Render::render(window, renderQueue);
		window.display();
	}
}