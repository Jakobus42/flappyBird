#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Pipe.hpp"

namespace entity {

/**
 * @brief A class representing a pair of pipes (upper and lower) that move together.
 * The upper and lower pipes share the same x-coordinate but have different y-coordinates,
 * with a gap in between them.
 */
class PipePair {
public:
    PipePair(std::size_t id, std::size_t velocity, std::size_t spacing, std::size_t gap, 
             const std::vector<std::string>& texturePaths);
    ~PipePair();

    bool move();
    void draw(sf::RenderWindow& window, std::size_t currentFrame);

private:
    std::size_t _id;
    std::size_t _velocity;    
    std::size_t _spacing;              
    std::size_t _gap;                  
    
    Pipe _upperPipe;  
    Pipe _lowerPipe; 
};

} // namespace entity

