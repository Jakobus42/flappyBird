#pragma once

#include <SFML/Graphics.hpp>

namespace entity {

/**
 * @class AEntity
 * @brief ...
 */
class AEntity {
    public:
        AEntity();
        virtual ~AEntity();
        AEntity(const AEntity &other);
        AEntity& operator=(const AEntity &other);

        const sf::Texture& getTexture() const;
        const sf::Sprite& getSprite() const;

        virtual bool move() = 0;
    protected:
        sf::Texture _texture;
        sf::Sprite _sprite;
};

} /* namespace entity */
