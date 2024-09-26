#pragma once

#include <ctime>
#include <random>

#include "../game/GameManager.hpp"
#include "AEntity.hpp"

namespace entity {

/**
 * @class Pipe
 * @brief ...
 */
class Pipe : public AEntity {
   public:
    Pipe(std::size_t id, bool isUpper, std::size_t velocity, std::size_t spacing, std::size_t gap,
         const std::vector<std::string>& texturePaths);
    ~Pipe();
    Pipe(const Pipe& other);
    Pipe& operator=(const Pipe& other);

    bool move();
    void draw(sf::RenderWindow& window, std::size_t currentFrame);

   private:
    std::size_t getLowerPipeY();
    std::size_t getUpperPipeY();

    bool _isUpper;
    std::size_t _id;
    std::size_t _y;
    std::size_t _gap;
    std::size_t _spacing;
};

} /* namespace entity */
