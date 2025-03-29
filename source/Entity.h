#pragma once

class Entity
{
private:
  unsigned int m_id;

  bool m_active;

public:
  Entity();

  bool isActive();

  unsigned int getID();

  void destroy();
};

