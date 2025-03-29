#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Game
{
private:
  const char* m_title;

  bool running;
  bool pausing;

  sf::RenderWindow m_window;

  void init();
  void update();

  void handleEvent();
  void handleRendering();

public:
  Game(const char* title, bool full_screen);

  void run();
};
