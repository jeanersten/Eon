#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <optional>

Game::Game(const char* title, bool fullscreen)
  : m_title(title)
  , m_full_screen(fullscreen)
  , running(true)
{
  init();
}

void Game::init()
{
  // TODO: Implement fullscreen window
  sf::VideoMode desktop_mode = sf::VideoMode::getDesktopMode();
  m_window.create(desktop_mode, m_title, sf::Style::Default, sf::State::Windowed);
  m_window.setPosition(sf::Vector2i{(int)desktop_mode.size.x / 2, (int)desktop_mode.size.y / 2});
  m_window.setFramerateLimit(60u);
}

void Game::update()
{
  handleEvent();
  handleRendering();
}

void Game::handleEvent()
{
  while(std::optional event = m_window.pollEvent())
  {
    if (event->is<sf::Event::Closed>())
    {
      running = false;
    }
  }
}

void Game::handleRendering()
{
  m_window.clear(sf::Color::White);
  m_window.display();
}

void Game::run()
{
  while (running)
  {
    update();
  }
  
  // INQY: is this even needed?
  m_window.close();
}
