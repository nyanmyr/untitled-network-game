#include <SFML/Graphics.hpp>
#include "../Engine/NacreCoordinator.hpp"
#include "Headers/EntityMaker.hpp"
#include "Headers/Components.hpp"

NacreCoordinator& entityMakerNC = NacreCoordinator::getInstance();

Entity makePlayer
(
	const uint8_t playerID,
	const ETexture texture,
	const sf::Vector2f pos,
	const sf::Vector2f size,
	const sf::Vector2f minVelocity,
	const sf::Vector2f maxVelocity,
	const sf::Vector2f speed,
	const sf::Vector2f drag,
	const sf::Color col
)
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent
	(
		entity,
		CPosition
		{ 
			pos.x,
			pos.y
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CZIndex
		{
			1,
			true
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		COrigin
		{
			size.x / 2.f,
			size.y / 2.f
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CVelocity
		{
			minVelocity.x,
			minVelocity.y,
			maxVelocity.x,
			maxVelocity.y
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CSpeed
		{
			speed.x,
			speed.y
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CDrag
		{
			drag.x,
			drag.y
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CPlayerController
		{
			true
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CTransform
		{
			size.x,
			size.y
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CTexture{ texture }
	);
	entityMakerNC.addComponent
	(
		entity,
		CSprite{}
	);

	entityMakerNC.addComponent
	(
		entity,
		CColor{ col }
	);

	entityMakerNC.addComponent
	(
		entity,
		CPlayerID{ playerID }
	);

	return entity;
}

Entity makeButton
(
	const ETexture texture,
	const sf::Vector2f pos,
	const sf::Vector2f size,
	const Scene scene,
	const std::string str,
	const sf::Font& font,
	const sf::Color col
)
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent(
		entity,
		CPosition
		{
			pos.x,
			pos.y
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CTransform
		{
			size.x,
			size.y
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		COrigin
		{
			size.x / 2.f,
			size.y / 2.f
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CButton
		{
			0.125f,
			true
		}
	);

	sf::Text text(font);
	entityMakerNC.addComponent
	(
		entity,
		CText
		{
			text,
			str,
			64,
			sf::Color::Black,
			TextFormat::MIDDLE
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CNextScene
		{
			scene,
			false
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CZIndex
		{
			1,
			true
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CTransform
		{
			size.x,
			size.y
		}
	);
	entityMakerNC.addComponent
	(
		entity,
		CTexture{ texture }
	);
	entityMakerNC.addComponent
	(
		entity,
		CSprite{}
	);

	entityMakerNC.addComponent
	(
		entity,
		CColor{ col }
	);

	return entity;
}

Entity makeLoadedTexturesContainer()
{
	Entity entity = entityMakerNC.createEntity();

	entityMakerNC.addComponent
	(
		entity,
		CTexturesContainer{}
	);

	return entity;
}