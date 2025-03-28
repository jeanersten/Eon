#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

struct CTransform
{
  sf::Vector2f position;
  sf::Angle rotation;
  sf::Vector2f scale;

  CTransform(sf::Vector2f position);
};

struct CSprite
{
  sf::Sprite visual;

  CSprite(const sf::Texture& texture);
};

struct CRectangleCollider
{
  sf::RectangleShape bounds;

  CRectangleCollider(sf::Vector2f size);
};
