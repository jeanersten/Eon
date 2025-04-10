#include "Debug.h"
#include "Game.h"
#include "Utils.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <cmath>
#include <optional>

Game::Game(const char* title, const std::string& config_path)
  : m_title(title)
  , m_running(true)
  , m_pausing(false)
  , m_game_font("assets/fonts/dogica.ttf")
  , m_score_text(m_game_font)
  , m_player_texture("assets/textures/Player.png")
  , m_bullet_texture("assets/textures/Bullet.png")
  , m_enemy_texture1("assets/textures/Enemy1.png")
  , m_enemy_texture2("assets/textures/Enemy2.png")
  , m_enemy_texture3("assets/textures/Enemy3.png")

{
  init(config_path);
}

void Game::init(const std::string& config_path)
{
  m_fullscreen = false;

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
    m_window.setPosition(sf::Vector2i{static_cast<int>((current_desktop_mode.size.x / 2) - windowed_size.x / 2),
                                      static_cast<int>((current_desktop_mode.size.y / 2) - windowed_size.y / 2)});
  }
  m_window.setFramerateLimit(60u);

  m_default_player_position = sf::Vector2f{static_cast<float>(m_window.getSize().x) / 2,
                                           static_cast<float>(m_window.getSize().y) / 2};

  m_score_text.setPosition(sf::Vector2f{4.0f, 4.0f});
  m_score_text.setCharacterSize(12.0f);
  m_score_text.setFillColor(sf::Color::White);

  m_enemy_texture[0] = m_enemy_texture1;
  m_enemy_texture[1] = m_enemy_texture2;
  m_enemy_texture[2] = m_enemy_texture3;


  spawnPlayer();
  spawnEnemy();
}

void Game::update()
{
  for (auto entity : m_entity_manager.getEntities())
  {
    entity->sprite->visual.setScale(entity->transform->scale);
  }
  if (!m_pausing)
  {
    handleComponentsInteraction();
    handleMovement();
    handleShoot();
    handleEnemySpawnTime();
    handleCollision();
    handleLifeSpan();
  }
  handleEvent();
  handleRendering();
}

void Game::restart()
{
  m_player->transform->position = m_default_player_position;
  for (auto entity : m_entity_manager.getEntities())
  {
    if (entity->getTag() != "Player")
    {
      entity->destroy();
    }
  }
}

void Game::spawnPlayer()
{
  m_player = m_entity_manager.makeEntity("Player");

  m_player->transform = std::make_shared<CTransform>(m_default_player_position, 200.0f);
  m_player->sprite = std::make_shared<CSprite>(m_player_texture);
  m_player->circle_collider = std::make_shared<CCircleCollider>(5.0f);
  m_player->input = std::make_shared<CInput>();

  m_player->sprite->visual.setPosition(m_player->transform->position);
  m_player->circle_collider->bounds.setPosition(m_player->transform->position);
  m_player->circle_collider->bounds.setFillColor(sf::Color::Transparent);
  m_player->circle_collider->bounds.setOutlineThickness(1.0f);
  m_player->circle_collider->bounds.setOutlineColor(sf::Color::Green);
}

void Game::spawnBullet()
{
  sf::Vector2f mouse_position {static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window))};

  auto bullet = m_entity_manager.makeEntity("Bullet");

  bullet->transform = std::make_shared<CTransform>(sf::Vector2f{m_player->transform->position}, 500.0f);
  bullet->sprite = std::make_shared<CSprite>(m_bullet_texture);
  bullet->circle_collider = std::make_shared<CCircleCollider>(1.0f);
  bullet->life_span = std::make_shared<CLifeSpan>(1.0f);

  bullet->transform->rotation = (mouse_position - bullet->transform->position).angle();
  bullet->transform->direction = (mouse_position - bullet->transform->position).normalized();
  bullet->sprite->visual.setPosition(m_player->transform->position);
  bullet->circle_collider->bounds.setPosition(m_player->transform->position);
  bullet->circle_collider->bounds.setFillColor(sf::Color::Transparent);
  bullet->circle_collider->bounds.setOutlineThickness(1.0f);
  bullet->circle_collider->bounds.setOutlineColor(sf::Color::Cyan);
}

void Game::spawnEnemy()
{
  auto enemy = m_entity_manager.makeEntity("Enemy");

  enemy->transform = std::make_shared<CTransform>(utils::generateRandomPosition(m_player->transform->position, sf::Vector2f{640, 480}), 50.0f);
  switch (utils::generateIndex(1, 3))
  {
    case 1:
      enemy->type = std::make_shared<CType>(0);
      enemy->sprite = std::make_shared<CSprite>(m_enemy_texture[enemy->type->index]);
      enemy->circle_collider = std::make_shared<CCircleCollider>(20.0f);
    break;

    case 2:
      enemy->type = std::make_shared<CType>(1);
      enemy->sprite = std::make_shared<CSprite>(m_enemy_texture[enemy->type->index]);
      enemy->circle_collider = std::make_shared<CCircleCollider>(28.0f);
    break;

    case 3:
      enemy->type = std::make_shared<CType>(2);
      enemy->sprite = std::make_shared<CSprite>(m_enemy_texture[enemy->type->index]);
      enemy->circle_collider = std::make_shared<CCircleCollider>(36.0f);
    break;

    default:
      ;
    break;
  }

  enemy->transform->direction = utils::generateRandomDirection();
  enemy->sprite->visual.setPosition(enemy->transform->position);
  enemy->circle_collider->bounds.setPosition(enemy->transform->position);
  enemy->circle_collider->bounds.setFillColor(sf::Color::Transparent);
  enemy->circle_collider->bounds.setOutlineThickness(1.0f);
  enemy->circle_collider->bounds.setOutlineColor(sf::Color::Red);
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> enemy)
{
  int object_division;

  switch (enemy->type->index)
  {
    case 0:
      object_division = 3;
    break;

    case 1:
      object_division = 4;
    break;

    case 2:
      object_division = 5;
    break;
    
    default:
      ;
    break;
  }

  for (int i = 0; i < object_division; i++)
  {
    sf::Angle angle = i * (sf::degrees(360) / object_division); 

    sf::Vector2f direction {std::cos(angle.asRadians()), std::sin(angle.asRadians())};

    auto small_enemy = m_entity_manager.makeEntity("SmallEnemy");
    small_enemy->transform = std::make_shared<CTransform>(sf::Vector2f{enemy->transform->position}, 20.0f);
    small_enemy->sprite = std::make_shared<CSprite>(m_enemy_texture[enemy->type->index]);
    small_enemy->circle_collider = std::make_shared<CCircleCollider>(enemy->circle_collider->bounds.getRadius() / 2);
    small_enemy->life_span = std::make_shared<CLifeSpan>(2.0f);

    small_enemy->transform->direction = direction;
    small_enemy->transform->scale = enemy->transform->scale / 2.0f;
    small_enemy->circle_collider->bounds.setPosition(small_enemy->transform->position);
    small_enemy->circle_collider->bounds.setFillColor(sf::Color::Transparent);
    small_enemy->circle_collider->bounds.setOutlineThickness(1.0f);
    small_enemy->circle_collider->bounds.setOutlineColor(sf::Color::Red);
  }
}

void Game::handleEvent()
{
  while(std::optional event = m_window.pollEvent())
  {
    if (m_window.hasFocus())
    {
      if (event->is<sf::Event::Closed>())
      {
        m_running = false;
      }
      else if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>())
      {
        switch (key_pressed->scancode)
        {
          case sf::Keyboard::Scancode::Left:
          case sf::Keyboard::Scancode::A:
            m_player->input->left = true;
          break;

          case sf::Keyboard::Scancode::Right:
          case sf::Keyboard::Scancode::D:
            m_player->input->right = true;
          break;

          case sf::Keyboard::Scancode::Up:
          case sf::Keyboard::Scancode::W:
            m_player->input->up = true;
          break;

          case sf::Keyboard::Scancode::Down:
          case sf::Keyboard::Scancode::S:
            m_player->input->down = true;
          break;

          default:
            ;
          break;
        }
      }
      else if (const auto* key_released = event->getIf<sf::Event::KeyReleased>())
      {
        switch (key_released->scancode)
        {
          case sf::Keyboard::Scancode::Left:
          case sf::Keyboard::Scancode::A:
            m_player->input->left = false;
          break;

          case sf::Keyboard::Scancode::Right:
          case sf::Keyboard::Scancode::D:
            m_player->input->right = false;
          break;

          case sf::Keyboard::Scancode::Up:
          case sf::Keyboard::Scancode::W:
            m_player->input->up = false;
          break;

          case sf::Keyboard::Scancode::Down:
          case sf::Keyboard::Scancode::S:
            m_player->input->down = false;
          break;

          default:
            ;
          break;
        }
      }
      else if (const auto* mouse_pressed = event->getIf<sf::Event::MouseButtonPressed>())
      {
        switch (mouse_pressed->button)
        {
          case sf::Mouse::Button::Left:
            m_player->input->shoot = true;
          break;

          default:
            ;
          break;
        }
      }
      else if (const auto* mouse_released = event->getIf<sf::Event::MouseButtonReleased>())
      {
        switch (mouse_released->button)
        {
          case sf::Mouse::Button::Left:
            m_player->input->shoot = false;
          break;

          default:
            ;
          break;
        }
      }
    }
  }
}

void Game::handleRendering()
{
  m_window.clear(sf::Color::Black);

  for (auto entity : m_entity_manager.getEntities())
  {
    if (entity->getTag() == "SmallEnemy")
    {
      entity->transform->rotation += sf::degrees(100) * m_delta_time;
    }
    entity->sprite->visual.setRotation(entity->transform->rotation);
    if (entity->getTag() != "Player" && entity->sprite && entity->circle_collider)
    {
      m_window.draw(entity->sprite->visual);
      /*m_window.draw(entity->circle_collider->bounds);*/
    }
    m_window.draw(m_player->sprite->visual);
    /*m_window.draw(m_player->circle_collider->bounds);*/
  }

  for (auto entity : m_entity_manager.getEntities())
  {
    if (entity->life_span)
    {
      float ratio = entity->life_span->remaining / entity->life_span->total;
      sf::Color transparent_change = entity->sprite->visual.getColor();
      transparent_change.a = (255 * ratio);

      entity->sprite->visual.setColor(transparent_change);
    }
  }

  debug::printDebugMsg(m_window, sf::Vector2f{4.0f, 4.0f}, std::to_string(m_player->transform->position.x));
  debug::printDebugMsg(m_window, sf::Vector2f{4.0f, 20.0f}, std::to_string(m_player->transform->position.y));
  debug::printDebugMsg(m_window, sf::Vector2f{4.0f, 36.0f}, std::to_string(m_current_time));
  debug::printDebugMsg(m_window, sf::Vector2f{4.0f, 52.0f}, std::to_string(m_delta_time));

  m_window.display();

}

void Game::handleComponentsInteraction()
{
  for (auto entity : m_entity_manager.getEntities())
  {
    if (entity->sprite && entity->circle_collider)
    {
      entity->sprite->visual.setPosition(entity->transform->position);
      entity->circle_collider->bounds.setPosition(entity->transform->position);
    }
  }
}

void Game::handleMovement()
{
  int moveX = static_cast<int>(m_player->input->right) - static_cast<int>(m_player->input->left);
  int moveY = static_cast<int>(m_player->input->down) - static_cast<int>(m_player->input->up);
  sf::Vector2f mouse_position {static_cast<sf::Vector2f>(sf::Mouse::getPosition(m_window))};

  if (moveX != 0 || moveY != 0)
  {
    m_player->transform->position += sf::Vector2f{static_cast<float>(moveX),
                                                  static_cast<float>(moveY)}.normalized() * m_player->transform->velocity * m_delta_time;
  }

  if (m_window.hasFocus())
  {
    m_player->transform->rotation = (mouse_position - m_player->transform->position).angle();
  }

  for (auto enemy : m_entity_manager.getEntities("Enemy"))
  {
    enemy->transform->position += enemy->transform->direction * enemy->transform->velocity * m_delta_time;
  }

  for (auto enemy : m_entity_manager.getEntities("SmallEnemy"))
  {
    enemy->transform->position += enemy->transform->direction * enemy->transform->velocity * m_delta_time;
  }
}

void Game::handleShoot()
{
  static float last_shot_time = m_current_time;
  float shoot_cooldown = 0.5f;

  if (m_player->input->shoot && (m_current_time - last_shot_time >= shoot_cooldown))
  {
    spawnBullet();
    last_shot_time = m_current_time;
  }

}

void Game::handleEnemySpawnTime()
{
  static float last_spawn_time = m_current_time;
  float spawn_cooldown = 2.0f;

  if (m_current_time - last_spawn_time >= spawn_cooldown)
  {
    if (m_entity_manager.getEntities("Enemy").size() <= 2)
    {
      spawnEnemy();
    }
    last_spawn_time = m_current_time;
  }
}

void Game::handleCollision()
{
  for (auto bullet : m_entity_manager.getEntities("Bullet"))
  {
    for (auto enemy : m_entity_manager.getEntities("Enemy"))
    {
      if (utils::collisionOccur(bullet, enemy))
      {
        spawnSmallEnemies(enemy);
        enemy->destroy();
        bullet->destroy();
      }
    }
  }

  for (auto player : m_entity_manager.getEntities("Player"))
  {
    for (auto enemy : m_entity_manager.getEntities("Enemy"))
    {
      if (utils::collisionOccur(player, enemy))
      {
        restart();
      }
    }
  }

  for (auto enemy : m_entity_manager.getEntities("Enemy"))
  {
    float enemy_left = enemy->transform->position.x - enemy->circle_collider->bounds.getRadius();
    float enemy_right = enemy->transform->position.x + enemy->circle_collider->bounds.getRadius();
    float enemy_top = enemy->transform->position.y - enemy->circle_collider->bounds.getRadius();
    float enemy_bottom = enemy->transform->position.y + enemy->circle_collider->bounds.getRadius();

    if (enemy_left <= 0 || enemy_right >= m_window.getSize().x)
    {
      enemy->transform->direction.x = -enemy->transform->direction.x;
    }
    if (enemy_top <= 0 || enemy_bottom >= m_window.getSize().y)
    {
      enemy->transform->direction.y = -enemy->transform->direction.y;
    }
  }

  float player_left = m_player->transform->position.x - m_player->circle_collider->bounds.getRadius();
  float player_right = m_player->transform->position.x + m_player->circle_collider->bounds.getRadius();
  float player_top = m_player->transform->position.y - m_player->circle_collider->bounds.getRadius();
  float player_bottom = m_player->transform->position.y + m_player->circle_collider->bounds.getRadius();

  if (player_left <= 0.0f)
  {
    m_player->transform->position.x = 0.0f + m_player->circle_collider->bounds.getRadius();
  }
  if (player_right >= m_window.getSize().x)
  {
    m_player->transform->position.x = m_window.getSize().x - m_player->circle_collider->bounds.getRadius();
  }
  if (player_top <= 0.0f)
  {
    m_player->transform->position.y = 0.0f + m_player->circle_collider->bounds.getRadius();
  }
  if (player_bottom >= m_window.getSize().y)
  {
    m_player->transform->position.y = m_window.getSize().y - m_player->circle_collider->bounds.getRadius();
  }
}

void Game::handleLifeSpan()
{
  for (auto entity : m_entity_manager.getEntities())
  {
    if (entity->getTag() == "Bullet" || entity->getTag() == "SmallEnemy")
    {
      entity->transform->position += entity->transform->direction * entity->transform->velocity * m_delta_time;
      entity->life_span->remaining -= m_delta_time;
      if (entity->life_span->remaining < 0.0f)
      {
        entity->destroy();
      }
    }
  }
}

void Game::run()
{
  sf::Clock global_clock;
  sf::Clock delta_clock;

  while (m_running)
  {
    m_delta_time = delta_clock.restart().asSeconds();
    m_current_time = global_clock.getElapsedTime().asSeconds();

    update();
    m_entity_manager.update();
  }
  
  m_window.close();
}
