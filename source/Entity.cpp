#include "Entity.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

Entity::Entity()
{
  visual.setRadius(50.0f);
  visual.setFillColor(sf::Color::Green);
  visual.setPosition(sf::Vector2f{50.0f, 50.0f});
}
