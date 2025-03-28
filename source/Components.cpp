#include "Components.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

CTransform::CTransform(sf::Vector2f position)
  : position(position)
  , rotation(sf::degrees(90.0f))
  , scale(sf::Vector2f{0.0f, 0.0f})
{}

CSprite::CSprite(const sf::Texture& texture)
  : visual(texture)
{}

CRectangleCollider::CRectangleCollider(sf::Vector2f size)
  : bounds(size)
{}
