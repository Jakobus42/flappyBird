#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace entity {

/**
 * @class AEntity
 * @brief Abstract base class representing an entity in the game.
 */
class AEntity {
   public:
    AEntity(float velocity, const std::vector<std::string>& texturePaths);
    virtual ~AEntity();
    AEntity(const AEntity& other);
    AEntity& operator=(const AEntity& other);

    const std::vector<sf::Texture>& getTexture() const;
    const sf::Sprite& getSprite() const;

    virtual bool move() = 0;
    virtual void draw(sf::RenderWindow& window, std::size_t currentFrame) = 0;
    virtual bool checkCollision(std::shared_ptr<entity::AEntity> other) const;
    virtual const sf::Vector2f& getPosition() const;


   protected:
    std::vector<sf::Texture> _textures;
    std::size_t _currentTexture;
    sf::Sprite _sprite;
    float _velocity;

    void setTextures(const std::vector<std::string>& texturePaths);
    void switchToNextTexture(std::size_t frameDelay, std::size_t currentFrame);
};

} /* namespace entity */
