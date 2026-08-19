#include "../Headers/Scenes.hpp"
#include <stdexcept>

void playScene
(
    bool& isHost,
    sf::RenderWindow& window,
    Scene scene,
    sf::Font& font,
    std::unordered_map<uint8_t, std::unique_ptr<sf::TcpSocket>>& connections
)
{
    switch (scene) {
    case PLAYING:
        PlayingScene(isHost, window, font, connections);
        break;
    default:
        throw std::runtime_error("Scene does not exist.");
        break;
    }
}
