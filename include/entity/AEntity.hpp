#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../game/GameManager.hpp"

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

        const std::vector<sf::Texture>& getTexture() const;
        const sf::Sprite& getSprite() const;

        virtual bool move() = 0;
        virtual void draw(sf::RenderWindow& window, std::size_t currentFrame) = 0;

    protected:
        std::vector<sf::Texture> _textures;
        sf::Sprite _sprite;

        void setTextures(std::vector<std::string>& texturePaths);
};

} /* namespace entity */
