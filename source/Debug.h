#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace debug
{
  void printDebugMsg(sf::RenderWindow& window, sf::Vector2f position, const sf::String& message);
}
