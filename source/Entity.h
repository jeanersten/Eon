#pragma once

#include "Components.h"

#include <memory>
#include <string>

class Entity
{
  friend class EntityManager;

private:
  Entity(unsigned int id, const std::string& tag);

  bool m_active;

  unsigned int m_id;
  std::string m_tag;

public:
  std::shared_ptr<CTransform> transform;
  std::shared_ptr<CSprite> sprite;
  std::shared_ptr<CRectangleCollider> rectangle_collider;
  std::shared_ptr<CCircleCollider> circle_collider;
  std::shared_ptr<CScore> score;
  std::shared_ptr<CLifeSpan> life_span;
  std::shared_ptr<CInput> input;

  bool isActive();

  unsigned int getID();
  const std::string& getTag();

  void destroy();
};

