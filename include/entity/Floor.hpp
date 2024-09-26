#pragma once

#include <ctime>
#include <random>

#include "../game/GameManager.hpp"
#include "AEntity.hpp"

namespace entity {

/**
 * @class Floor
 * @brief ...
 */
class Floor : public AEntity {
   public:
    Floor(std::size_t id, std::size_t velocity, const std::vector<std::string>& texturePaths);
    ~Floor();
    Floor(const Floor& other);
    Floor& operator=(const Floor& other);

    bool move();
    void draw(sf::RenderWindow& window, std::size_t currentFrame);

   private:
    std::size_t _id;
};

} /* namespace entity */
