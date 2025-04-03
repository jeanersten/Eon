#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Game
{
private:
  const char* m_title;

  bool m_running;
  bool m_pausing;

  sf::RenderWindow m_window;

  bool m_fullscreen;

  void init();
  void update();

  void handleEvent();
  void handleRendering();

public:
  Game(const char* title, bool full_screen);

  void run();
};
