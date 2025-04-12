#pragma once

#include "Entity.h"

#include <map>
#include <memory>
#include <string>
#include <vector>

using EntityCollection = std::vector<std::shared_ptr<Entity>>;
using TaggedEntityCollection = std::map<std::string, EntityCollection>;

class EntityManager
{
private:
  EntityCollection m_entities;
  EntityCollection m_entities_to_add;
  TaggedEntityCollection m_tagged_entities;

  unsigned int m_total_entities;

  void removeInactiveEntities(EntityCollection& entities);

public:
  EntityManager();

  const EntityCollection& getEntities();
  const EntityCollection& getEntities(const std::string& tag);

  std::shared_ptr<Entity> makeEntity(const std::string& tag);

  void update();
};
