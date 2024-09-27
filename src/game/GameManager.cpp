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
        _entities.push_back(Entity{EntitiyType::BACKGROUND, std::make_shared<entity::Background>(i, backgroundConfig.velocity, backgroundConfig.textures.at("default"))});
    }
    const auto& pipeConfig = _config.getPipeConfig();
    for (std::size_t i = 0; i < 4; ++i) {
        _entities.push_back(Entity{EntitiyType::PIPE, std::make_shared<entity::PipePair> (i, pipeConfig.velocity, pipeConfig.spacing, pipeConfig.gap, pipeConfig.textures.at("default"))});
    }
    const auto& birdConfig = _config.getBirdConfig();
    auto birdy = std::make_shared<entity::Bird>(
        _window.getSize().x / 3, 
        _window.getSize().y / 2, 
        birdConfig.textures.at("default"),
        birdConfig.velocity, 
        birdConfig.jumpForce);
    _entities.push_back(Entity{EntitiyType::BIRD, birdy});
    const auto& floorConfig = _config.getFloorConfig();
    for (std::size_t i = 0; i < 2; ++i) {
        _entities.push_back(Entity{EntitiyType::FLOOR, std::make_shared<entity::Background>(i, floorConfig.velocity, floorConfig.textures.at("default"))});
    }
}

std::shared_ptr<entity::AEntity> GameManager::findEntityByType(const std::vector<Entity>& entities, EntitiyType targetType) {
    for (const auto& e : entities) {
        if (e.type == targetType) {
            return e.entity;
        }
    }
    throw std::runtime_error("Cant find entity");
}

bool GameManager::run() {
    sf::Music music; //TODO extract into SoundManager later
    if (!music.openFromFile(_config.getMusicConfig().at("default")))
        throw std::runtime_error("cant open " + _config.getMusicConfig().at("default"));
    music.play();
    auto birdy = findEntityByType(_entities, EntitiyType::BIRD);
    while (_window.isOpen()) {
        for (auto event = sf::Event{}; _window.pollEvent(event);) {
            if (((event.type == sf::Event::KeyPressed) &&
                 (event.key.code == sf::Keyboard::Escape)) ||
                event.type == sf::Event::Closed) {
                return 1;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                auto bird = std::dynamic_pointer_cast<entity::Bird>(birdy);
                if (bird) {
                    bird->jump(_currentFrame);
                    // play sound
                }
            }
        }
        _window.clear();
        for (const auto& [type, entity] : _entities) {
            if (type == EntitiyType::PIPE || type == EntitiyType::FLOOR) {
                if(entity->checkCollision(birdy)) {
                    //play hit sound
                    return 0;
                }
            }
            entity->move();
            entity->draw(_window, _currentFrame);
        }
        _window.display();
        _currentFrame++;
    }
    return 1;
}


void GameManager::reset() {
    _entities.clear();
    _window.clear();
    _currentFrame = 0;
}

} /* namespace game */
