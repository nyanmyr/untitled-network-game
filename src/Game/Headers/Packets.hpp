#ifndef PACKETS_HPP
#define PACKETS_HPP

#include <SFML/Network.hpp>

struct PMovement
{
    double newSpeedX = 0.0;
    double newSpeedY = 0.0;
    uint8_t id = 0;
};

sf::Packet& operator<<(sf::Packet& packet, const PMovement& data)
{
    return packet << data.newSpeedX << data.newSpeedY << data.id;
}

sf::Packet& operator>>(sf::Packet& packet, PMovement& data)
{
    return packet >> data.newSpeedX >> data.newSpeedY >> data.id;
}

#endif