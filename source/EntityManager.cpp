#include "EntityManager.h"

#include <string>

EntityManager::EntityManager()
  : m_total_entities(0)
{}

void EntityManager::removeInactiveEntities(EntityCollection& entities)
{
  for (EntityCollection::iterator it = entities.begin(); it != entities.end();)
  {
    if (!(*it)->isActive())
    {
      it = entities.erase(it);
    }
    else
    {
      ++it;
    }
  }
}

const EntityCollection& EntityManager::getEntities() const
{
  return m_entities;
}

const EntityCollection& EntityManager::getEntities(const std::string& tag) const
{
  static const EntityCollection empty {};
  auto it {m_tagged_entities.find(tag)};

  if (it != m_tagged_entities.end())
  {
    return it->second;
  }

  return empty;
}

std::shared_ptr<Entity> EntityManager::makeEntity(const std::string& tag)
{
  auto entity = std::shared_ptr<Entity>(new Entity(++m_total_entities, tag));

  m_entities_to_add.push_back(entity);
  m_tagged_entities[tag].push_back(entity);

  return entity;
}

void EntityManager::update()
{
  removeInactiveEntities(m_entities);

  for (auto& [tag, entities] : m_tagged_entities)
  {
    removeInactiveEntities(entities);
  }

  for (auto entity : m_entities_to_add)
  {
    m_entities.push_back(entity);
  }

  m_entities_to_add.clear();
}
