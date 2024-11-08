#include "../../include/entity/Background.hpp"

namespace entity {

/**
 * @brief Constructs a new Background object.
 */

Background::Background(std::size_t id, std::size_t velocity, const std::vector<std::string>& texturePaths)
    : AEntity(velocity, texturePaths), _id(id) {
    _sprite.setPosition(_sprite.getGlobalBounds().width * _id,
                        SCREEN_HEIGHT - _sprite.getGlobalBounds().height);
}

/**
 * @brief Destroys the Background object.
 */
Background::~Background() {}

/**
 * @brief Copy constructor.
 * @param other The other Background object to copy.
 */
Background::Background(const Background& other) : AEntity(other) { *this = other; }

/**
 * @brief Copy assignment operator.
 * @param other The other Background object to assign from.
 * @return A reference to the assigned Background object.
 */
Background& Background::operator=(const Background& other) {
    if (this != &other) {
        _id = other._id;
        _velocity = other._velocity;
        _currentTexture = other._currentTexture;
    }
    return *this;
}

bool Background::move() {
    _sprite.move(-_velocity, 0);
     if (_sprite.getPosition().x <= -_sprite.getGlobalBounds().width) {
        _sprite.setPosition(_sprite.getPosition().x + _sprite.getGlobalBounds().width * 2, _sprite.getPosition().y);
    }
    return false;
}

void Background::draw(sf::RenderWindow& window, std::size_t currentFrame) {
    window.draw(_sprite);
}

} /* namespace entity */
