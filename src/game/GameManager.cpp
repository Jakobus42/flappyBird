#include "../../include/game/GameManager.hpp"

namespace game {

/**
 * @brief Constructs a new GameManager object.
 */
GameManager::GameManager(): 
_window(sf::RenderWindow{{SCREEN_WIDTH, SCREEN_HEIGHT}, "Flappy Bird"}),
_currentFrame(0) {
  if (!_backgroundTexture.loadFromFile("assets/sprites/background-day-wide.png")) {
      throw std::runtime_error("cant load assets/sprites/background-day-wide.png");
  }
  _background.setTexture(_backgroundTexture);
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

void GameManager::init() {
  _config.loadFromFile("config.json");
  _window.setFramerateLimit(60);
}

bool GameManager::run() {
  while (_window.isOpen())
  {
    for (auto event = sf::Event{}; _window.pollEvent(event);)
    {
      if (((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) || event.type == sf::Event::Closed)
      {
        return 1;
      }
      for(auto it = _entities.begin(); it != _entities.end() && event.key.code == sf::Keyboard::Space; ++it) {
          if (auto bird = std::dynamic_pointer_cast<entity::Bird>(*it)) {
              (*bird).jump(_currentFrame);
          }
        }
    }
    for (auto it = _entities.begin(); it != _entities.end() - 1; ++it) {
      if(_entities.back()->checkCollision((*it))) {
        return 0;
      }
      if (auto pipe = std::dynamic_pointer_cast<entity::Pipe>(*it)) {
          if(pipe->checkCollision(_entities.back())) {
            return 0;
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
  return 0;
}

void GameManager::reset() {
  _entities.clear();
  _window.clear();
  _currentFrame = 0;
}
bool GameManager::menu() {
    sf::Font font;
    sf::Event event;
    if (!font.loadFromFile("font.ttf")) {
        throw std::runtime_error("can't open font");
    }

    sf::Text title;
    title.setFont(font);
    title.setString("Flappy Birds");
    title.setCharacterSize(80);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold);
    title.setPosition(_window.getSize().x / 2 - title.getGlobalBounds().width / 2, 100);

    sf::Text instruction;
    instruction.setFont(font);
    instruction.setString("Press SPACE to Start or ESC to Exit");
    instruction.setCharacterSize(50);
    instruction.setFillColor(sf::Color::White);
    instruction.setPosition(_window.getSize().x / 2 - instruction.getGlobalBounds().width / 2, _window.getSize().y / 2);

    bool spacePressed = false;
    bool scaleUp = true;
    float instructionScale = 1.0f;
    sf::Clock clock;
    float fadeAlpha = 255;
    bool fading = false;

    while (_window.isOpen()) {
        _window.clear();
        _window.draw(_background);

        while (_window.pollEvent(event)) {
            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || event.type == sf::Event::Closed) {
                _window.close();
                return true;
            }
            if (event.key.code == sf::Keyboard::Space && !spacePressed) {
                spacePressed = true;
                fading = true;
            }
        }
        float deltaTime = clock.restart().asSeconds();
        if (!spacePressed) {
            if (scaleUp) {
                instructionScale += 0.5f * deltaTime;
                if (instructionScale >= 1.1f) {
                    scaleUp = false;
                }
            } else {
                instructionScale -= 0.5f * deltaTime;
                if (instructionScale <= 1.0f) {
                    scaleUp = true;
                }
            }
            instruction.setScale(instructionScale, instructionScale);
            instruction.setPosition(_window.getSize().x / 2 - instruction.getGlobalBounds().width / 2, _window.getSize().y / 2);
        }
        if (fading) {
            fadeAlpha -= 400 * deltaTime;
            if (fadeAlpha <= 0) {
                return false;
            }
            instruction.setFillColor(sf::Color(255, 255, 255, fadeAlpha));
            title.setFillColor(sf::Color(255, 255, 255, fadeAlpha));  
        }
        _window.draw(title);
        _window.draw(instruction);
        for (auto it = _entities.begin(); it != _entities.end(); ++it) {
            if (std::dynamic_pointer_cast<entity::Floor>(*it)) {
                (*it)->move(_currentFrame);
                (*it)->draw(_window, _currentFrame);
            }
        }
        _window.display();
    }

    return true;
}


} /* namespace game */
