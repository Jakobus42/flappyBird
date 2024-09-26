#include "../../include/entity/Bird.hpp"


namespace entity {

/**
 * @brief Constructs a new Bird object.
 */
Bird::Bird(std::size_t x, std::size_t y, const std::vector<std::string>& texturePaths,
           float velocity, float jumpForce)
    : AEntity(velocity, texturePaths), _jumpForce(jumpForce) {
    _sprite.setScale(3, 3);
    _sprite.setPosition(x, y - (_textures[_currentTexture].getSize().y * _sprite.getScale().y) / 2);
}

/**
 * @brief Destroys the Bird object.
 */
Bird::~Bird() {}

/**
 * @brief Copy constructor.
 * @param other The other Bird object to copy.
 */
Bird::Bird(const Bird& other) : AEntity(other), _jumpForce(other._jumpForce) {}

/**
 * @brief Copy assignment operator.
 * @param other The other Bird object to assign from.
 * @return A reference to the assigned Bird object.
 */
Bird& Bird::operator=(const Bird& other) {
    if (this != &other) {
        _textures = other._textures;
        _sprite = other._sprite;
    }
    return *this;
}

bool Bird::jump(std::size_t currentFrame) {
    _velocity = -13.5f;
    _sprite.move(0, _velocity);
    return 0;
}

bool Bird::move() {
    _velocity += 0.65f;
    _sprite.move(0, _velocity);
    return 0;
}

void Bird::draw(sf::RenderWindow& window, std::size_t currentFrame) {
    switchToNextTexture(3, currentFrame);
    if (_velocity < 0) {
        _sprite.setRotation(_velocity);
    } else {
        _sprite.setRotation(_velocity * 2);
    }
    window.draw(_sprite);
}

} /* namespace entity */
