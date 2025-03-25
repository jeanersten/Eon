#pragma once

#include "SFML/Graphics.hpp"

class Entity
{
private:
  unsigned int m_id {};

  bool m_active {};

public:
  Entity();

  // NOTE: temporary
  sf::CircleShape visual;

  bool isActive();

  unsigned int getID();

  void destroy();
};

