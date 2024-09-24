#pragma once

#include "AEntity.hpp"
namespace entity {

/**
 * @class Bird
 * @brief ...
 */
class Bird: public AEntity {
    public:
        Bird(std::size_t x, std::size_t y);
        ~Bird();
        Bird(const Bird &other);
        Bird& operator=(const Bird &other);

        bool move();
        void draw(sf::RenderWindow& window, std::size_t currentFrame);

};

} /* namespace entity */
