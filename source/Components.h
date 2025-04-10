#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

struct CTransform
{
  sf::Vector2f position;
  sf::Angle rotation;
  sf::Vector2f scale;
  sf::Vector2f direction;
  float velocity;

  CTransform(sf::Vector2f position);
  CTransform(sf::Vector2f position, float velcoity);
};

struct CSprite
{
  sf::Sprite visual;

  explicit CSprite(const sf::Texture& texture);
};

struct CRectangleCollider
{
  sf::RectangleShape bounds;

  CRectangleCollider(sf::Vector2f size);
};

struct CCircleCollider
{
  sf::CircleShape bounds;

  CCircleCollider(float radius);
};

struct CType
{
  unsigned int index;

  CType(int index);
};

struct CLifeSpan
{
  float remaining;
  float total;

  CLifeSpan(float total);
};

struct CScore
{
  int value;

  CScore(int value);
};

struct CInput
{
  bool left;
  bool right;
  bool up;
  bool down;
  bool shoot;

  CInput();
};
