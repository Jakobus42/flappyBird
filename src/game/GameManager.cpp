#include "../../include/game/GameManager.hpp"

namespace game {

/**
 * @brief Constructs a new GameManager object.
 */
GameManager::GameManager()
    : _window(sf::RenderWindow{{SCREEN_WIDTH, SCREEN_HEIGHT}, "Flappy Bird"}),
     _currentFrame(0),
     _score(0),
     _menu(Menu(SCREEN_WIDTH, SCREEN_HEIGHT)){
}



/**
 * @brief Destroys the GameManager object.
 */
GameManager::~GameManager() {}

/**
 * @brief Copy constructor.
 * @param other The other GameManager object to copy.
 */
GameManager::GameManager(const GameManager&):
_menu(500, 500) {

}

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
    _window.setFramerateLimit(_config.getGeneralConfig().fps);
    loadEntitiesFromConfig();
    music.setVolume(_config.getMusicConfig().volume);
    sound.setVolume(_config.getSoundEffectConfig().volume);
    if (!music.openFromFile(_config.getMusicConfig().music.at("default")))
        throw std::runtime_error("cant open " + _config.getMusicConfig().music.at("default"));
    if (!flapSound.loadFromFile(_config.getSoundEffectConfig().soundEffects.at("wing")))
        throw std::runtime_error("cant open " + _config.getSoundEffectConfig().soundEffects.at("wing"));
    if (!font.loadFromFile("font.ttf"))
        return  throw std::runtime_error("cant load font.ttf ");
    music.play();
}
 void GameManager::loadEntitiesFromConfig() {
 const auto& backgroundConfig = _config.getBackgroundConfig();
    for (std::size_t i = 0; i < 2; ++i) {
        _entities.push_back(Entity{EntitiyType::BACKGROUND, std::make_shared<entity::Background>(i, backgroundConfig.velocity, backgroundConfig.textures.at("default"))});
    }
    const auto& pipeConfig = _config.getPipeConfig();
    for (std::size_t i = 0; i < 4; ++i) {
        _entities.push_back(Entity{EntitiyType::PIPE, std::make_shared<entity::PipePair> (i, pipeConfig.velocity, pipeConfig.spacing, pipeConfig.gap, pipeConfig.textures.at("default"))});
    }
    const auto& birdConfig = _config.getBirdConfig();
    birdy = std::make_shared<entity::Bird>(
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

bool GameManager::startGame() {
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
                    sound.setBuffer(flapSound);
                    sound.play();
                }
            }
        }
        _window.clear();
        for (const auto& [type, entity] : _entities) {
            if (type == EntitiyType::PIPE || type == EntitiyType::FLOOR) {
                if(entity->checkCollision(birdy)) {
                    return 0;
                }
            } else if(birdy->getPosition().y <= 0) {
                return 0;
            }
            if(type == EntitiyType::PIPE && entity->getPosition().x - birdy->getPosition().x <= 5.0f && entity->getPosition().x - birdy->getPosition().x >= -5.0f) {
                _score++;
            }
            entity->move();
            entity->draw(_window, _currentFrame);
        }
        sf::Text scoreAsText("Score: " + std::to_string(_score), font, 70);
        scoreAsText.setPosition(20, 20);
        _window.draw(scoreAsText);
        _window.display();
        _currentFrame++;
    }
    return 1;
}


void GameManager::run() { //TODO refactor
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || 
               (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
                _window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    _menu.moveUp();
                } else if (event.key.code == sf::Keyboard::Down) {
                    _menu.moveDown();
                } else if (event.key.code == sf::Keyboard::Space) {
                    Menu::Option selected = _menu.getSelectedOption();
                    switch (selected) {
                        case Menu::Option::START:
                            startGame();
                            reset();
                            break;
                        case Menu::Option::OPTIONS:
                            std::cout << "Options selected" << std::endl;
                            break;
                        case Menu::Option::EXIT:
                            _window.close();
                            break;
                    }
                }
            }
        }
        _window.clear();
        for (const auto& [type, entity] : _entities) {
            if(type != EntitiyType::BIRD) {
                entity->move();
                entity->draw(_window, _currentFrame);
            }
        }
        _menu.draw(_window);
        _window.display();
    }
}

void GameManager::reset() {
    _score = 0;
    _entities.clear();
    loadEntitiesFromConfig();
}

} /* namespace game */
