#pragma once

#include "AEntity.hpp"
#include "../game/GameManager.hpp"
#include <random> 
#include <ctime>

namespace entity {

/**
 * @class Pipe
 * @brief ...
 */
class Pipe: public AEntity {
    public:
        Pipe(std::size_t id, bool isUpper, std::size_t velocity, std::size_t spacing, std::size_t gap, const std::vector<std::string>& texturePaths);
        ~Pipe();
        Pipe(const Pipe &other);
        Pipe& operator=(const Pipe &other);

        bool move(std::size_t currentFrame);
        void draw(sf::RenderWindow& window, std::size_t currentFrame);
        bool checkCollision(std::shared_ptr<entity::AEntity> other) const;
    private:
        static std::size_t getLowerPipeY();
        static std::size_t Pipe::getUpperPipeY();
        
        bool _isUpper;
        sf::Sprite _secondPipe;
        std::size_t _id;
        std::size_t _y;
        std::size_t _gap;
        std::size_t _spacing;

};

} /* namespace entity */
