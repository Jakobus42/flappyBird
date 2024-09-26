#pragma once

#include "../game/GameManager.hpp"
#include "AEntity.hpp"

namespace entity {

/**
 * @class PipePair
 * @brief Represents a pair of pipes (upper and lower) that move together.
 */
class PipePair : public AEntity {
   public:
    PipePair(float velocity, std::size_t spacing, std::size_t gap, const std::vector<std::string>& texturePaths);
    ~PipePair();
    PipePair(const PipePair& other);
    PipePair& operator=(const PipePair& other);

    bool move(); 
    void draw(sf::RenderWindow& window, std::size_t currentFrame);

   private:
    std::size_t getRandomY(); 
    std::size_t getUpperPipeY(); 

    sf::Sprite _lowerPipe;       
    sf::Sprite _upperPipe;       
    std::size_t _gap;
    std::size_t _randomY;     
};

}  // namespace entity
