#include "Game.h"

#include <SFML/System.hpp>

int main()
{
  Game game {"Eon Engine!", sf::Vector2u{640, 480}, false};
  game.run();

  return 0;
}
