#pragma once

class Entity
{
private:
  bool m_active;

  unsigned int m_id;

public:
  Entity();

  bool isActive();

  unsigned int getID();

  void destroy();
};

