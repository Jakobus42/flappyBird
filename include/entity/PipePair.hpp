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
    PipePair(std::size_t id, float velocity, std::size_t spacing, std::size_t gap, const std::vector<std::string>& texturePaths);
    ~PipePair();
    PipePair(const PipePair& other);
    PipePair& operator=(const PipePair& other);

    bool move(); 
    void draw(sf::RenderWindow& window, std::size_t currentFrame);
    bool checkCollision(std::shared_ptr<entity::AEntity> other) const;
    const sf::Vector2f& getPosition() const;

   private:
    int64_t getRandomY(); 
    int64_t getUpperPipeY(); 

    sf::Sprite _lowerPipe;       
    sf::Sprite _upperPipe;       
    std::size_t _gap;
    std::size_t _randomY;   
    std::size_t _id;
    std::size_t _spacing;  
};

}  // namespace entity
