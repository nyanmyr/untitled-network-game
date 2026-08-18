#include "../Headers/Scenes.hpp"
#include <stdexcept>

void playScene
(
    sf::RenderWindow& window,
    Scene scene,
    sf::Font& font,
    std::unordered_map<uint8_t,
    std::unique_ptr<sf::TcpSocket>> connections
)
{
    switch (scene) {
    case MENU:
        MenuScene(window, font);
        break;
    case PLAYING:
        PlayingScene(window, font);
        break;
    default:
        throw std::runtime_error("Scene does not exist.");
        break;
    }
}
