#pragma once

#include "Entity.h"

#include <SFML/System.hpp>

#include <memory>

namespace utils
{
  bool collisionOccur(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2);
  int generateIndex(int min_range, int max_range);
  sf::Vector2f generateRandomDirection();
  sf::Vector2f generateRandomPosition(sf::Vector2f player_position, sf::Vector2f range);
}
