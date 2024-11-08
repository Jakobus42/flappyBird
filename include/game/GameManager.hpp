#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>

#include "../entity/AEntity.hpp"
#include "../entity/Background.hpp"
#include "../entity/Bird.hpp"
#include "../entity/PipePair.hpp"
#include "../game/Config.hpp"
#include "../game/Menu.hpp"

namespace game {

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080  // TODO dont hardcode

/**
 * @class GameManager
 * @brief ...
 */
class GameManager {
   public:
    GameManager();
    ~GameManager();
    GameManager(const GameManager& other);
    GameManager& operator=(const GameManager& other);

    void init(const std::string& configPath);
    void run();


   private:

    enum class EntitiyType { BIRD, PIPE, FLOOR, BACKGROUND };
    enum class GameState { MENU, PLAY, EXIT };
    struct Entity {
        EntitiyType type;
        std::shared_ptr<entity::AEntity> entity;
    };

    sf::RenderWindow _window;
    Config _config;
    std::vector<Entity> _entities;
    std::size_t _currentFrame;
    std::size_t _score;


    sf::Music music; //TODO extract into SoundManager later
    sf::SoundBuffer flapSound;
    sf::Sound sound;
    sf::Font font;

    Menu _menu;

    std::shared_ptr<entity::Bird> birdy;

    std::shared_ptr<entity::AEntity> findEntityByType(const std::vector<Entity>& entities, EntitiyType targetType);
    void loadEntitiesFromConfig();

    bool startGame();
    void reset();
};

} /* namespace game */
