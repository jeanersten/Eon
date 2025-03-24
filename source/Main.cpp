#include <SFML/Graphics.hpp>

int main()
{
  sf::RenderWindow window {sf::VideoMode(sf::Vector2u{640u, 480u}), "Eon Engine"};

  while(window.isOpen())
  {
    while (const std::optional event = window.pollEvent())
    {
      if (event->is<sf::Event::Closed>())
      {
        window.close();
      }
    }

    window.clear();
    window.display();
  }

  return 0;
}
