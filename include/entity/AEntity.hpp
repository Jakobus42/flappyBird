#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

namespace entity {


/**
 * @class AEntity
 * @brief ...
 */
class AEntity {
    public:
        AEntity(std::size_t velocity, std::vector<std::string> textures);
        virtual ~AEntity();
        AEntity(const AEntity &other);
        AEntity& operator=(const AEntity &other);

        const std::vector<sf::Texture>& getTexture() const;
        const sf::Sprite& getSprite() const;

        virtual bool move(std::size_t currentFrame) = 0;
        virtual void draw(sf::RenderWindow& window, std::size_t currentFrame) = 0;
        virtual bool checkCollision(std::shared_ptr<entity::AEntity> other) const;
    protected:
        std::vector<sf::Texture> _textures;
        std::size_t _velocity;
        sf::Sprite _sprite;

        void setTextures(std::vector<std::string>& texturePaths);
};


} /* namespace entity */
