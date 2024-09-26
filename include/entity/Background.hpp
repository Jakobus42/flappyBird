#pragma once

#include <ctime>
#include <random>

#include "../game/GameManager.hpp"
#include "AEntity.hpp"

namespace entity {

/**
 * @class Background
 * @brief ...
 */
class Background : public AEntity {
   public:
    Background(std::size_t id, std::size_t velocity, const std::vector<std::string>& texturePaths);
    ~Background();
    Background(const Background& other);
    Background& operator=(const Background& other);

    bool move(float maximumX);
    void draw(sf::RenderWindow& window, std::size_t currentFrame);

   private:
    std::size_t _id;
};

} /* namespace entity */
