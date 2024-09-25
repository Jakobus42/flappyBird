#include "../../include/game/GameManager.hpp"

namespace game {

/**
 * @brief Constructs a new GameManager object.
 */
GameManager::GameManager(): 
_window(sf::RenderWindow{{SCREEN_WIDTH, SCREEN_HEIGHT}, "Flappy Bird"}),
_currentFrame(0) {

  for (std::size_t i = 0; i < 4; ++i) {
    _entities.push_back(std::make_shared<entity::Pipe>(i));
    _entities.push_back(std::make_shared<entity::Floor>(i));
  }
  _entities.push_back(std::make_shared<entity::Bird>(_window.getSize().x / 4, _window.getSize().y / 2));
}

/**
 * @brief Destroys the GameManager object.
 */
GameManager::~GameManager() {

}

/**
 * @brief Copy constructor.
 * @param other The other GameManager object to copy.
 */
GameManager::GameManager(const GameManager &) {
}

/**
 * @brief Copy assignment operator.
 * @param other The other GameManager object to assign from.
 * @return A reference to the assigned GameManager object.
 */
GameManager& GameManager::operator=(const GameManager &) {
    return *this;
}

void GameManager::start() {
  _window.setFramerateLimit(60);
  sf::Texture backgroundTexture;
  if (!backgroundTexture.loadFromFile("assets/sprites/background-day-wide.png")) {
      throw std::runtime_error("cant load assets/sprites/background-day-wide.png");
  }
  _background.setTexture(backgroundTexture);
  while (_window.isOpen())
  {
    for (auto event = sf::Event{}; _window.pollEvent(event);)
    {
      if (((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) || event.type == sf::Event::Closed)
      {
        _window.close();
      }
      for(auto it = _entities.begin(); it != _entities.end() && event.key.code == sf::Keyboard::Space; ++it) {
          if (auto bird = std::dynamic_pointer_cast<entity::Bird>(*it)) {
              (*bird).jump(_currentFrame);
          }
        }
    }
    for (auto it = _entities.begin(); it != _entities.end() - 1; ++it) {
      if(_entities.back()->checkCollision((*it))) {
        return ;
      }
      if (auto pipe = std::dynamic_pointer_cast<entity::Pipe>(*it)) {
          if(pipe->checkCollision(_entities.back())) {
            return ;
          }
      }
    }
    _window.draw(_background);
    for(auto it = _entities.begin(); it != _entities.end(); ++it) {
      (*it)->move(_currentFrame);
      (*it)->draw(_window, _currentFrame);
    }
    _window.display();
    _window.clear();
    _currentFrame++;
  }
}

} /* namespace game */
