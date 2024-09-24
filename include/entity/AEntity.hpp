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
        ~AEntity();
        AEntity(const AEntity &other);
        AEntity& operator=(const AEntity &other);

        const sf::Texture& getTexture() const;
        const sf::Sprite& getSprite() const;
    protected:
        sf::Texture texture;
        sf::Sprite sprite;

};

} /* namespace entity */
