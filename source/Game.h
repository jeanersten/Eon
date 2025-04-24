#pragma once

#include "DebugOverlay.h"
#include "Entity.h"
#include "EntityManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <string>

enum class GameState
{
  MAIN_MENU,
  PAUSE,
  PLAY,
  WIN,
  LOSE
};

class Game
{
private:
  std::string m_title;

  sf::Clock m_delta_clock;
  sf::Clock m_global_clock;
  float m_delta_time;
  float m_current_time;

  bool m_running;

  GameState m_state;

  sf::Vector2u m_resolution;
  sf::Vector2u m_min_resolution;
  sf::RenderWindow m_render_window;
  sf::RenderTexture m_render_texture;
  sf::View m_view;

  sf::Vector2f m_mouse_position;

  bool m_fullscreen;

  DebugOverlay debug;

  sf::Texture m_banner_textures[2];
  sf::Texture m_button_textures[2];
  sf::Texture m_player_textures[1];
  sf::Texture m_bullet_textures[1];
  sf::Texture m_enemy_textures[3];

  EntityManager m_entity_manager;

  std::shared_ptr<Entity> m_player;
  sf::Vector2f m_default_player_position;

  void init();
  void update();
  void reset();

  void loadMainMenu();
  void loadPauseMenu();
  void spawnPlayer();
  void spawnBullet();
  void spawnEnemy();
  void spawnSmallEnemies(std::shared_ptr<Entity> enemy);

  void handleEvent();
  void handleRendering();
  void handleMainMenu();
  void handlePauseMenu();
  void handleMovement();
  void handlePlayerShooting(float delay);
  void handleEnemySpawnTime(float interval, int max_enemies);
  void handleCollision();
  void handleLIfeSpan();

public:
  Game(const std::string& title, sf::Vector2u resolution, bool full_screen);

  void run();
};
