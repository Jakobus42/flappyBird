#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include "../entity/AEntity.hpp"
#include "../entity/Bird.hpp"
#include "../entity/Pipe.hpp"
#include "../entity/Floor.hpp"
#include "../entity/Button.hpp"

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
        bool checkCollsion(std::size_t x, std::size_t y) const;



    private:
        sf::RenderWindow _window;
        std::vector<std::shared_ptr<entity::AEntity>> _entities;
        sf::Sprite _background;
        sf::Texture _backgroundTexture;
        sf::Sprite _floor;
        std::size_t _currentFrame;
        entity::Button quit;

};

} /* namespace game */
