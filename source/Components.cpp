#include "Components.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

CTransform::CTransform(sf::Vector2f position)
  : position(position)
  , rotation(sf::degrees(90.0f))
  , scale(sf::Vector2f{1.0f, 1.0f})
  , direction(sf::Vector2f{0.0f, 0.0f})
  , velocity(0.0f)
{}

CTransform::CTransform(sf::Vector2f position, float speed)
  : position(position)
  , rotation(sf::degrees(90.0f))
  , scale(sf::Vector2f{1.0f, 1.0f})
  , direction(sf::Vector2f{0.0f, 0.0f})
  , velocity(speed)
{}

CSprite::CSprite(const sf::Texture& texture)
  : visual(texture)
{
  visual.setOrigin(sf::Vector2f{static_cast<float>(visual.getTexture().getSize().x) / 2,
                                static_cast<float>(visual.getTexture().getSize().y) / 2});
}

CRectangleCollider::CRectangleCollider(sf::Vector2f size)
  : bounds(size)
{}

CCircleCollider::CCircleCollider(float radius)
  : bounds(radius)
{
  bounds.setOrigin(sf::Vector2f{radius, radius});
}

CType::CType(int index)
  : index(index)
{}

CScore::CScore(int value)
  : value(value)
{}

CLifeSpan::CLifeSpan(float total)
  : total(total)
  , remaining(total)
{}

CInput::CInput()
  : left(false)
  , right(false)
  , up(false)
  , down(false)
  , shoot(false)
{}
