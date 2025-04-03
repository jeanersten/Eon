#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <optional>

Game::Game(const char* title, bool fullscreen)
  : m_title(title)
  , m_running(true)
  , m_fullscreen(fullscreen)
{
  init();
}

void Game::init()
{
  sf::VideoMode current_desktop_mode = sf::VideoMode::getDesktopMode();
  if (m_fullscreen)
  {
    sf::Vector2u fullscreen_size = current_desktop_mode.size;
    m_window.create(sf::VideoMode{fullscreen_size}, m_title, sf::Style::Default, sf::State::Fullscreen);
    m_window.setPosition(sf::Vector2i{0, 0});
  }
  else
  {
    sf::Vector2u windowed_size = sf::Vector2u{current_desktop_mode.size.x / 2, current_desktop_mode.size.y / 2};
    m_window.create(sf::VideoMode{windowed_size}, m_title, sf::Style::Close, sf::State::Windowed);
    m_window.setPosition(sf::Vector2i{(int)((current_desktop_mode.size.x / 2) - windowed_size.x / 2),
                                      (int)((current_desktop_mode.size.y / 2) - windowed_size.y / 2)});
  }
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
      m_running = false;
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
  while (m_running)
  {
    update();
  }
  
  m_window.close();
}
