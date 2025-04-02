#include "Entity.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

Entity::Entity()
{}

bool Entity::isActive()
{
  return m_active;
}

unsigned int Entity::getID()
{
  return m_id;
}

void Entity::destroy()
{
  m_active = false;
}
