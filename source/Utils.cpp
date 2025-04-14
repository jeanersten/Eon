#include "Utils.h"

#include <cmath>
#include <filesystem>
#include <random>
#include <utility>

#if defined (_WIN32)
  #include <Windows.h>
#endif

#if defined (__linux__)
  #include <string>

  #include <limits.h>
  #include <unistd.h>
#endif

bool utils::collider::checkCircleVsCircle(std::shared_ptr<Entity> first_entity, std::shared_ptr<Entity> second_entity)
{
  const float x_distance {second_entity->transform->position.x - first_entity->transform->position.x};
  const float y_distance {second_entity->transform->position.y - first_entity->transform->position.y};
  const float squared_distance {(x_distance * x_distance) + (y_distance * y_distance)};

  const float first_entity_radius {first_entity->circle_collider->bounds.getRadius()};
  const float second_entity_radius {second_entity->circle_collider->bounds.getRadius()};
  const float squared_radius {(first_entity_radius + second_entity_radius) * (first_entity_radius + second_entity_radius)};

  return squared_distance <= squared_radius;
}

sf::Angle utils::calculator::angleBetween(sf::Vector2f from, sf::Vector2f to)
{
  return (to - from).angle();
}

sf::Vector2f utils::calculator::directionBetween(sf::Vector2f from, sf::Vector2f to)
{
  return (to - from).normalized();
}

std::filesystem::path utils::locator::getAssetPath(const std::filesystem::path& file_path)
{
  #if defined (_WIN32)
    wchar_t path[MAX_PATH] { 0 };
    GetModuleFileNameW(NULL, path, MAX_PATH);
    return std::filesystem::path(path).parent_path() / "assets" / file_path;
  #elif defined (__linux__)
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    return std::filesystem::path(std::string(result, (count > 0) ? count : 0)).parent_path() / "assets" / file_path;
  #endif
}

int utils::generator::generateRandomIndex(int min_range, int max_range)
{
  if (min_range > max_range)
  {
    std::swap(min_range, max_range);
  }

  static std::mt19937 generator {std::random_device{}()};
  std::uniform_int_distribution<int> distribution {min_range, max_range};

  return distribution(generator);
}

sf::Vector2f utils::generator::generateRandomDirection()
{
  sf::Angle angle_range {sf::degrees(360)};

  static std::mt19937 generator {std::random_device{}()};
  std::uniform_real_distribution<float> angle_distribution {0.0f, angle_range.asRadians()};

  float angle {angle_distribution(generator)};
  float x {std::cos(angle)}; 
  float y {std::sin(angle)}; 

  return sf::Vector2f{x, y};
}

sf::Vector2f utils::generator::generateRandomPosition(float x_min_range, float x_max_range,
                                                      float y_min_range, float y_max_range,
                                                      sf::Vector2f player_position, float player_range)
{
  if (x_min_range > x_max_range)
  {
    std::swap(x_min_range, x_max_range);
  }

  if (y_min_range > y_max_range)
  {
    std::swap(y_min_range, y_max_range);
  }

  static std::mt19937 generator {std::random_device{}()};
  std::uniform_real_distribution<float> x_distribution {x_min_range, x_max_range};
  std::uniform_real_distribution<float> y_distribution {y_min_range, y_max_range};

  sf::Vector2f random_position {0.0f, 0.0f};
  int attempts {0};

  do
  {
    random_position.x = x_distribution(generator);
    random_position.y = y_distribution(generator);

    float x_distance {random_position.x - player_position.x};
    float y_distance {random_position.y - player_position.y};
    float squared_distance {(x_distance * x_distance) + (y_distance * y_distance)};

    if (squared_distance >= (player_range * player_range) || (++attempts > 100))
    {
      break;
    }
  }
  while (true);

  return random_position;
}
