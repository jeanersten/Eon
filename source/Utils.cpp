#include "Entity.h"

#include <SFML/System.hpp>

#include <memory>
#include <random>
#include <utility>

namespace utils
{
  bool collisionOccur(std::shared_ptr<Entity> e1, std::shared_ptr<Entity> e2)
  {
    const float dx = e2->transform->position.x - e1->transform->position.x;
    const float dy = e2->transform->position.y - e1->transform->position.y;
    const float distance_squared = (dx * dx) + (dy * dy);

    const float r1 = e1->circle_collider->bounds.getRadius();
    const float r2 = e2->circle_collider->bounds.getRadius();
    const float radius_squared = (r1 + r2) * (r1 + r2);

    return distance_squared <= radius_squared;
  }

  int generateIndex(int min_range, int max_range)
  {
    if (min_range > max_range) std::swap(min_range, max_range);

    static std::random_device hardware_random;
    static std::mt19937 generate {hardware_random()};

    std::uniform_int_distribution<int> dist {min_range, max_range};

    return dist(generate);
  }

  sf::Vector2f generateRandomDirection()
  {
    sf::Angle angle_range;
    angle_range = sf::degrees(360);

    static std::random_device hardware_random;
    static std::mt19937 generate {hardware_random()};

    std::uniform_real_distribution<float> angle_dist {0.0f, angle_range.asRadians()};

    float angle = angle_dist(generate);

    float x = std::cos(angle);
    float y = std::sin(angle);

    return sf::Vector2f{x, y};
  }

  sf::Vector2f generateRandomPosition(sf::Vector2f player_position, sf::Vector2f range)
  {
    static std::random_device hardware_random;
    static std::mt19937 generate {hardware_random()};
    
    std::uniform_real_distribution<float> dist_x {64.0f, range.x};
    std::uniform_real_distribution<float> dist_y {64.0f, range.y};

    sf::Vector2f random_position;
    int attempts = 0;

    do
    {
      random_position.x = dist_x(generate);
      random_position.y = dist_y(generate);

      float dx = random_position.x - player_position.x;
      float dy = random_position.y - player_position.y;
      float distance_squared = dx * dx + dy * dy;

      if (distance_squared >= 128 * 128 || ++attempts > 100) break;
    }
    while (true);

    return random_position;
  }
}

