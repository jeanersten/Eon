#pragma once

#include "Entity.h"
#include "EntityManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <string>

class Game
{
private:
  std::string m_title;

  sf::Clock m_delta_clock;
  sf::Clock m_global_clock;
  float m_delta_time;
  float m_current_time;

  bool m_running;
  bool m_pausing;

  sf::RenderWindow m_render_window;
  sf::RenderTexture m_render_texture;

  sf::Vector2f m_mouse_position;

  bool m_fullscreen;

  sf::Texture m_player_textures[1];
  sf::Texture m_bullet_textures[1];
  sf::Texture m_enemy_textures[3];

  EntityManager m_entity_manager;

  std::shared_ptr<Entity> m_player;
  sf::Vector2f m_default_player_position;

  void init();
  void update();
  void reset();

  void spawnPlayer();
  void spawnBullet();
  void spawnEnemy();
  void spawnSmallEnemies(std::shared_ptr<Entity> enemy);

  void handleEvent();
  void handleRendering();
  void handleMovement();
  void handlePlayerShooting();
  void handleEnemySpawnTime(int max_enemies);
  void handleCollision();
  void handleLIfeSpan();

public:
  Game(const std::string& title, bool full_screen);

  void run();
};
