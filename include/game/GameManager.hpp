#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include "../entity/AEntity.hpp"
#include "../entity/Bird.hpp"
#include "../entity/Pipe.hpp"
#include "../entity/Floor.hpp"

namespace game {

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define PIPE_SPACING 692

/**
 * @class GameManager
 * @brief ...
 */
class GameManager {
    public:
        GameManager();
        ~GameManager();
        GameManager(const GameManager &other);
        GameManager& operator=(const GameManager &other);

        bool run();
        void reset();
        bool menu();
    private:
        sf::RenderWindow _window;
        std::vector<std::shared_ptr<entity::AEntity>> _entities;
        sf::Sprite _background;
        sf::Texture _backgroundTexture;
        std::size_t _currentFrame;

};

} /* namespace game */
