#pragma once

#include <SFML/Graphics.hpp>

namespace entity {

/**
 * @class AEntity
 * @brief ...
 */
class AEntity {
    public:
        AEntity(const sf::Texture& texture, const sf::Sprite& sprite);
        virtual ~AEntity();
        AEntity(const AEntity &other);
        AEntity& operator=(const AEntity &other);

        const sf::Texture& getTexture() const;
        const sf::Sprite& getSprite() const;

        virtual bool move() = 0;
    protected:
        std::vector<sf::Texture> _textures;
        sf::Sprite _sprite;
};

} /* namespace entity */
