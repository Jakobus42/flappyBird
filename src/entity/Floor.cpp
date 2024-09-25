#include "../../include/entity/Floor.hpp"

namespace entity {

/**
 * @brief Constructs a new Floor object.
 */


Floor::Floor(std::size_t id):
AEntity(),
_velocity(-10.0f),
_id(id),
_currentTexture(0) {
    std::vector<std::string> texturePaths = {
        "assets/sprites/base_wide_only.png"
    };
    setTextures(texturePaths);
     _sprite.setTexture(_textures[_currentTexture]);
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
        _sprite.setPosition(_sprite.getPosition().x + _sprite.getGlobalBounds().width * 2, _sprite.getPosition().y);
    }
    return 0;
}

void Floor::draw(sf::RenderWindow& window, std::size_t currentFrame) {
    window.draw(_sprite);
}

} /* namespace entity */
