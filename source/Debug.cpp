#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace debug
{
  sf::Font display_font {"assets/fonts/dogica.ttf"};

  void printDebugMsg(sf::RenderWindow& window, sf::Vector2f position, const sf::String& message)
  {
  sf::Text local_text {display_font};
    local_text.setPosition(position);
    local_text.setString(message);
    local_text.setCharacterSize(10.0f);
    window.draw(local_text);
  }
}
