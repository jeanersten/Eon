#pragma once

#include "Entity.h"

#include <SFML/System.hpp>

#include <memory>

namespace utils
{
  namespace collider
  {
    bool checkCircleVsCircle(std::shared_ptr<Entity> first_entity, std::shared_ptr<Entity> second_entity);
  }

  namespace generator
  {
    int generateRandomIndex(int min_range, int max_range);
    sf::Vector2f generateRandomDirection();
    sf::Vector2f generateRandomPosition(float x_min_range, float max_range,
                                        float y_min_range, float y_max_range,
                                        sf::Vector2f player_position, float player_range);
  }
}
