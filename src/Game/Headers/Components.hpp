#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <SFML/Graphics.hpp>
#include "Scenes.hpp"
#include <optional>
#include <string>

enum TextFormat
{
	TOP,
	MIDDLE,
	BOTTOM
};

struct CPosition
{
	float x = 0.f;
	float y = 0.f;
};

struct CTransform
{
	float width = 0.f;
	float height = 0.f;
};

struct COrigin
{
	float offsetX = 0.f;
	float offsetY = 0.f;
};

struct CButton
{
	double clickedDuration = 0.f;
	double enabled = true;
	double clickedTimer = 0.f;
	bool clicked = false;
};

struct CText
{
	std::optional<sf::Text> box {};
	std::string string = "";
	int size = 12;
	sf::Color color = sf::Color::White;
	TextFormat format = TextFormat::MIDDLE;
};

struct CNextScene
{
	Scene next = Scene::PLAYING;
	bool active = false;
};

struct CZIndex
{
	int index = 0;
	bool visible = true;
};

struct CVelocity
{
	double minX = 0.f;
	double minY = 0.f;
	double maxX = 0.f;
	double maxY = 0.f;
	double x = 0.f;
	double y = 0.f;
};

struct CSpeed
{
	double x = 0.f;
	double y = 0.f;
};

struct CPlayerController
{
	bool enabled = false;
};

struct CDrag
{
	double x = 0.f;
	double y = 0.f;
};

struct CSprite
{
	std::optional<sf::Sprite> body {};
};

enum ETexture
{
	TEXTURE_PLACEHOLDER
};

struct CTexture
{
	ETexture data;

	CTexture() = default;
	CTexture(ETexture texture) :
		data(texture) {
	};
};

struct CTexturesContainer
{
	std::unordered_map<ETexture, sf::Texture> map;
};

struct CColor
{
	sf::Color col = sf::Color(sf::Color::White);
};


struct CPlayerID
{
	uint8_t id = 0;
};

#endif