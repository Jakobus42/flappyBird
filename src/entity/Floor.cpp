#include "../../include/entity/Floor.hpp"

namespace entity {

/**
 * @brief Constructs a new Floor object.
 */


Floor::Floor(std::size_t id, std::size_t velocity, const std::vector<std::string>& texturePaths):
AEntity(velocity, texturePaths),
_id(id) {
    _sprite.setPosition(_sprite.getGlobalBounds().width * _id, SCREEN_HEIGHT - _sprite.getGlobalBounds().height);
}

/**
 * @brief Destroys the Floor object.
 */
Floor::~Floor() {}

/**
 * @brief Copy constructor.
 * @param other The other Floor object to copy.
 */
Floor::Floor(const Floor& other): 
AEntity(other) {
    *this = other;
}

/**
 * @brief Copy assignment operator.
 * @param other The other Floor object to assign from.
 * @return A reference to the assigned Floor object.
 */
Floor& Floor::operator=(const Floor& other) {
    if (this != &other) {
        _id = other._id;
        _velocity = other._velocity;
        _currentTexture = other._currentTexture;
    }
    return *this;
}

bool Floor::move(std::size_t) {
    _sprite.move(_velocity, 0);
    if (_sprite.getPosition().x < -_sprite.getGlobalBounds().width) {
        _sprite.setPosition(_sprite.getPosition().x + _sprite.getGlobalBounds().width * 4, _sprite.getPosition().y); //TODO HARDCODED
    }
    return 0;
}

void Floor::draw(sf::RenderWindow& window, std::size_t currentFrame) {
    switchToNextTexture(3, currentFrame)
    window.draw(_sprite);
}

} /* namespace entity */
