#include "DebugOverlay.h"
#include "Utils.h"

#include <SFML/Graphics.hpp>

#include <string>

DebugOverlay::DebugOverlay()
  : m_font(utils::locator::getAssetPath("fonts/Dogica.ttf"))
  , m_draw_position(sf::Vector2f{10.0f, 10.0f})
  , m_text_gap(10.f)
{
  m_font.setSmooth(false);
}

void DebugOverlay::setDrawPosition(sf::Vector2f position)
{
  m_draw_position = position;
}

void DebugOverlay::setTextGap(float gap)
{
  m_text_gap = gap;
}

void DebugOverlay::write(const std::string& key, const std::string& message)
{
  const std::string full_text {key + ": " + message};
  auto it {m_text_entries.find(key)};

  if (it == m_text_entries.end())
  {
    auto [text, inserted] {m_text_entries.try_emplace(key, sf::Text{m_font, full_text, 10u})};

    if (inserted)
    {
      text->second.setFillColor(sf::Color::White);
      m_key_order.push_back(key);
    }
    else
    {
      return;
    }
  }
  else
  {
    it->second.setString(full_text);
  }
}

void DebugOverlay::draw(sf::RenderWindow& window)
{
    int line {0};

    for (const auto& key : m_key_order)
    {
      sf::Text& text {m_text_entries.at(key)};

      text.setPosition(sf::Vector2f{m_draw_position.x, m_draw_position.y + (line * m_text_gap)});
      window.draw(text);
      ++line;
    }
}
