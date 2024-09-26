#include "../../include/game/GameManager.hpp"

namespace game {

/**
 * @brief Constructs a new GameManager object.
 */
GameManager::GameManager()
    : _window(sf::RenderWindow{{SCREEN_WIDTH, SCREEN_HEIGHT}, "Flappy Bird"}), _currentFrame(0) {
    _window.setFramerateLimit(60);
}

/**
 * @brief Destroys the GameManager object.
 */
GameManager::~GameManager() {}

/**
 * @brief Copy constructor.
 * @param other The other GameManager object to copy.
 */
GameManager::GameManager(const GameManager&) {}

/**
 * @brief Copy assignment operator.
 * @param other The other GameManager object to assign from.
 * @return A reference to the assigned GameManager object.
 */
GameManager& GameManager::operator=(const GameManager&) { return *this; }

void GameManager::init(const std::string& configPath) {
    if (!_window.isOpen()) {
        throw std::runtime_error("Window cant be opened");
    }
    _config.loadFromFile(configPath);
    const auto& backgroundConfig = _config.getBackgroundConfig();
    for (std::size_t i = 0; i < 2; ++i) {
        _entities.push_back(
            entity::Background(i, backgroundConfig.velocity, backgroundConfig.textures));
    }
    const auto& floorConfig = _config.getFloorConfig();
    for (std::size_t i = 0; i < 2; ++i) {
        _entities.push_back(entity::Floor(i, floorConfig.velocity, floorConfig.textures));
    }
    const auto& pipeConfig = _config.getPipeConfig();
    for (std::size_t i = 0; i < 4; ++i) {
        _entities.push_back(
            entity::Pipe(i % 2, pipeConfig.velocity, pipeConfig.spacing, pipeConfig.textures));
    }
    const auto& birdConfig = _config.getBirdConfig();
    _entities.push_back(entity::Bird(_window.getSize().x / 3, _window.getSize().y / 2,
                                     birdConfig.textures, _window.getSize().y / 2,
                                     birdConfig.velocity, _window.getSize().y / 2,
                                     birdConfig.jumpForce));
}

bool GameManager::run() {
    while (_window.isOpen()) {
        for (auto event = sf::Event{}; _window.pollEvent(event);) {
            if (((event.type == sf::Event::KeyPressed) &&
                 (event.key.code == sf::Keyboard::Escape)) ||
                event.type == sf::Event::Closed) {
                return 1;
            }
            for (auto it = _entities.begin();
                 it != _entities.end() && event.key.code == sf::Keyboard::Space; ++it) {
                if (auto bird = std::dynamic_pointer_cast<entity::Bird>(*it)) {
                    (*bird).jump(_currentFrame);
                }
            }
        }
        _window.draw(_background);
        for (auto it = _entities.begin(); it != _entities.end(); ++it) {
            _entities.back()->checkCollision((*it))(*it)->move(_currentFrame);
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

} /* namespace game */
