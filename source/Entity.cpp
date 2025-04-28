#include "Entity.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <string>

Entity::Entity(unsigned int id, const std::string& tag)
  : m_active(true)
  , m_id(id)
  , m_tag(tag)
{}

bool Entity::isActive()
{
  return m_active;
}

unsigned int Entity::getID() const
{
  return m_id;
}

const std::string& Entity::getTag() const
{
  return m_tag;
}

void Entity::destroy()
{
  m_active = false;
}
