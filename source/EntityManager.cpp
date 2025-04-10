#include "EntityManager.h"

EntityManager::EntityManager()
{}

void EntityManager::removeInactiveEntities(EntityContainer& entities)
{
  for (EntityContainer::iterator it = entities.begin(); it != entities.end();)
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

const EntityContainer& EntityManager::getEntities()
{
  return m_entities;
}

const EntityContainer& EntityManager::getEntities(const std::string& tag)
{
  return m_entities_map[tag];
}

std::shared_ptr<Entity> EntityManager::makeEntity(const std::string& tag)
{
  auto entity = std::shared_ptr<Entity>(new Entity(++m_total_entities, tag));
  m_entities_to_add.push_back(entity);
  m_entities_map[tag].push_back(entity);
  return entity;
}

void EntityManager::update()
{
  removeInactiveEntities(m_entities);
  for (auto& [tag, entities] : m_entities_map)
  {
    removeInactiveEntities(entities);
  }

  for (auto entity : m_entities_to_add)
  {
    m_entities.push_back(entity);
  }
  m_entities_to_add.clear();
}
