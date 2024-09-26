#pragma once

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>

#include "../entity/AEntity.hpp"
#include "../entity/Background.hpp"
#include "../entity/Bird.hpp"
#include "../entity/PipePair.hpp"
#include "../game/Config.hpp"

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
    bool run();
    void reset();


   private:

    enum class Entitiy { BIRD, PIPE, FLOOR, BACKGROUND };
    enum class GameState { MENU, PLAY, EXIT };


    sf::RenderWindow _window;
    Config _config;
    std::multimap<Entitiy, std::shared_ptr<entity::AEntity>> _entities;
    std::size_t _currentFrame;

};

} /* namespace game */
