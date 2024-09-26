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
        Floor(std::size_t id, std::size_t velocity, const std::vector<std::string>& texturePaths);
        ~Floor();
        Floor(const Floor &other);
        Floor& operator=(const Floor &other);

        bool move(std::size_t currentFrame);
        void draw(sf::RenderWindow& window, std::size_t currentFrame);

    private:
        std::size_t _id;
};

} /* namespace entity */
