#pragma once

#include "Entity.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Game
{
private:
  const char* m_title {};

  // NOTE: later to implement
  [[maybe_unused]] bool m_full_screen {};

  bool running {};
  bool pausing {};

  // NOTE: temporary
  Entity player {};

  sf::RenderWindow m_window {};

  void init();
  void update();

  void handleEvent();
  void handleRendering();

public:
  Game(const char* title, bool full_screen);

  void run();
};
