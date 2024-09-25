#pragma once

#include "AEntity.hpp"
#include "../game/GameManager.hpp"
#include <random> 
#include <ctime>

namespace entity {

/**
 * @class Floor
 * @brief ...
 */
class Floor: public AEntity {
    public:
        Floor(std::size_t id);
        ~Floor();
        Floor(const Floor &other);
        Floor& operator=(const Floor &other);

        bool move(std::size_t currentFrame);
        void draw(sf::RenderWindow& window, std::size_t currentFrame);

    private:
        std::size_t _currentTexture;
        float _velocity;
        std::size_t _id;
};

} /* namespace entity */
