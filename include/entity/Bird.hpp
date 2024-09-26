#pragma once

#include "AEntity.hpp"
namespace entity {

/**
 * @class Bird
 * @brief ...
 */
class Bird: public AEntity {
    public:
        Bird(std::size_t x, std::size_t y, const std::vector<std::string>& texturePaths, std::size_t velocity, std::size_t jumpForce);
        ~Bird();
        Bird(const Bird &other);
        Bird& operator=(const Bird &other);

        bool move(std::size_t currentFrame);
        void draw(sf::RenderWindow& window, std::size_t currentFrame);

        bool jump(std::size_t currentFrame);
    private:
        const std::size_t _jumpForce;
};

} /* namespace entity */
