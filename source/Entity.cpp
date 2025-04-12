#include "Entity.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <string>

Entity::Entity(unsigned int id, const std::string& tag)
  : m_active(true)
  , m_id(id)
  , m_tag(tag)
  , transform(nullptr)
  , sprite(nullptr)
  , rectangle_collider(nullptr)
  , circle_collider(nullptr)
  , score(nullptr)
  , life_span(nullptr)
  , input(nullptr)
{}

bool Entity::isActive()
{
  return m_active;
}

unsigned int Entity::getID()
{
  return m_id;
}

const std::string& Entity::getTag()
{
  return m_tag;
}

void Entity::destroy()
{
  m_active = false;
}
