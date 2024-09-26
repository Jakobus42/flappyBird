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
        _entities.push_back(std::make_shared<entity::Background>(i, backgroundConfig.velocity, backgroundConfig.textures.at("default"))); //TODO add a texture logic
    }
    const auto& floorConfig = _config.getFloorConfig();
    for (std::size_t i = 0; i < 2; ++i) {
        _entities.push_back(std::make_shared<entity::Floor>(i, floorConfig.velocity, floorConfig.textures.at("default")));
    }
    const auto& pipeConfig = _config.getPipeConfig();
    for (std::size_t i = 0; i < 4; ++i) {
        _entities.push_back(
            std::make_shared<entity::Pipe>(i, i % 2, pipeConfig.velocity, pipeConfig.spacing, 640 ,pipeConfig.textures.at("default"))); // TODO load gap in config
    }
    // const auto& birdConfig = _config.getBirdConfig();
    // _entities.push_back(std::make_shared<entity::Bird>(_window.getSize().x / 3, _window.getSize().y / 2, birdConfig.textures.at("default"), birdConfig.velocity, birdConfig.jumpForce))
}

template <typename T>
std::shared_ptr<T> GameManager::getEntity() const {
    for (const auto& entity : _entities) {
        if (auto specificEntity = std::dynamic_pointer_cast<T>(entity)) {
            return specificEntity;
        }
    }
    throw std::runtime_error("Cant find entity");
}


bool GameManager::run() {
    auto bird = getEntity<entity::Bird>();

    while (_window.isOpen()) {
        for (auto event = sf::Event{}; _window.pollEvent(event);) {
            if (((event.type == sf::Event::KeyPressed) &&
                 (event.key.code == sf::Keyboard::Escape)) ||
                event.type == sf::Event::Closed) {
                return 1;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                bird->jump(_currentFrame);
            }
        }
        _window.clear();
        for (const auto& entity : _entities) {
            if (std::dynamic_pointer_cast<entity::Pipe>(entity) || std::dynamic_pointer_cast<entity::Floor>(entity)) {
                if (bird->checkCollision(entity)) {
                    return 0;
                }
            }
            entity->move(_currentFrame);
            entity->draw(_window, _currentFrame);
        }
        _window.display();
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
