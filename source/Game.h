#pragma once

#include "EntityManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <string>

struct WindowConfig
{
  int width, height;
  int fps_limit;
  bool fullscreen;
};

struct FontConfig
{
  std::string path;
  int size;
  int red, green, blue;
};

struct PlayerConfig
{
   std::string texture_path;
   float collision_radius;
   float speed;
};

struct BulletConfig
{
  std::string texture_path;
  float collision_radius;
  float speed;
};

struct EnemyConfig
{
  std::string texture_path;
  float collision_radius;
  float min_speed, max_speed;
  int type;
  int spawn_interval;
};

class Game
{
private:
  WindowConfig m_window_config;
  FontConfig m_font_config;
  PlayerConfig m_player_config;
  BulletConfig m_bullet_config;
  EnemyConfig m_enemy_config;

  const char* m_title;

  float m_current_time;
  float m_delta_time;

  bool m_running;
  bool m_pausing;

  sf::RenderWindow m_window;

  bool m_fullscreen;

  sf::Font m_game_font;

  int m_score;
  sf::Text m_score_text;

  sf::Texture m_player_texture;
  sf::Texture m_bullet_texture;
  sf::Texture m_enemy_texture1;
  sf::Texture m_enemy_texture2;
  sf::Texture m_enemy_texture3;
  sf::Texture m_enemy_texture[3];

  EntityManager m_entity_manager;

  std::shared_ptr<Entity> m_player;
  sf::Vector2f m_default_player_position;

  void init(const std::string& config_path);
  void update();
  void restart();

  void spawnPlayer();
  void spawnBullet();
  void spawnUltimate();
  void spawnEnemy();
  void spawnSmallEnemies(std::shared_ptr<Entity> enemy);

  void handleEvent();
  void handleRendering();
  void handleComponentsInteraction();
  void handleMovement();
  void handleShoot();
  void handleEnemySpawnTime();
  void handleCollision();
  void handleLifeSpan();

public:
  Game(const char* title, const std::string& config_path);

  void run();
};
