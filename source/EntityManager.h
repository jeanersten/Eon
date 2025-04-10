#pragma once

#include "Entity.h"

#include <map>
#include <memory.h>
#include <vector>

typedef std::vector<std::shared_ptr<Entity>> EntityContainer;
typedef std::map<std::string, EntityContainer> EntityMap;

class EntityManager
{
private:
  EntityContainer m_entities;
  EntityContainer m_entities_to_add;
  EntityMap m_entities_map;
  unsigned int m_total_entities;

  void removeInactiveEntities(EntityContainer& entities);

public:
  EntityManager();

  const EntityContainer& getEntities();
  const EntityContainer& getEntities(const std::string& tag);

  std::shared_ptr<Entity> makeEntity(const std::string& tag);

  void update();
};
