#ifndef PACKETS_HPP
#define PACKETS_HPP

#include <SFML/Network.hpp>

struct PNewSpeed
{
    double x = 0.0;
    double y = 0.0;
    uint8_t id = 0;
    DeltaTime dt = 0;
};

sf::Packet& operator<<(sf::Packet& packet, const PNewSpeed& data)
{
    return packet << data.x << data.y << data.id << data.dt;
}

sf::Packet& operator>>(sf::Packet& packet, PNewSpeed& data)
{
    return packet >> data.x >> data.y >> data.id >> data.dt;
}

#endif