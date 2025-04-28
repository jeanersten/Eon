#include "Components.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

CTransform::CTransform(sf::Vector2f position)
  : position(position)
  , rotation(sf::degrees(0.0f))
  , direction(sf::Vector2f{0.0f, 0.0f})
  , scale(sf::Vector2f{1.0f, 1.0f})
  , speed(0.0f)
{}

CSprite::CSprite(const sf::Texture& texture)
  : visual(texture)
{}

CText::CText(const sf::Font& font)
  : visual(font)
{}

CRectangleCollider::CRectangleCollider(sf::Vector2f size)
  : bounds(size)
{}

CCircleCollider::CCircleCollider(float radius)
  : bounds(radius)
{}

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
