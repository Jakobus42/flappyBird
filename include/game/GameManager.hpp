#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>

namespace game {

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

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

        bool checkCollsion(std::size_t x, std::size_t y) const;

    private:

};

} /* namespace game */
