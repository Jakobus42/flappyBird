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
        Pipe(std::size_t id);
        ~Pipe();
        Pipe(const Pipe &other);
        Pipe& operator=(const Pipe &other);

        bool move(std::size_t currentFrame);
        void draw(sf::RenderWindow& window, std::size_t currentFrame);

        static int64_t getRandomY();
    private:
        std::size_t _currentTexture;
        float _velocity;
        std::size_t _id;
        std::size_t _y;
};

} /* namespace entity */
