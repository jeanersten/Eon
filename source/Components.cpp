#include "Components.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

CTransform::CTransform(sf::Vector2f position)
  : position(position)
  , rotation(sf::degrees(90.0f))
  , direction(sf::Vector2f{0.0f, 0.0f})
  , scale(sf::Vector2f{1.0f, 1.0f})
  , speed(0.0f)
{}

CSprite::CSprite(const sf::Texture& texture)
  : visual(texture)
{
  visual.setOrigin(sf::Vector2f{static_cast<float>(texture.getSize().x) / 2.0f,
                                static_cast<float>(texture.getSize().y) / 2.0f});
}

CRectangleCollider::CRectangleCollider(sf::Vector2f size)
  : bounds(size)
{
  bounds.setOrigin(sf::Vector2f{size.x / 2.0f, size.y / 2.0f});
}

CCircleCollider::CCircleCollider(float radius)
  : bounds(radius)
{
  bounds.setOrigin(sf::Vector2f{radius, radius});
}

CLifeSpan::CLifeSpan(float value)
  : total(value)
  , remaining(value)
{}

CScore::CScore(int value)
  : amount(value)
{}

CInput::CInput()
  : left(false)
  , right(false)
  , up(false)
  , down(false)
  , shoot(false)
{}
